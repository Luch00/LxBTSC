#include "PluginHelper.h"
#include "utils.h"
#include <QThread>
#include <QUrlQuery>
#include <QRegularExpression>
//#include <QMessageBox>

PluginHelper::PluginHelper(QString pluginPath, QObject *parent)
	: QObject(parent)
{
	//QMessageBox::information(0, "debug", QString(""), QMessageBox::Ok);
	pathToPlugin = QString(pluginPath);
	utils::checkEmoteSets(pathToPlugin);
	config = new ConfigWidget(pathToPlugin);
	chat = new ChatWidget(pathToPlugin);
	waitForLoad();
	initPwDialog();
	connect(chat, &ChatWidget::fileUrlClicked, this, &PluginHelper::onFileUrlClicked);
	connect(chat, &ChatWidget::clientUrlClicked, this, &PluginHelper::onClientUrlClicked);
	connect(chat, &ChatWidget::channelUrlClicked, this, &PluginHelper::onChannelUrlClicked);
	connect(chat, &ChatWidget::linkHovered, this, &PluginHelper::onLinkHovered);
	connect(chat->webObject(), &TsWebObject::transferCancelled, this, &PluginHelper::onTransferCancelled);
	connect(config, &ConfigWidget::configChanged, chat->webObject(), &TsWebObject::configChanged);
	g = connect(qApp, &QApplication::applicationStateChanged, this, &PluginHelper::onAppStateChanged);
	chat->setStyleSheet("border: 1px solid gray");
}

PluginHelper::~PluginHelper()
{
	disconnect();
	delete pwDialog;
	delete chat;
	delete config;
}

// Disconnect used signals
void PluginHelper::disconnect() const
{
	QObject::disconnect(c);
	QObject::disconnect(d);
	QObject::disconnect(e);
	QObject::disconnect(g);
}

// delay ts a bit until webview  is loaded
void PluginHelper::waitForLoad() const
{
	int waited = 0; //timeout after about 5s
	while (!chat->loaded() && waited < 50)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
		++waited;
		QThread::msleep(100);
	}
}

// silly thing to prevent webengineview freezing on minimize
void PluginHelper::onAppStateChanged(Qt::ApplicationState state)
{
	if (currentState == Qt::ApplicationHidden || currentState == Qt::ApplicationInactive)
	{
		QSize s = chat->size();
		chat->resize(s.width() + 1, s.height() + 1);
		chat->resize(s);
	}
	currentState = state;
}

// Receive chat tab changed signal
void PluginHelper::onTabChange(int i)
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
		currentTabName = tabName;
		chat->webObject()->tabChanged(tabName);
	}
}

// After server tab change check what chat tab is selected
void PluginHelper::recheckSelectedTab()
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
			currentTabName = tabName;
			chat->webObject()->tabChanged(tabName);
		}
	}
}

void PluginHelper::onLinkHovered(const QUrl &url)
{
	QWidget* selectedchat = chatTabWidget->currentWidget();
	QMetaObject::invokeMethod(selectedchat, "highlighted", Q_ARG(QString, url.toString()));
}


void PluginHelper::onClientUrlClicked(const QUrl &url)
{
	QRegularExpression re("client://0\\.0\\.0\\.(\\d+)\\/([\\S]+)~(.+)");
	QRegularExpressionMatch match = re.match(url.toString(QUrl::PrettyDecoded));
	if (match.hasMatch())
	{
		uint64 id = match.captured(1).toULongLong();
		QString uid = match.captured(2);
		QString name = match.captured(3);

		QWidget* selectedchat = chatTabWidget->currentWidget();
		QMetaObject::invokeMethod(selectedchat, "fireContextMenu", Q_ARG(uint64, id), Q_ARG(QWidget*, chat), Q_ARG(bool, true), Q_ARG(QString, name), Q_ARG(QString, uid));
	}
}

void PluginHelper::onChannelUrlClicked(const QUrl& url)
{
	QRegularExpression re("channelid://0\\.0\\.0\\.(\\d+)");
	QRegularExpressionMatch match = re.match(url.toString(QUrl::PrettyDecoded));
	if (match.hasMatch())
	{
		uint64 id = match.captured(1).toULongLong();

		QWidget* selectedchat = chatTabWidget->currentWidget();
		QMetaObject::invokeMethod(selectedchat, "fireContextMenu", Q_ARG(uint64, id), Q_ARG(QWidget*, chat), Q_ARG(bool, false), Q_ARG(QString, ""), Q_ARG(QString, ""));
	}
}

// called when webview tries to navigate to url with ts3file protocol
void PluginHelper::onFileUrlClicked(const QUrl &url)
{
	if (url.hasQuery())
	{
		QUrlQuery query;
		query.setQuery(url.query());

		QString filename = query.queryItemValue("filename", QUrl::FullyDecoded);
		QString size = query.queryItemValue("size", QUrl::FullyDecoded);

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

		File file(filename, size, schi);
		if (filetransfers.values().contains(file))
		{
			// this file is already being transferred -> cancel
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
			filetransfers.insert(res, file);
			emit chat->webObject()->downloadStarted(message_id, res);
		}
		else
		{
			emit chat->webObject()->downloadStartFailed(message_id);
		}
	}
}

// user clicked cancel on transfer
void PluginHelper::onTransferCancelled(int id) const
{
	if (filetransfers.contains(id))
	{
		File f = filetransfers.value(id);
		ts3Functions.haltTransfer(f.serverConnectionHandlerId(), id, 1, nullptr);
	}
}

// called when 'ok' is pressed in password dialog
void PluginHelper::onPwDialogAccepted(const QString pw)
{
	QVariant url = pwDialog->property("url");
	onFileUrlClicked(QUrl(url.toString() + "&password=" + pw.toHtmlEscaped()));
}

// set up the dialog for file transfer passwords
void PluginHelper::initPwDialog()
{
	pwDialog = new QInputDialog(chat);
	pwDialog->setInputMode(QInputDialog::TextInput);
	pwDialog->setLabelText("Password");
	pwDialog->setTextEchoMode(QLineEdit::Password);
	connect(pwDialog, &QInputDialog::textValueSelected, this, &PluginHelper::onPwDialogAccepted);
	pwDialog->setModal(true);
	pwDialog->setProperty("url", "");
}

// called when emote is clicked in html emote menu
void PluginHelper::onEmoticonAppend(QString e) const
{
	if (!chatLineEdit->document()->isModified())
	{
		chatLineEdit->document()->clear();
	}
	chatLineEdit->insertPlainText(e);
	chatLineEdit->setFocus();
}

// called when teamspeak emote menu button is clicked
void PluginHelper::onEmoticonButtonClicked(bool c) const
{
	if (QApplication::keyboardModifiers() == Qt::ControlModifier)
	{
		toggleNormalChat();
	}
	else
	{
		emit chat->webObject()->toggleEmoteMenu();
	}
}

// hides plugin webview and restores the default chatwidget
void PluginHelper::toggleNormalChat() const
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

// Receive chat tab closed signal
void PluginHelper::onTabClose(int i)
{
	if (i > 1)
	{
		const QString tabName = QString("tab-%1-server").arg(servers[currentServerID].safe_uid());
		chat->webObject()->tabChanged(tabName);
		chatTabWidget->setCurrentIndex(0);
	}
}

// grab the necessary ui widgets
void PluginHelper::initUi()
{
	mainwindow = findMainWindow();
	dynamicConnect("callPrintConsoleMessage(uint64,QString,int)", "onPrintConsoleMessage(uint64,QString,int)");
	dynamicConnect("callPrintConsoleMessageToCurrentTab(QString)", "onPrintConsoleMessageToCurrentTab(QString)");

	QWidget* parent = findWidget("MainWindowChatWidget", mainwindow);
	qobject_cast<QBoxLayout*>(parent->layout())->insertWidget(0, chat);

	chatTabWidget = qobject_cast<QTabWidget*>(findWidget("ChatTabWidget", parent));
	chatTabWidget->setMinimumHeight(24);
	chatTabWidget->setMaximumHeight(24);

	c = connect(chatTabWidget, &QTabWidget::currentChanged, this, &PluginHelper::onTabChange);
	d = connect(chatTabWidget, &QTabWidget::tabCloseRequested, this, &PluginHelper::onTabClose);
	chatTabWidget->setMovable(false);

	chatLineEdit = qobject_cast<QTextEdit*>(findWidget("ChatLineEdit", parent));
	connect(chat->webObject(), &TsWebObject::emoteSignal, this, &PluginHelper::onEmoticonAppend);

	emoticonButton = qobject_cast<QToolButton*>(findWidget("EmoticonButton", parent));
	emoticonButton->disconnect();
	e = connect(emoticonButton, &QToolButton::clicked, this, &PluginHelper::onEmoticonButtonClicked);
}

void PluginHelper::dynamicConnect(const QString& signalName, const QString& slotName)
{
	int index = mainwindow->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable(signalName)));
	if (index == -1)
	{
		ts3Functions.printMessageToCurrentTab("Signal not found");
		return;
	}

	QMetaMethod signal = mainwindow->metaObject()->method(index);

	index = this->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(qPrintable(slotName)));
	if (index == -1)
	{
		ts3Functions.printMessageToCurrentTab("Slot not found");
		return;
	}

	QMetaMethod slot = this->metaObject()->method(index);

	connect(mainwindow, signal, this, slot);
}

void PluginHelper::onPrintConsoleMessage(uint64 serverConnectionHandlerID, QString message, int targetMode)
{
	chat->webObject()->printConsoleMessage(getMessageTarget(serverConnectionHandlerID, targetMode, 0), message);
}

void PluginHelper::onPrintConsoleMessageToCurrentTab(QString message)
{
	if (currentTabName.isNull())
	{
		currentTabName = QString("tab-%1-server").arg(servers[currentServerID].safe_uid());
	}
	chat->webObject()->printConsoleMessage(currentTabName, message);
}

// find mainwindow widget
QMainWindow* PluginHelper::findMainWindow() const
{
	foreach(QWidget *widget, qApp->topLevelWidgets())
	{
		if (QMainWindow *m = qobject_cast<QMainWindow*>(widget))
		{
			return m;
		}
	}
	return nullptr;
}

QWidget* PluginHelper::findWidget(QString name, QWidget* parent)
{
	QList<QWidget*> children = parent->findChildren<QWidget*>();
	for (int i = 0; i < children.count(); ++i)
	{
		if (children[i]->objectName() == name)
		{
			return children[i];
		}
	}
	return nullptr;
}

// server tab changed
void PluginHelper::currentServerChanged(uint64 serverConnectionHandlerID)
{
	currentServerID = serverConnectionHandlerID;

	if (first == false)
	{
		recheckSelectedTab();
	}
}

void PluginHelper::textMessageReceived(uint64 serverConnectionHandlerID, anyID fromID, anyID toID, anyID targetMode, QString senderUniqueID, QString fromName, QString message, bool outgoing)
{
	QString userlink = QString("client://%1/%2~%3").arg(QString::number(fromID), senderUniqueID, fromName.toHtmlEscaped());
	emit chat->webObject()->textMessageReceived(
		getMessageTarget(serverConnectionHandlerID, targetMode, outgoing ? toID : fromID),
		outgoing ? "Outgoing" : "Incoming",
		QTime::currentTime().toString("hh:mm:ss"),
		fromName,
		userlink,
		message
	);
}

// string used to identify tabs
QString PluginHelper::getMessageTarget(uint64 serverConnectionHandlerID, anyID targetMode, anyID clientID)
{
	if (targetMode == 3)
	{
		return QString("tab-%1-server").arg(servers[serverConnectionHandlerID].safe_uid());
	}
	if (targetMode == 2)
	{
		return QString("tab-%1-channel").arg(servers[serverConnectionHandlerID].safe_uid());
	}
	return QString("tab-%1-private-%2").arg(servers[serverConnectionHandlerID].safe_uid()).arg(servers[serverConnectionHandlerID].get_client(clientID).safe_uid());
}

// get current time as string
QString PluginHelper::time()
{
	return QTime::currentTime().toString("hh:mm:ss");
}

void PluginHelper::serverConnected(uint64 serverConnectionHandlerID)
{
	if (first)
	{
		initUi();
		first = false;
	}

	char *res;
	if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_UNIQUE_IDENTIFIER, &res) == ERROR_ok)
	{
		const Server server(serverConnectionHandlerID, res, getAllClientNicks(serverConnectionHandlerID));
		emit chat->webObject()->addServer(server.safe_uid());
		bool reconnected = servers.values().contains(server);
		
		servers.insert(serverConnectionHandlerID, server);
		free(res);

		if (!reconnected)
		{
			char *msg;
			if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_WELCOMEMESSAGE, &msg) == ERROR_ok)
			{
				emit chat->webObject()->serverWelcomeMessage(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), msg);
				free(msg);
			}
			if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_NAME, &msg) == ERROR_ok)
			{
				emit chat->webObject()->serverConnected(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), msg);
				free(msg);
				return;
			}
		}
	}
	emit chat->webObject()->serverConnected(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), "");
}

void PluginHelper::serverDisconnected(uint serverConnectionHandlerID)
{
	emit chat->webObject()->serverDisconnected(getMessageTarget(serverConnectionHandlerID, 3, 0), time());
}

void PluginHelper::clientConnected(uint64 serverConnectionHandlerID, anyID clientID)
{
	const Client client = getClient(serverConnectionHandlerID, clientID);
	servers[serverConnectionHandlerID].add_client(clientID, client);
	emit chat->webObject()->clientConnected(getMessageTarget(serverConnectionHandlerID, 3, clientID), time(), client.link(), client.nickname());
}

void PluginHelper::clientDisconnected(uint64 serverConnectionHandlerID, anyID clientID, QString message)
{
	const Client &client = servers[serverConnectionHandlerID].get_client(clientID);
	emit chat->webObject()->clientDisconnected(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), client.link(), client.nickname(), message);
}

void PluginHelper::clientTimeout(uint64 serverConnectionHandlerID, anyID clientID)
{
	const Client &client = servers[serverConnectionHandlerID].get_client(clientID);
	emit chat->webObject()->clientTimeout(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), client.link(), client.nickname());
}

// called when file transfer ends in some way
void PluginHelper::transferStatusChanged(anyID transferID, unsigned status)
{
	if (filetransfers.contains(transferID))
	{
		File file = filetransfers.take(transferID);
		switch (status)
		{
		case ERROR_file_transfer_complete:
			QMetaObject::invokeMethod(chat->webObject(), "downloadFinished", Q_ARG(int, transferID));
			QMetaObject::invokeMethod(mainwindow, "onShowFileTransferTrayMessage", Q_ARG(QString, file.filename()));
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
}

void PluginHelper::clientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, QString displayName)
{
	Client c = servers[serverConnectionHandlerID].get_client(clientID);
	c.set_nickname(displayName);
	servers[serverConnectionHandlerID].add_client(clientID, c);
}

void PluginHelper::poked(uint64 serverConnectionHandlerID, anyID pokerID, QString pokerName, QString pokerUniqueID, QString pokeMessage)
{
	QString userlink = QString("client://%1/%2~%3").arg(QString::number(pokerID), pokerUniqueID, pokerName.toHtmlEscaped());
	emit chat->webObject()->clientPoked(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), userlink, pokerName, pokeMessage);
}

void PluginHelper::reload() const
{
	chat->reload();
}

void PluginHelper::reloadEmotes() const
{
	utils::checkEmoteSets(pathToPlugin);
	emit chat->webObject()->loadEmotes();
}

// Get the nickname and unique id of a client
Client PluginHelper::getClient(uint64 serverConnectionHandlerID, anyID id)
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
		free(uid);
	}
	return Client(res, uniqueid, id);
}

// cache all connected clients
QMap<unsigned short, Client> PluginHelper::getAllClientNicks(uint64 serverConnectionHandlerID)
{
	QMap<unsigned short, Client> map;
	anyID *list;
	if (ts3Functions.getClientList(serverConnectionHandlerID, &list) == ERROR_ok)
	{
		for (size_t i = 0; list[i] != NULL; i++)
		{
			map.insert(list[i], getClient(serverConnectionHandlerID, list[i]));
		}
		free(list);
	}
	return map;
}

void PluginHelper::openConfig()
{
	config->open();
}


