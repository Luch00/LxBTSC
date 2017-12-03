/*
 * Teamspeak 3 chat plugin
 * HTML chatbox using WebEngine
 *
 * Copyright (c) 2017 Luch
 */

#ifdef _WIN32
#pragma warning (disable : 4100)  /* Disable Unreferenced parameter warning */
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "teamspeak/public_errors.h"
#include "teamspeak/public_errors_rare.h"
#include "teamspeak/public_definitions.h"
#include "teamspeak/public_rare_definitions.h"
#include "teamspeak/clientlib_publicdefinitions.h"
#include "ts3_functions.h"
#include "plugin.h"
#include <QApplication>
#include <QMainWindow>
#include <ChatWidget.h>
#include <QMap>
#include <QMetaObject>
#include <QPlainTextEdit>
#include <QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QUrlQuery>
#include <QThread>
#include <server.h>
#include <utils.h>

#include <QInputDialog>

//#include <QMessageBox>

static struct TS3Functions ts3Functions;

#ifdef _WIN32
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s
#else
#define _strcpy(dest, destSize, src) { strncpy(dest, src, destSize-1); (dest)[destSize-1] = '\0'; }
#endif

#define PLUGIN_API_VERSION 22

#define PATH_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

static char* pluginID = NULL;

#ifdef _WIN32
/* Helper function to convert wchar_T to Utf-8 encoded strings on Windows */
static int wcharToUtf8(const wchar_t* str, char** result) {
	int outlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, 0, 0);
	*result = (char*)malloc(outlen);
	if(WideCharToMultiByte(CP_UTF8, 0, str, -1, *result, outlen, 0, 0) == 0) {
		*result = NULL;
		return -1;
	}
	return 0;
}
#endif

/*********************************** Required functions ************************************/
/*
 * If any of these required functions is not implemented, TS3 will refuse to load the plugin
 */

/* Unique name identifying this plugin */
const char* ts3plugin_name() {
#ifdef _WIN32
	/* TeamSpeak expects UTF-8 encoded characters. Following demonstrates a possibility how to convert UTF-16 wchar_t into UTF-8. */
	static char* result = NULL;  /* Static variable so it's allocated only once */
	if(!result) {
		const wchar_t* name = L"Better Chat";
		if(wcharToUtf8(name, &result) == -1) {  /* Convert name into UTF-8 encoded result */
			result = "Better Chat";  /* Conversion failed, fallback here */
		}
	}
	return result;
#else
	return "Better Chat";
#endif
}

/* Plugin version */
const char* ts3plugin_version() {
    return "1.5";
}

/* Plugin API version. Must be the same as the clients API major version, else the plugin fails to load. */
int ts3plugin_apiVersion() {
	return PLUGIN_API_VERSION;
}

/* Plugin author */
const char* ts3plugin_author() {
	/* If you want to use wchar_t, see ts3plugin_name() on how to use */
    return "Luch";
}

/* Plugin description */
const char* ts3plugin_description() {
	/* If you want to use wchar_t, see ts3plugin_name() on how to use */
    return "Better text chat";
}

/* Set TeamSpeak 3 callback functions */
void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
    ts3Functions = funcs;
}

uint64 currentServerID;
ChatWidget *chat;
QInputDialog *pwDialog;

QMap<uint64, Server> servers;
QTabWidget *chatTabWidget;
QPlainTextEdit *chatLineEdit;
QToolButton *emoticonButton;
QMetaObject::Connection c;
QMetaObject::Connection d;
QMetaObject::Connection e;
QMetaObject::Connection f;
QMetaObject::Connection g;
QString pathToPlugin;
bool first = true;

// Receive chat tab changed signal
static void receiveTabChange(int i)
{
	//QMessageBox::information(0, "debug", QString("tabchange_trigger: %1 %2").arg(currentServerID).arg(i), QMessageBox::Ok);
	if (i >= 0)
	{
		QString tabName;
		if (i == 0)
		{
			tabName = QString("tab-%1-server").arg(servers[currentServerID].safe_uid());
		}
		else if (i == 1)
		{
			tabName = QString("tab-%1-channel").arg(servers[currentServerID].safe_uid());
		}
		else
		{
			const QString id = servers[currentServerID].get_client_by_nickname(chatTabWidget->tabText(i)).safe_uid();
			tabName = QString("tab-%1-private-%2").arg(servers[currentServerID].safe_uid()).arg(id);
		}
		chat->webObject()->tabChanged(tabName);
	}
}
 
// After server tab change check what chat tab is selected
static void recheckSelectedTab()
{
	if (currentServerID != NULL)
	{
		const int i = chatTabWidget->currentIndex();

		if (i >= 0)
		{
			QString tabName;
			if (i == 0)
			{
				tabName = QString("tab-%1-server").arg(servers[currentServerID].safe_uid());
			}
			else if (i == 1)
			{
				tabName = QString("tab-%1-channel").arg(servers[currentServerID].safe_uid());
			}
			else
			{
				const QString id = servers[currentServerID].get_client_by_nickname(chatTabWidget->tabText(i)).safe_uid();
				tabName = QString("tab-%1-private-%2").arg(servers[currentServerID].safe_uid()).arg(id);
			}
			chat->webObject()->tabChanged(tabName);
		}
	}
}

// Receive chat tab closed signal
static void receiveTabClose(int i)
{
	if (i > 1)
	{
		const QString tabName = QString("tab-%1-server").arg(servers[currentServerID].safe_uid());
		chat->webObject()->tabChanged(tabName);
		chatTabWidget->setCurrentIndex(0);
	}
}

// hides plugin webview and restores the default chatwidget
void toggleNormalChat()
{
	if (chat->isVisible())
	{
		chat->hide();
		chatTabWidget->setMaximumHeight(16777215);
	}
	else
	{
		chatTabWidget->setMaximumHeight(24);
		chat->show();
	}
}

// called when teamspeak emote menu button is clicked
static void receiveEmoticonButtonClick(bool c)
{
	if(QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		toggleNormalChat();
	}
	else
	{
		emit chat->webObject()->toggleEmoteMenu();
	}
}

// called when webview tries to navigate to url with ts3file protocol
static void receiveFileUrlClick(const QUrl &url)
{
	if (url.hasQuery())
	{
		QUrlQuery query;
		query.setQuery(url.query());
		QString server_uid = query.queryItemValue("serverUID", QUrl::FullyDecoded);

		uint64 schi = NULL;
		for each(const Server & server in servers)
		{
			if (server.uid() == server_uid)
			{
				schi = server.server_connection_handler_id();
			}
		}

		if (schi == NULL)
		{
			// failed to get serverconnectionhandlerid -> cancel
			return;
		}
		// CHECK FOR PASSWORD REQUIREMENT
		QString channel_id = query.queryItemValue("channel", QUrl::FullyDecoded);
		int has_password = 0;
		if (ts3Functions.getChannelVariableAsInt(schi, channel_id.toULongLong(), CHANNEL_FLAG_PASSWORD, &has_password) != ERROR_ok)
		{
			// failed to get channel information -> cancel
			return;
		}

		QString password = query.queryItemValue("password", QUrl::FullyDecoded); //"";
		if (has_password == 1 && password.isEmpty())
		{
			pwDialog->setProperty("url", url);
			pwDialog->show();
			return;
		}

		QString is_dir = query.queryItemValue("isDir", QUrl::FullyDecoded);
		QString file_path = query.queryItemValue("path", QUrl::FullyDecoded);
		QString filename = query.queryItemValue("filename", QUrl::FullyDecoded);
		QString message_id = query.queryItemValue("message_id", QUrl::FullyDecoded);

		QString full_path;
		if (file_path == "/")
		{
			full_path = QString("/%1").arg(filename);
		}
		else
		{
			full_path = QString("%1/%2").arg(file_path, filename);
		}
		std::string std_filepath = full_path.toStdString();

		QString download_path = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DownloadLocation);
		std::string std_download_path = download_path.toStdString();
		std::string std_password = password.toStdString();

		anyID res;
		if (ts3Functions.requestFile(schi, channel_id.toULongLong(), std_password.c_str(), std_filepath.c_str(), 1, 0, std_download_path.c_str(), &res, nullptr) == ERROR_ok)
		{
			emit chat->webObject()->downloadStarted(message_id, res);
		}
	}
}

// called when emote is clicked in html emote menu
static void receiveEmoticonAppend(QString e)
{
	if (!chatLineEdit->document()->isModified())
	{
		chatLineEdit->document()->clear();
	}
	chatLineEdit->insertPlainText(e);
	chatLineEdit->setFocus();
}

// Find the widget containing chat tabs and store it for later use
void findChatTabWidget()
{
	QWidgetList list = qApp->allWidgets();
	for (int i = 0; i < list.count(); i++)
	{
		if (list[i]->objectName() == "ChatTabWidget")
		{
			chatTabWidget = static_cast<QTabWidget*>(list[i]);
			QWidget *parent = chatTabWidget->parentWidget();
			static_cast<QBoxLayout*>(parent->layout())->insertWidget(0, chat);

			chatTabWidget->setMinimumHeight(24);
			chatTabWidget->setMaximumHeight(24);

			c = QObject::connect(chatTabWidget, &QTabWidget::currentChanged, receiveTabChange);
			d = QObject::connect(chatTabWidget, &QTabWidget::tabCloseRequested, receiveTabClose);
			chatTabWidget->setMovable(false);
			
			break;
		}
	}
}

// find the chatline
void findChatLineEdit()
{
	QWidgetList list = qApp->allWidgets();
	for (int i = 0; i < list.count(); i++)
	{
		if (list[i]->objectName() == "ChatLineEdit")
		{
			chatLineEdit = static_cast<QPlainTextEdit*>(list[i]);
			QObject::connect(chat->webObject(), &TsWebObject::emoteSignal, receiveEmoticonAppend);
			break;
		}
	}
}

// find the button for emote menu
void findEmoticonButton()
{
	QWidgetList list = qApp->allWidgets();
	for (int i = 0; i < list.count(); i++)
	{
		if (list[i]->objectName() == "EmoticonButton")
		{
			// the one with no tooltip is the correct one :/
			if (list[i]->toolTip().isEmpty())
			{
				emoticonButton = static_cast<QToolButton*>(list[i]);
				emoticonButton->disconnect();
				e = QObject::connect(emoticonButton, &QToolButton::clicked, receiveEmoticonButtonClick);
				break;
			}
		}
	}
}

// silly thing to prevent webengineview freezing on minimize
Qt::ApplicationState currentState;
void appStateChanged(Qt::ApplicationState state)
{
	if (currentState == Qt::ApplicationHidden || currentState == Qt::ApplicationInactive)
	{
		QSize s = chat->size();
		chat->resize(s.width() + 1, s.height() + 1);
		chat->resize(s);
	}
	currentState = state;
}

// Disconnect used signals
void disconnectChatWidget()
{
	// disconnect or crash
	QObject::disconnect(c);
	QObject::disconnect(d);
	QObject::disconnect(e);
	QObject::disconnect(f);
	QObject::disconnect(g);
}

// delay ts a bit until webview  is loaded
void waitForLoad()
{
	int waited = 0; //timeout after about 5s
	while(!chat->loaded() && waited < 50)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
		++waited;
		QThread::msleep(100);
	}
}

// called when 'ok' is pressed in password dialog
static void pwDialogAccepted(const QString pw)
{
	QVariant url = pwDialog->property("url");
	receiveFileUrlClick(QUrl(url.toString() + "&password=" + pw.toHtmlEscaped()));
}

// set up the dialog for file transfer passwords
void initPwDialog()
{
	pwDialog = new QInputDialog(chat);
	pwDialog->setInputMode(QInputDialog::TextInput);
	pwDialog->setLabelText("Password");
	pwDialog->setTextEchoMode(QLineEdit::Password);
	QObject::connect(pwDialog, &QInputDialog::textValueSelected, pwDialogAccepted);
	pwDialog->setModal(true);
	pwDialog->setProperty("url", "");
}

// Init plugin
int ts3plugin_init() {
	char pluginPath[PATH_BUFSIZE];
	
	ts3Functions.getPluginPath(pluginPath, PATH_BUFSIZE, pluginID);
	pathToPlugin = QString(pluginPath);
	utils::checkEmoteSets(pathToPlugin);
	initPwDialog();
	chat = new ChatWidget(pathToPlugin);
	waitForLoad();
	QObject::connect(chat, &ChatWidget::fileUrlClicked, receiveFileUrlClick);
	g = QObject::connect(qApp, &QApplication::applicationStateChanged, appStateChanged);
	chat->setStyleSheet("border: 1px solid gray");

    return 0;
}

/* Custom code called right before the plugin is unloaded */
void ts3plugin_shutdown() {
    /* Your plugin cleanup code here */
	disconnectChatWidget();
	delete chat;
	delete pwDialog;

	/* Free pluginID if we registered it */
	if(pluginID) {
		free(pluginID);
		pluginID = NULL;
	}
}

/****************************** Optional functions ********************************/
/*
 * Following functions are optional, if not needed you don't need to implement them.
 */

/* Tell client if plugin offers a configuration window. If this function is not implemented, it's an assumed "does not offer" (PLUGIN_OFFERS_NO_CONFIGURE). */
//int ts3plugin_offersConfigure() {
//	/*
//	 * Return values:
//	 * PLUGIN_OFFERS_NO_CONFIGURE         - Plugin does not implement ts3plugin_configure
//	 * PLUGIN_OFFERS_CONFIGURE_NEW_THREAD - Plugin does implement ts3plugin_configure and requests to run this function in an own thread
//	 * PLUGIN_OFFERS_CONFIGURE_QT_THREAD  - Plugin does implement ts3plugin_configure and requests to run this function in the Qt GUI thread
//	 */
//	return PLUGIN_OFFERS_NO_CONFIGURE;  /* In this case ts3plugin_configure does not need to be implemented */
//}

/* Plugin might offer a configuration window. If ts3plugin_offersConfigure returns 0, this function does not need to be implemented. */
//void ts3plugin_configure(void* handle, void* qParentWidget) {
//}

void ts3plugin_registerPluginID(const char* id) {
	const size_t sz = strlen(id) + 1;
	pluginID = (char*)malloc(sz * sizeof(char));
	_strcpy(pluginID, sz, id);  /* The id buffer will invalidate after exiting this function */
}

/* Plugin command keyword. Return NULL or "" if not used. */
const char* ts3plugin_commandKeyword() {
	return "lxb";
}

/* Plugin processes console command. Return 0 if plugin handled the command, 1 if not handled. */
int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char* command) {
	if (strcmp(command, "toggle") == 0)
	{
		toggleNormalChat();
	}
	if (strcmp(command, "reload") == 0)
	{
		chat->reload();
	}
	if (strcmp(command, "emotes") == 0)
	{
		utils::checkEmoteSets(pathToPlugin);
		emit chat->webObject()->loadEmotes();
	}
	return 0;  /* Plugin handled command */
}

/* Client changed current server connection handler */
void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID) {
	currentServerID = serverConnectionHandlerID;

	if (first == false)
	{
		recheckSelectedTab();
	}
}

/* Required to release the memory for parameter "data" allocated in ts3plugin_infoData and ts3plugin_initMenus */
void ts3plugin_freeMemory(void* data) {
	free(data);
}

int ts3plugin_requestAutoload() {
	return 0;  /* 1 = request autoloaded, 0 = do not request autoload */
}

/************************** TeamSpeak callbacks ***************************/
/*
 * Following functions are optional, feel free to remove unused callbacks.
 * See the clientlib documentation for details on each function.
 */

/* Clientlib */

// Get the nickname and unique id of a client
Client getClient(uint64 serverConnectionHandlerID, anyID id)
{
	char res[TS3_MAX_SIZE_CLIENT_NICKNAME];
	if (ts3Functions.getClientDisplayName(serverConnectionHandlerID, id, res, TS3_MAX_SIZE_CLIENT_NICKNAME) == ERROR_ok)
	{
	}
	QString uniqueid;
	char *uid;
	if (ts3Functions.getClientVariableAsString(serverConnectionHandlerID, id, CLIENT_UNIQUE_IDENTIFIER, &uid) == ERROR_ok)
	{
		uniqueid = uid;
		ts3plugin_freeMemory(uid);
	}
	return Client(res, uniqueid);
}

// cache all connected clients
QMap<unsigned short, Client> getAllClientNicks(uint64 serverConnectionHandlerID)
{
	QMap<unsigned short, Client> map;
	anyID *list;
	if (ts3Functions.getClientList(serverConnectionHandlerID, &list) == ERROR_ok)
	{
		for (size_t i = 0; list[i] != NULL; i++)
		{
			map.insert(list[i], getClient(serverConnectionHandlerID, list[i]));
		}
		ts3plugin_freeMemory(list);
	}
	return map;
}

// connected to or disconnected from a server
void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber) {
	if (newStatus == STATUS_CONNECTION_ESTABLISHED)
	{
		if (first)
		{
			// Add new chat widget to the UI
			findChatLineEdit();
			findEmoticonButton();
			findChatTabWidget();
			first = false;
		}

		char *res;
		if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_UNIQUE_IDENTIFIER, &res) == ERROR_ok)
		{
			const Server server(serverConnectionHandlerID, res, getAllClientNicks(serverConnectionHandlerID));
			emit chat->webObject()->addServer(server.safe_uid());
			char *msg;
			if (!servers.values().contains(server))
			{
				if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_WELCOMEMESSAGE, &msg) == ERROR_ok)
				{
					emit chat->webObject()->statusMessageReceived(QString("tab-%1-server").arg(server.safe_uid()), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_Welcome", msg);
					ts3plugin_freeMemory(msg);
				}
			}
			servers.insert(serverConnectionHandlerID, server);
			ts3plugin_freeMemory(res);
		}
		emit chat->webObject()->statusMessageReceived(QString("tab-%1-server").arg(servers[serverConnectionHandlerID].safe_uid()), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_Connected", "Server Connected");
	}
	if (newStatus == STATUS_DISCONNECTED)
	{
		emit chat->webObject()->statusMessageReceived(QString("tab-%1-server").arg(servers[serverConnectionHandlerID].safe_uid()), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_Disconnected", "Server Disconnected");
	}
}

// Show a status message when a client connects or disconnects
void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage) {
	if (oldChannelID == 0)
	{
		// client connected
		const Client client = getClient(serverConnectionHandlerID, clientID);
		servers[serverConnectionHandlerID].add_client(clientID, client);

		//emit chat->webObject()->statusMessageReceived(QString("tab-%1-server").arg(servers[serverConnectionHandlerID].safe_uid()), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_ClientConnected", QString("<span class='TextMessage_UserLink'>%1</span> connected").arg(client.nickname()));
		emit chat->webObject()->statusMessageReceived(QString("tab-%1-server").arg(servers[serverConnectionHandlerID].safe_uid()), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_ClientConnected", QString("%1 connected").arg(client.nickname()));
	}
	if (newChannelID == 0)
	{
		const Client &client = servers[serverConnectionHandlerID].get_client(clientID);
		//chat->statusReceived(QString("tab-%1-server").arg(servers[serverConnectionHandlerID]), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_ClientDisconnected", QString("<span class=\\'TextMessage_UserLink\\'>%1</span> disconnected (%2)").arg(client.nickname).arg(moveMessage));
		emit chat->webObject()->statusMessageReceived(QString("tab-%1-server").arg(servers[serverConnectionHandlerID].safe_uid()), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_ClientDisconnected", QString("%1 disconnected (%2)").arg(client.nickname()).arg(moveMessage));
	}
}

// client drops connection
void ts3plugin_onClientMoveTimeoutEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage) {
	const Client &client = servers[serverConnectionHandlerID].get_client(clientID);
	//chat->statusReceived(QString("tab-%1-server").arg(servers[serverConnectionHandlerID]), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_ClientDropped", QString("<span class=\\'TextMessage_UserLink\\'>%1</span> timed out").arg(client.nickname));
	emit chat->webObject()->statusMessageReceived(QString("tab-%1-server").arg(servers[serverConnectionHandlerID].safe_uid()), QTime::currentTime().toString("hh:mm:ss"), "TextMessage_ClientDropped", QString("%1 timed out").arg(client.nickname()));
}

int ts3plugin_onServerErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, const char* extraMessage) {
	if(returnCode) {
		return 1;
	}
	return 0;  /* If no plugin return code was used, the return value of this function is ignored */
}

// Client received a text message
int ts3plugin_onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message, int ffIgnored) {

	/* Friend/Foe manager has ignored the message, so ignore here as well. */
	if(ffIgnored) {
		return 0; /* Client will ignore the message anyways, so return value here doesn't matter */
	}

	// get clients own ID
	anyID myID;
	if (ts3Functions.getClientID(serverConnectionHandlerID, &myID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		return 0;
	}
	bool outgoing = false;
	if (myID == fromID) {
		outgoing = true;
	}

	QString key;
	if (targetMode == 3)
	{
		key = QString("tab-%1-server").arg(servers[serverConnectionHandlerID].safe_uid());
	}
	else if (targetMode == 2)
	{
		key = QString("tab-%1-channel").arg(servers[serverConnectionHandlerID].safe_uid());
	}
	else
	{
		if (fromID == myID)
		{
			key = QString("tab-%1-private-%2").arg(servers[serverConnectionHandlerID].safe_uid()).arg(servers[serverConnectionHandlerID].get_client(toID).safe_uid());
		}
		else
		{
			key = QString("tab-%1-private-%2").arg(servers[serverConnectionHandlerID].safe_uid()).arg(servers[serverConnectionHandlerID].get_client(fromID).safe_uid());
		}
	}
	emit chat->webObject()->textMessageReceived(key, utils::direction(outgoing), QTime::currentTime().toString("hh:mm:ss"), fromName, message);
    return 0;  /* 0 = handle normally, 1 = client will ignore the text message */
}

// this is called when file transfer ends in some way
void ts3plugin_onFileTransferStatusEvent(anyID transferID, unsigned int status, const char* statusMessage, uint64 remotefileSize, uint64 serverConnectionHandlerID) {
	switch (status)
	{
	case ERROR_file_transfer_complete:
		QMetaObject::invokeMethod(chat->webObject(), "downloadFinished", Q_ARG(int, transferID));
		break;
	case ERROR_file_transfer_canceled:
		QMetaObject::invokeMethod(chat->webObject(), "downloadCancelled", Q_ARG(int, transferID));
		break;
	case ERROR_file_transfer_interrupted:
		QMetaObject::invokeMethod(chat->webObject(), "downloadFailed", Q_ARG(int, transferID));
		break;
	case ERROR_file_transfer_reset:
		QMetaObject::invokeMethod(chat->webObject(), "downloadFailed", Q_ARG(int, transferID));
		break;
	default:
		QMetaObject::invokeMethod(chat->webObject(), "downloadFailed", Q_ARG(int, transferID));
		break;
	}
}

/* Called when client custom nickname changed */
void ts3plugin_onClientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, const char* displayName, const char* uniqueClientIdentifier) {
	Client c = servers[serverConnectionHandlerID].get_client(clientID);
	c.set_nickname(displayName);
	servers[serverConnectionHandlerID].add_client(clientID, c);
}

//void ts3plugin_onNewChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID) {
//}

//void ts3plugin_onNewChannelCreatedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 channelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onDelChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onChannelMoveEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 newChannelParentID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onUpdateChannelEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onUpdateChannelEditedEvent(uint64 serverConnectionHandlerID, uint64 channelID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onUpdateClientEvent(uint64 serverConnectionHandlerID, anyID clientID, anyID invokerID, const char* invokerName, const char* invokerUniqueIdentifier) {
//}

//void ts3plugin_onClientMoveSubscriptionEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility) {
//}

//void ts3plugin_onClientMoveMovedEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage) {
//}

//void ts3plugin_onClientKickFromChannelEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage) {
//}

//void ts3plugin_onClientKickFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage) {
//}

//void ts3plugin_onClientIDsEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, anyID clientID, const char* clientName) {
//}

//void ts3plugin_onClientIDsFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onServerEditedEvent(uint64 serverConnectionHandlerID, anyID editerID, const char* editerName, const char* editerUniqueIdentifier) {
//}

//void ts3plugin_onServerUpdatedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onServerStopEvent(uint64 serverConnectionHandlerID, const char* shutdownMessage) {
//}

//void ts3plugin_onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID) {
//}

//void ts3plugin_onConnectionInfoEvent(uint64 serverConnectionHandlerID, anyID clientID) {
//}

//void ts3plugin_onServerConnectionInfoEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onChannelSubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onChannelSubscribeFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onChannelUnsubscribeEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onChannelUnsubscribeFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onChannelDescriptionUpdateEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onChannelPasswordChangedEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onPlaybackShutdownCompleteEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onSoundDeviceListChangedEvent(const char* modeID, int playOrCap) {
//}

//void ts3plugin_onEditPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short* samples, int sampleCount, int channels) {
//}

//void ts3plugin_onEditPostProcessVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask) {
//}

//void ts3plugin_onEditMixedPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, const unsigned int* channelSpeakerArray, unsigned int* channelFillMask) {
//}

//void ts3plugin_onEditCapturedVoiceDataEvent(uint64 serverConnectionHandlerID, short* samples, int sampleCount, int channels, int* edited) {
//}

//void ts3plugin_onCustom3dRolloffCalculationClientEvent(uint64 serverConnectionHandlerID, anyID clientID, float distance, float* volume) {
//}

//void ts3plugin_onCustom3dRolloffCalculationWaveEvent(uint64 serverConnectionHandlerID, uint64 waveHandle, float distance, float* volume) {
//}

//void ts3plugin_onUserLoggingMessageEvent(const char* logMessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString) {
//}

/* Clientlib rare */

//void ts3plugin_onClientBanFromServerEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, anyID kickerID, const char* kickerName, const char* kickerUniqueIdentifier, uint64 time, const char* kickMessage) {
//}

//int ts3plugin_onClientPokeEvent(uint64 serverConnectionHandlerID, anyID fromClientID, const char* pokerName, const char* pokerUniqueIdentity, const char* message, int ffIgnored) {
//    return 0;  /* 0 = handle normally, 1 = client will ignore the poke */
//}

//void ts3plugin_onClientSelfVariableUpdateEvent(uint64 serverConnectionHandlerID, int flag, const char* oldValue, const char* newValue) {
//}

//void ts3plugin_onFileListEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompletesize, const char* returnCode) {
//}

//void ts3plugin_onFileListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* path) {
//}

//void ts3plugin_onFileInfoEvent(uint64 serverConnectionHandlerID, uint64 channelID, const char* name, uint64 size, uint64 datetime) {
//}

//void ts3plugin_onServerGroupListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, const char* name, int type, int iconID, int saveDB) {
//}

//void ts3plugin_onServerGroupListFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onServerGroupByClientIDEvent(uint64 serverConnectionHandlerID, const char* name, uint64 serverGroupList, uint64 clientDatabaseID) {
//}

//void ts3plugin_onServerGroupPermListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onServerGroupPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID) {
//}

//void ts3plugin_onServerGroupClientListEvent(uint64 serverConnectionHandlerID, uint64 serverGroupID, uint64 clientDatabaseID, const char* clientNameIdentifier, const char* clientUniqueID) {
//}

//void ts3plugin_onChannelGroupListEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, const char* name, int type, int iconID, int saveDB) {
//}

//void ts3plugin_onChannelGroupListFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onChannelGroupPermListEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onChannelGroupPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID) {
//}

//void ts3plugin_onChannelPermListEvent(uint64 serverConnectionHandlerID, uint64 channelID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onChannelPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID) {
//}

//void ts3plugin_onClientPermListEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onClientPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID) {
//}

//void ts3plugin_onChannelClientPermListEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 clientDatabaseID, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onChannelClientPermListFinishedEvent(uint64 serverConnectionHandlerID, uint64 channelID, uint64 clientDatabaseID) {
//}

//void ts3plugin_onClientChannelGroupChangedEvent(uint64 serverConnectionHandlerID, uint64 channelGroupID, uint64 channelID, anyID clientID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
//}

//int ts3plugin_onServerPermissionErrorEvent(uint64 serverConnectionHandlerID, const char* errorMessage, unsigned int error, const char* returnCode, unsigned int failedPermissionID) {
//	return 0;  /* See onServerErrorEvent for return code description */
//}

//void ts3plugin_onPermissionListGroupEndIDEvent(uint64 serverConnectionHandlerID, unsigned int groupEndID) {
//}

//void ts3plugin_onPermissionListEvent(uint64 serverConnectionHandlerID, unsigned int permissionID, const char* permissionName, const char* permissionDescription) {
//}

//void ts3plugin_onPermissionListFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onPermissionOverviewEvent(uint64 serverConnectionHandlerID, uint64 clientDatabaseID, uint64 channelID, int overviewType, uint64 overviewID1, uint64 overviewID2, unsigned int permissionID, int permissionValue, int permissionNegated, int permissionSkip) {
//}

//void ts3plugin_onPermissionOverviewFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onServerGroupClientAddedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientName, const char* clientUniqueIdentity, uint64 serverGroupID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
//}

//void ts3plugin_onServerGroupClientDeletedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientName, const char* clientUniqueIdentity, uint64 serverGroupID, anyID invokerClientID, const char* invokerName, const char* invokerUniqueIdentity) {
//}

//void ts3plugin_onClientNeededPermissionsEvent(uint64 serverConnectionHandlerID, unsigned int permissionID, int permissionValue) {
//}

//void ts3plugin_onClientNeededPermissionsFinishedEvent(uint64 serverConnectionHandlerID) {
//}

//void ts3plugin_onClientChatClosedEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientUniqueIdentity) {
//}

//void ts3plugin_onClientChatComposingEvent(uint64 serverConnectionHandlerID, anyID clientID, const char* clientUniqueIdentity) {
//}

//void ts3plugin_onServerLogEvent(uint64 serverConnectionHandlerID, const char* logMsg) {
//}

//void ts3plugin_onServerLogFinishedEvent(uint64 serverConnectionHandlerID, uint64 lastPos, uint64 fileSize) {
//}

//void ts3plugin_onMessageListEvent(uint64 serverConnectionHandlerID, uint64 messageID, const char* fromClientUniqueIdentity, const char* subject, uint64 timestamp, int flagRead) {
//}

//void ts3plugin_onMessageGetEvent(uint64 serverConnectionHandlerID, uint64 messageID, const char* fromClientUniqueIdentity, const char* subject, const char* message, uint64 timestamp) {
//}

//void ts3plugin_onClientDBIDfromUIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID) {
//}

//void ts3plugin_onClientNamefromUIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID, const char* clientNickName) {
//}

//void ts3plugin_onClientNamefromDBIDEvent(uint64 serverConnectionHandlerID, const char* uniqueClientIdentifier, uint64 clientDatabaseID, const char* clientNickName) {
//}

//void ts3plugin_onComplainListEvent(uint64 serverConnectionHandlerID, uint64 targetClientDatabaseID, const char* targetClientNickName, uint64 fromClientDatabaseID, const char* fromClientNickName, const char* complainReason, uint64 timestamp) {
//}

//void ts3plugin_onBanListEvent(uint64 serverConnectionHandlerID, uint64 banid, const char* ip, const char* name, const char* uid, uint64 creationTime, uint64 durationTime, const char* invokerName,
//							  uint64 invokercldbid, const char* invokeruid, const char* reason, int numberOfEnforcements, const char* lastNickName) {
//}

//void ts3plugin_onClientServerQueryLoginPasswordEvent(uint64 serverConnectionHandlerID, const char* loginPassword) {
//}

//void ts3plugin_onPluginCommandEvent(uint64 serverConnectionHandlerID, const char* pluginName, const char* pluginCommand) {
//}

//void ts3plugin_onIncomingClientQueryEvent(uint64 serverConnectionHandlerID, const char* commandText) {
//}

//void ts3plugin_onServerTemporaryPasswordListEvent(uint64 serverConnectionHandlerID, const char* clientNickname, const char* uniqueClientIdentifier, const char* description, const char* password, uint64 timestampStart, uint64 timestampEnd, uint64 targetChannelID, const char* targetChannelPW) {
//}

/* Client UI callbacks */

/*
 * Called from client when an avatar image has been downloaded to or deleted from cache.
 * This callback can be called spontaneously or in response to ts3Functions.getAvatar()
 */
//void ts3plugin_onAvatarUpdated(uint64 serverConnectionHandlerID, anyID clientID, const char* avatarPath) {
//}

/*
 * Called when a plugin menu item (see ts3plugin_initMenus) is triggered. Optional function, when not using plugin menus, do not implement this.
 *
 * Parameters:
 * - serverConnectionHandlerID: ID of the current server tab
 * - type: Type of the menu (PLUGIN_MENU_TYPE_CHANNEL, PLUGIN_MENU_TYPE_CLIENT or PLUGIN_MENU_TYPE_GLOBAL)
 * - menuItemID: Id used when creating the menu item
 * - selectedItemID: Channel or Client ID in the case of PLUGIN_MENU_TYPE_CHANNEL and PLUGIN_MENU_TYPE_CLIENT. 0 for PLUGIN_MENU_TYPE_GLOBAL.
 */
//void ts3plugin_onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID) {
//}

/* This function is called if a plugin hotkey was pressed. Omit if hotkeys are unused. */
//void ts3plugin_onHotkeyEvent(const char* keyword) {
//}

/* Called when recording a hotkey has finished after calling ts3Functions.requestHotkeyInputDialog */
//void ts3plugin_onHotkeyRecordedEvent(const char* keyword, const char* key) {
//}

// This function receives your key Identifier you send to notifyKeyEvent and should return
// the friendly device name of the device this hotkey originates from. Used for display in UI.
//const char* ts3plugin_keyDeviceName(const char* keyIdentifier) {
//	return NULL;
//}

// This function translates the given key identifier to a friendly key name for display in the UI
//const char* ts3plugin_displayKeyText(const char* keyIdentifier) {
//	return NULL;
//}

// This is used internally as a prefix for hotkeys so we can store them without collisions.
// Should be unique across plugins.
//const char* ts3plugin_keyPrefix() {
//	return NULL;
//}

