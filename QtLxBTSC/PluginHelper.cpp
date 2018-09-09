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

	wObject = new TsWebObject(this);
	client = new WebClient();
	connect(client, &WebClient::htmlData, wObject, &TsWebObject::htmlData);
	connect(client, &WebClient::fileData, wObject, &TsWebObject::fileData);
	connect(client, &WebClient::emoteJson, wObject, &TsWebObject::emoteJson);
	connect(client, &WebClient::webError, wObject, &TsWebObject::webError);
	connect(wObject, &TsWebObject::getEmbedData, client, &WebClient::onEmbedData);
	connect(wObject, &TsWebObject::getEmoteJson, client, &WebClient::onEmoteData);

	chat = new ChatWidget(pathToPlugin, wObject);
	waitForLoad();
	connect(chat, &ChatWidget::fileUrlClicked, transfers, &FileTransferListWidget::onFileUrlClicked);
	connect(chat, &ChatWidget::clientUrlClicked, this, &PluginHelper::onClientUrlClicked);
	connect(chat, &ChatWidget::channelUrlClicked, this, &PluginHelper::onChannelUrlClicked);
	connect(chat, &ChatWidget::linkHovered, this, &PluginHelper::onLinkHovered);
	connect(transfers, &FileTransferListWidget::showTransferCompletePop, this, &PluginHelper::onTransferCompleted);
	connect(transfers, &FileTransferListWidget::transferFailed, this, &PluginHelper::onTransferFailure);
	connect(config, &ConfigWidget::configChanged, wObject, &TsWebObject::configChanged);
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
	delete client;
	servers.clear();
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
		auto s = servers.value(ts3Functions.getCurrentServerConnectionHandlerID());
		if (s == nullptr)
			return;

		if (i == 0)
		{
			emit wObject->tabChanged(s->safeUniqueId(), 3, "");
		}
		else if (i == 1)
		{
			emit wObject->tabChanged(s->safeUniqueId(), 2, "");
		}
		else
		{
			auto c = s->getClientByName(chatTabWidget->tabText(i));
			if (c == nullptr)
				return;

			emit wObject->tabChanged(s->safeUniqueId(), 1, c->safeUniqueId());
		}
	}
}

std::tuple<int, QString, QString> PluginHelper::getCurrentTab()
{
	const int i = chatTabWidget->currentIndex();

	if (i >= 0)
	{
		auto s = servers.value(ts3Functions.getCurrentServerConnectionHandlerID());
		if (s == nullptr)
			return { 0, "", "" };

		if (i == 0)
		{
			return { 3, s->safeUniqueId(), "" };
		}
		if (i == 1)
		{
			return { 2, s->safeUniqueId(), "" };
		}
		auto c = s->getClientByName(chatTabWidget->tabText(i));
		if (c == nullptr)
			return { 0, "", "" };

		return { 1, s->safeUniqueId(), c->safeUniqueId() };
	}
	return { 0, "", "" };
}

// After server tab change check what chat tab is selected
void PluginHelper::recheckSelectedTab()
{
	int mode;
	QString server;
	QString client;
	std::tie(mode, server, client) = getCurrentTab();
	if (mode > 0)
		emit wObject->tabChanged(server, mode, client);
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
	QMetaObject::invokeMethod(wObject, "downloadFailed");
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
		emit wObject->toggleEmoteMenu();
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
		// prevent freezing
		QSize s = chat->size();
		chat->resize(s.width() + 1, s.height() + 1);
		chat->resize(s);
	}
}

// Receive chat tab closed signal
void PluginHelper::onTabClose(int i)
{
	if (i > 1)
	{
		emit wObject->tabChanged(servers[ts3Functions.getCurrentServerConnectionHandlerID()]->safeUniqueId(), 3, "");
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
	connect(wObject, &TsWebObject::emoteSignal, this, &PluginHelper::onEmoticonAppend);

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
	emit wObject->printConsoleMessage(getServerId(serverConnectionHandlerID), targetMode, "", message);
}

void PluginHelper::onPrintConsoleMessageToCurrentTab(QString message)
{
	int mode;
	QString server;
	QString client;
	std::tie(mode, server, client) = getCurrentTab();
	if (mode > 0)
		emit wObject->printConsoleMessage(server, mode, client, message);
	else
		emit wObject->printConsoleMessage(server, 3, "", message);
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
	if (first == false)
	{
		recheckSelectedTab();
	}
}

void PluginHelper::textMessageReceived(uint64 serverConnectionHandlerID, anyID fromID, anyID toID, anyID targetMode, QString senderUniqueID, QString fromName, QString message, bool outgoing)
{
	auto c = servers.value(serverConnectionHandlerID)->getClient(fromID);
	if (c == nullptr)
	{
		QSharedPointer<TsClient> client(new TsClient(fromName, senderUniqueID, fromID));
		c = client;
		servers.value(serverConnectionHandlerID)->addClient(fromID, client);
	}
	auto r = servers.value(serverConnectionHandlerID)->getClient(toID);
	// serverid, in or out, time, name, link, message, mode, senderid, targetid
	emit wObject->textMessageReceived(
		getServerId(serverConnectionHandlerID),
		outgoing ? "Outgoing" : "Incoming",
		QTime::currentTime().toString("hh:mm:ss"),
		fromName,
		c->clientLink(),
		message,
		targetMode,
		c->safeUniqueId(),
		r != nullptr ? r->safeUniqueId() : "MISSING-DEFAULT"
	);
}

QString PluginHelper::getServerId(uint64 serverConnectionHandlerID)
{
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return "MISSING-DEFAULT";
	return s->safeUniqueId();
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
		auto myid = getOwnClientId(serverConnectionHandlerID);
		QSharedPointer<TsServer> server(new TsServer(serverConnectionHandlerID, res, myid, getAllClientNicks(serverConnectionHandlerID)));
		emit wObject->addServer(server->safeUniqueId());
		
		servers.insert(serverConnectionHandlerID, server);
		free(res);

		char *msg;
		if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_WELCOMEMESSAGE, &msg) == ERROR_ok)
		{
			emit wObject->serverWelcomeMessage(getServerId(serverConnectionHandlerID), time(), msg);
			free(msg);
		}
		if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_NAME, &msg) == ERROR_ok)
		{
			emit wObject->serverConnected(getServerId(serverConnectionHandlerID), time(), msg);
			free(msg);
		}
		recheckSelectedTab();
	}
}

void PluginHelper::serverDisconnected(uint serverConnectionHandlerID)
{
	if (servers.contains(serverConnectionHandlerID))
	{
		// don't spam "disconnected" in case connection was lost
		if (servers.value(serverConnectionHandlerID)->connected())
		{
			servers.value(serverConnectionHandlerID)->setDisconnected();
			emit wObject->serverDisconnected(getServerId(serverConnectionHandlerID), time());
		}
	}
}

void PluginHelper::clientConnected(uint64 serverConnectionHandlerID, anyID clientID)
{
	auto client = getClient(serverConnectionHandlerID, clientID);
	servers.value(serverConnectionHandlerID)->addClient(clientID, client);
	emit wObject->clientConnected(getServerId(serverConnectionHandlerID), time(), client->clientLink(), client->name());
}

void PluginHelper::clientDisconnected(uint64 serverConnectionHandlerID, anyID clientID, QString message)
{
	// don't print own disconnects
	if (clientID == servers.value(serverConnectionHandlerID)->myId())
		return;
	
	auto client = servers.value(serverConnectionHandlerID)->getClient(clientID);
	if (client == nullptr)
		return;

	emit wObject->clientDisconnected(getServerId(serverConnectionHandlerID), time(), client->clientLink(), client->name(), message);
}

void PluginHelper::clientTimeout(uint64 serverConnectionHandlerID, anyID clientID)
{
	auto server = servers.value(serverConnectionHandlerID);
	auto client = server->getClient(clientID);
	emit wObject->clientTimeout(getServerId(serverConnectionHandlerID), time(), client->clientLink(), client->name());
}

// called when file transfer ends in some way
void PluginHelper::transferStatusChanged(anyID transferID, unsigned status)
{
	transfers->transferStatusChanged(transferID, status);
}

void PluginHelper::clientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, QString displayName) const
{
	auto c = servers.value(serverConnectionHandlerID)->getClient(clientID);
	c->setName(displayName);
}

void PluginHelper::poked(uint64 serverConnectionHandlerID, anyID pokerID, QString pokerName, QString pokerUniqueID, QString pokeMessage)
{
	auto c = servers.value(serverConnectionHandlerID)->getClient(pokerID);
	if (c == nullptr)
	{
		QSharedPointer <TsClient> client(new TsClient(pokerName, pokerUniqueID, pokerID));
		c = client;
		servers.value(serverConnectionHandlerID)->addClient(pokerID, client);
	}
	emit wObject->clientPoked(
		getServerId(serverConnectionHandlerID),
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
	emit wObject->loadEmotes();
}

// Get the nickname and unique id of a client
QSharedPointer<TsClient> PluginHelper::getClient(uint64 serverConnectionHandlerID, anyID id)
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
	return QSharedPointer<TsClient>(new TsClient(res, uniqueid, id));
}

// cache all connected visible clients
QMap<unsigned short, QSharedPointer<TsClient>> PluginHelper::getAllClientNicks(uint64 serverConnectionHandlerID)
{
	QMap<unsigned short, QSharedPointer<TsClient>> map;
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
	emit wObject->serverStopped(getServerId(serverConnectionHandlerID), time(), message);
}

// called when client enters view by joining the same channel or by this client subscribing to a channel
void PluginHelper::clientEnteredView(uint64 serverConnectionHandlerID, anyID clientID) const
{
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return;

	s->addClient(clientID, getClient(serverConnectionHandlerID, clientID));
}

anyID PluginHelper::getOwnClientId(uint64 serverConnectionHandlerID) const
{
	anyID id;
	if (ts3Functions.getClientID(serverConnectionHandlerID, &id) != ERROR_ok)
	{
		return 0;
	}
	return id;
}
