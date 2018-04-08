#include "PluginHelper.h"
#include "utils.h"
#include <QThread>
#include <QRegularExpression>

PluginHelper::PluginHelper(QString pluginPath, QObject *parent)
	: QObject(parent)
{
	//QMessageBox::information(0, "debug", QString(""), QMessageBox::Ok);
	pathToPlugin = QString(pluginPath);
	utils::checkEmoteSets(pathToPlugin);
	config = new ConfigWidget(pathToPlugin);
	transfers = new FileTransferListWidget();
	onConfigChanged();
	chat = new ChatWidget(pathToPlugin);
	waitForLoad();
	connect(chat, &ChatWidget::fileUrlClicked, transfers, &FileTransferListWidget::onFileUrlClicked);
	connect(chat, &ChatWidget::clientUrlClicked, this, &PluginHelper::onClientUrlClicked);
	connect(chat, &ChatWidget::channelUrlClicked, this, &PluginHelper::onChannelUrlClicked);
	connect(chat, &ChatWidget::linkHovered, this, &PluginHelper::onLinkHovered);
	connect(transfers, &FileTransferListWidget::showTransferCompletePop, this, &PluginHelper::onTransferCompleted);
	connect(transfers, &FileTransferListWidget::transferFailed, this, &PluginHelper::onTransferFailure);
	connect(config, &ConfigWidget::configChanged, chat->webObject(), &TsWebObject::configChanged);
	connect(config, &ConfigWidget::configChanged, this, &PluginHelper::onConfigChanged);
	g = connect(qApp, &QApplication::applicationStateChanged, this, &PluginHelper::onAppStateChanged);
	chat->setStyleSheet("border: 1px solid gray");
}

PluginHelper::~PluginHelper()
{
	disconnect();
	delete chat;
	delete config;
	delete transfers;
	qDeleteAll(servers);
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
	if (i >= 0)
	{
		TsServer* s = servers.value(ts3Functions.getCurrentServerConnectionHandlerID());
		if (s == nullptr)
			return;

		QString tabName;
		if (i == 0)
		{
			tabName = QString("tab-%1-server").arg(s->safeUniqueId());
		}
		else if (i == 1)
		{
			tabName = QString("tab-%1-channel").arg(s->safeUniqueId());
		}
		else
		{
			TsClient* c = s->getClientByName(chatTabWidget->tabText(i));
			if (c == nullptr)
				return;

			tabName = QString("tab-%1-private-%2").arg(s->safeUniqueId()).arg(c->safeUniqueId());
		}
		currentTabName = tabName;
		emit chat->webObject()->tabChanged(tabName);
	}
}

// After server tab change check what chat tab is selected
void PluginHelper::recheckSelectedTab()
{
	//if (currentServerID != NULL)
	//{
		const int i = chatTabWidget->currentIndex();

		if (i >= 0)
		{
			TsServer* s = servers.value(ts3Functions.getCurrentServerConnectionHandlerID());
			if (s == nullptr)
				return;

			QString tabName;
			if (i == 0)
			{
				tabName = QString("tab-%1-server").arg(s->safeUniqueId());
			}
			else if (i == 1)
			{
				tabName = QString("tab-%1-channel").arg(s->safeUniqueId());
			}
			else
			{
				TsClient* c = s->getClientByName(chatTabWidget->tabText(i));
				if (c == nullptr)
					return;

				tabName = QString("tab-%1-private-%2").arg(s->safeUniqueId()).arg(c->safeUniqueId());
			}
			currentTabName = tabName;
			emit chat->webObject()->tabChanged(tabName);
		}
	//}
}

void PluginHelper::onLinkHovered(const QUrl &url)
{
	QWidget* selectedchat = chatTabWidget->currentWidget();
	QMetaObject::invokeMethod(selectedchat, "highlighted", Q_ARG(QString, url.toString()));
}


void PluginHelper::onClientUrlClicked(const QUrl &url)
{
	const static QRegularExpression re("client://0\\.0\\.0\\.(\\d+)\\/([\\S]+)~(.+)");
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
	const static QRegularExpression re("channelid://0\\.0\\.0\\.(\\d+)");
	QRegularExpressionMatch match = re.match(url.toString(QUrl::PrettyDecoded));
	if (match.hasMatch())
	{
		uint64 id = match.captured(1).toULongLong();

		QWidget* selectedchat = chatTabWidget->currentWidget();
		QMetaObject::invokeMethod(selectedchat, "fireContextMenu", Q_ARG(uint64, id), Q_ARG(QWidget*, chat), Q_ARG(bool, false), Q_ARG(QString, ""), Q_ARG(QString, ""));
	}
}

void PluginHelper::onTransferCompleted(QString filename) const
{
	QMetaObject::invokeMethod(mainwindow, "onShowFileTransferTrayMessage", Q_ARG(QString, filename));
}

void PluginHelper::onTransferFailure() const
{
	QMetaObject::invokeMethod(chat->webObject(), "downloadFailed");
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
		const QString tabName = QString("tab-%1-server").arg(servers[ts3Functions.getCurrentServerConnectionHandlerID()]->safeUniqueId());
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
		currentTabName = QString("tab-%1-server").arg(servers.value(ts3Functions.getCurrentServerConnectionHandlerID())->safeUniqueId());
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
	//currentServerID = serverConnectionHandlerID;

	if (first == false)
	{
		recheckSelectedTab();
	}
}

void PluginHelper::textMessageReceived(uint64 serverConnectionHandlerID, anyID fromID, anyID toID, anyID targetMode, QString senderUniqueID, QString fromName, QString message, bool outgoing)
{
	TsClient* c = servers.value(serverConnectionHandlerID)->getClient(fromID);
	if (c == nullptr)
	{
		c = new TsClient(fromName, senderUniqueID, fromID);
		servers.value(serverConnectionHandlerID)->addClient(fromID, c);
	}
	emit chat->webObject()->textMessageReceived(
		getMessageTarget(serverConnectionHandlerID, targetMode, outgoing ? toID : fromID),
		outgoing ? "Outgoing" : "Incoming",
		QTime::currentTime().toString("hh:mm:ss"),
		fromName,
		c->clientLink(),
		message
	);
}

// string used to identify tabs
QString PluginHelper::getMessageTarget(uint64 serverConnectionHandlerID, anyID targetMode, anyID clientID)
{
	TsServer * s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return "tab-MISSING-DEFAULT";

	if (targetMode == 3)
	{
		return QString("tab-%1-server").arg(s->safeUniqueId());
	}
	if (targetMode == 2)
	{
		return QString("tab-%1-channel").arg(s->safeUniqueId());
	}
	TsClient* c = s->getClient(clientID);
	if (c == nullptr)
		return "tab-MISSING-DEFAULT";

	return QString("tab-%1-private-%2").arg(s->safeUniqueId()).arg(c->safeUniqueId());
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
		//TsServer* server = new TsServer(serverConnectionHandlerID, res);
		TsServer* server = new TsServer(serverConnectionHandlerID, res, getAllClientNicks(serverConnectionHandlerID));
		emit chat->webObject()->addServer(server->safeUniqueId());
		bool reconnected = servers.values().contains(server);
		if (reconnected)
		{
			for each (TsServer* old in servers.values())
			{
				if (old == server)
					delete old;
			}
		}
		
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
	TsClient* client = getClient(serverConnectionHandlerID, clientID);
	servers.value(serverConnectionHandlerID)->addClient(clientID, client);
	emit chat->webObject()->clientConnected(getMessageTarget(serverConnectionHandlerID, 3, clientID), time(), client->clientLink(), client->name());
}

void PluginHelper::clientDisconnected(uint64 serverConnectionHandlerID, anyID clientID, QString message)
{
	TsClient* client = servers.value(serverConnectionHandlerID)->getClient(clientID);
	if (client == nullptr)
	{
		return;
	}
	emit chat->webObject()->clientDisconnected(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), client->clientLink(), client->name(), message);
}

void PluginHelper::clientTimeout(uint64 serverConnectionHandlerID, anyID clientID)
{
	TsClient* client = servers.value(serverConnectionHandlerID)->getClient(clientID);
	emit chat->webObject()->clientTimeout(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), client->clientLink(), client->name());
}

// called when file transfer ends in some way
void PluginHelper::transferStatusChanged(anyID transferID, unsigned status)
{
	transfers->transferStatusChanged(transferID, status);
}

void PluginHelper::clientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, QString displayName) const
{
	TsClient* c = servers.value(serverConnectionHandlerID)->getClient(clientID);
	c->setName(displayName);
}

void PluginHelper::poked(uint64 serverConnectionHandlerID, anyID pokerID, QString pokerName, QString pokerUniqueID, QString pokeMessage)
{
	TsClient* c = servers.value(serverConnectionHandlerID)->getClient(pokerID);
	if (c == nullptr)
	{
		c = new TsClient(pokerName, pokerUniqueID, pokerID);
		servers.value(serverConnectionHandlerID)->addClient(pokerID, c);
	}
	emit chat->webObject()->clientPoked(
		getMessageTarget(serverConnectionHandlerID, 3, 0), 
		time(), 
		c->clientLink(), 
		pokerName, 
		pokeMessage
	);
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
TsClient* PluginHelper::getClient(uint64 serverConnectionHandlerID, anyID id)
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
	return new TsClient(res, uniqueid, id);
}

// cache all connected visible clients
QMap<unsigned short, TsClient*> PluginHelper::getAllClientNicks(uint64 serverConnectionHandlerID)
{
	QMap<unsigned short, TsClient*> map;
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

void PluginHelper::openConfig() const
{
	config->show();
}

void PluginHelper::openTransfers() const
{
	transfers->show();
}

void PluginHelper::onConfigChanged() const
{
	QString dir = config->getConfigAsString("DOWNLOAD_DIR");
	transfers->setDownloadDirectory(dir);
}

void PluginHelper::serverStopped(uint64 serverConnectionHandlerID, QString message)
{
	emit chat->webObject()->serverStopped(getMessageTarget(serverConnectionHandlerID, 3, 0), time(), message);
}

// called when client enters view by joining the same channel or by this client subscribing to a channel
void PluginHelper::clientEnteredView(uint64 serverConnectionHandlerID, anyID clientID) const
{
	TsServer* s = servers.value(serverConnectionHandlerID);
	// return if server 
	if (s == nullptr)
		return;
	/*TsClient* c = getClient(serverConnectionHandlerID, clientID);
	if (c == nullptr)
	{
		ts3Functions.printMessageToCurrentTab("WTF");
	}
	ts3Functions.printMessageToCurrentTab(c->name().toStdString().c_str());*/
	s->addClient(clientID, getClient(serverConnectionHandlerID, clientID));
	//servers.value(serverConnectionHandlerID)->addClient(clientID, getClient(serverConnectionHandlerID, clientID));
}





