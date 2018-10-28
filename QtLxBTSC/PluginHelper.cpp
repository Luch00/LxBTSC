/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "PluginHelper.h"
#include "utils.h"
#include <QTimer>
#include <QMenuBar>
#include <QToolButton>
#include <QApplication>
#include <QFileDialog>

PluginHelper::PluginHelper(const QString& pluginPath, QObject *parent)
	: QObject(parent)
	, wObject(new TsWebObject(this))
	, config(new ConfigWidget(pluginPath))
	, transfers(new FileTransferListWidget())
	, client(new WebClient(this))
	, chat(new ChatWidget(pluginPath, this->wObject))
	, pluginPath(pluginPath)
{
	utils::makeEmoteJsonArray(pluginPath);
	onConfigChanged();

	connect(this, &PluginHelper::triggerReloadEmotes, this, &PluginHelper::reloadEmotes);
	connect(client, &WebClient::htmlData, wObject, &TsWebObject::htmlData);
	connect(client, &WebClient::fileData, wObject, &TsWebObject::fileData);
	connect(client, &WebClient::emoteJson, wObject, &TsWebObject::emoteJson);
	connect(client, &WebClient::webError, wObject, &TsWebObject::webError);
	connect(wObject, &TsWebObject::getEmbedData, client, &WebClient::onEmbedData);
	connect(wObject, &TsWebObject::getEmoteJson, client, &WebClient::onEmoteData);

	connect(chat, &ChatWidget::fileUrlClicked, transfers, &FileTransferListWidget::onFileUrlClicked);
	connect(chat, &ChatWidget::clientUrlClicked, this, &PluginHelper::onClientUrlClicked);
	connect(chat, &ChatWidget::channelUrlClicked, this, &PluginHelper::onChannelUrlClicked);
	connect(chat, &ChatWidget::linkHovered, this, &PluginHelper::onLinkHovered);
	connect(transfers, &FileTransferListWidget::transferFailed, this, &PluginHelper::onTransferFailure);
	connect(config, &ConfigWidget::configChanged, wObject, &TsWebObject::configChanged);
	connect(config, &ConfigWidget::configChanged, this, &PluginHelper::onConfigChanged);

	connect(qApp, &QApplication::applicationStateChanged, this, &PluginHelper::onAppStateChanged);

	// run init when eventloop starts
	QTimer::singleShot(0, this, [=]() { initUi(); });
}

PluginHelper::~PluginHelper()
{
	delete chatMenu;
	delete chat;
	delete config;
	delete transfers;
	servers.clear();
	chatTabWidget->setMaximumHeight(16777215);
	connect(emoticonButton, SIGNAL(clicked()), mainwindow, SLOT(onEmoticonsButtonClicked()));
}

// grab the necessary ui widgets
void PluginHelper::initUi()
{
	mainwindow = utils::findMainWindow();
	connect(mainwindow, SIGNAL(callPrintConsoleMessage(uint64, QString, int)), this, SLOT(onPrintConsoleMessage(uint64, QString, int)));
	connect(mainwindow, SIGNAL(callPrintConsoleMessageToCurrentTab(QString)), this, SLOT(onPrintConsoleMessageToCurrentTab(QString)));
	connect(transfers, SIGNAL(showTransferCompletePop(QString)), mainwindow, SLOT(onShowFileTransferTrayMessage(QString)));

	QWidget* parent = utils::findWidget("MainWindowChatWidget", mainwindow);
	qobject_cast<QBoxLayout*>(parent->layout())->insertWidget(0, chat);

	chatTabWidget = qobject_cast<QTabWidget*>(utils::findWidget("ChatTabWidget", parent));
	chatTabWidget->setMinimumHeight(chatTabWidget->tabBar()->height());
	chatTabWidget->setMaximumHeight(chatTabWidget->tabBar()->height());

	connect(chatTabWidget, &QTabWidget::currentChanged, this, &PluginHelper::onTabChange);
	chatTabWidget->setMovable(false);

	chatLineEdit = qobject_cast<QTextEdit*>(utils::findWidget("ChatLineEdit", parent));
	connect(wObject, &TsWebObject::emoteSignal, this, &PluginHelper::onEmoticonAppend);

	emoticonButton = qobject_cast<QToolButton*>(utils::findWidget("EmoticonButton", parent));
	emoticonButton->disconnect();
	connect(emoticonButton, &QToolButton::clicked, this, &PluginHelper::onEmoticonButtonClicked);

	insertMenu();
	wObject->setDone(true);
	ts3Functions.logMessage("Hook UI", LogLevel_INFO, "BetterChat", 0);
}

// add own menu to menubar
void PluginHelper::insertMenu()
{
	chatMenu = new QMenu("Bette&rChat");
	QMenu* debug = new QMenu("D&ebug", chatMenu);
	QAction* settings = new QAction("&Settings", chatMenu);
	QAction* transfers = new QAction("&Downloads", chatMenu);
	QAction* toggle = new QAction("&Toggle Chat", chatMenu);
	QAction* browseDirectory = new QAction("&Browse Directory", debug);
	QAction* reloademotes = new QAction("&Reload Emotes", debug);
	QAction* reloadchat = new QAction("&Clear and Reload Chat", debug);
	connect(settings, &QAction::triggered, [this]() { openConfig(); });
	connect(transfers, &QAction::triggered, [this]() { openTransfers(); });
	connect(toggle, &QAction::triggered, [this]() { toggleNormalChat(); });
	connect(browseDirectory, &QAction::triggered, [this]() { QDesktopServices::openUrl(QUrl::fromLocalFile(pluginPath + "LxBTSC/template")); });
	connect(reloademotes, &QAction::triggered, [this]() { fullReloadEmotes(); });
	connect(reloadchat, &QAction::triggered, [this]() { chat->reload(); });
	debug->addAction(browseDirectory);
	debug->addSeparator();
	debug->addAction(reloademotes);
	debug->addAction(reloadchat);
	chatMenu->addAction(settings);
	chatMenu->addAction(transfers);
	chatMenu->addAction(toggle);
	chatMenu->addMenu(debug);

	QMenuBar* menubar = mainwindow->menuBar();
	menubar->insertMenu(menubar->actions().last(), chatMenu);
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
void PluginHelper::onTabChange(int i) const
{
	int mode;
	QString server;
	QString client;
	std::tie(mode, server, client) = getTab(i);
	if (mode == 0)
		return;

	emit wObject->tabChanged(server, mode, client);
}

std::tuple<int, QString, QString> PluginHelper::getTab(int tabIndex) const
{
	if (tabIndex >= 0)
	{
		auto s = servers.value(ts3Functions.getCurrentServerConnectionHandlerID());
		if (s == nullptr)
			return { 0, "", "" };

		if (tabIndex == 0)
		{
			return { 3, s->safeUniqueId(), "" };
		}
		if (tabIndex == 1)
		{
			return { 2, s->safeUniqueId(), "" };
		}
		auto c = s->getClientByName(chatTabWidget->tabText(tabIndex));
		if (c == nullptr)
			return { 0, "", "" };

		return { 1, s->safeUniqueId(), c->safeUniqueId() };
	}
	return { 0, "", "" };
}

uint64 PluginHelper::getServerDefaultChannel(uint64 serverConnectionHandlerID)
{
	// first need server channel list
	uint64* channelList;
	if (ts3Functions.getChannelList(serverConnectionHandlerID, &channelList) == ERROR_ok)
	{
		// then go through each channel
		for (size_t i = 0; channelList[i] != NULL; i++)
		{
			// get CHANNEL_FLAG_DEFAULT variable until 1 is returned
			int res;
			if (ts3Functions.getChannelVariableAsInt(serverConnectionHandlerID, channelList[i], CHANNEL_FLAG_DEFAULT, &res) == ERROR_ok)
			{
				if (res == 1)
				{
					// free the array and return id of default channel
					uint64 channelid = channelList[i];
					free(channelList);
					return channelid;
				}
			}
		}
	}
	ts3Functions.logMessage("Could not find default channel", LogLevel_INFO, "BetterChat", 0);
	return 0;
}

void PluginHelper::getServerEmoteFileInfo(uint64 serverConnectionHandlerID)
{
	uint64 channelID = getServerDefaultChannel(serverConnectionHandlerID);
	if (channelID != 0)
	{
		// request file info of emotes.json in default channel root, this will be returned in OnFileInfoEvent
		if (ts3Functions.requestFileInfo(serverConnectionHandlerID, channelID, "", "/emotes.json", returnCodeEmoteFileInfo) != ERROR_ok)
		{
			ts3Functions.logMessage("Could not request server emotes.json", LogLevel_INFO, "BetterChat", 0);
		}
	}
}

void PluginHelper::handleFileInfoEvent(uint64 serverConnectionHandlerID, uint64 channelID, const QString& name, uint64 size, uint64 datetime)
{
	if (name != "/emotes.json") // only handle emotes.json
		return;

	if (size > 31457280) // put in some kind of size limitation, left it as large for now
	{
		ts3Functions.logMessage("emotes.json too large, skipping", LogLevel_INFO, "BetterChat", 0);
		return;
	}

	QFileInfo old(QString("%1LxBTSC/template/Emotes/%2/emotes.json").arg(pluginPath).arg(servers[serverConnectionHandlerID]->safeUniqueId()));

	// check if old file on disk
	if (old.exists())
	{
		qint64 oldUnixtime = old.created().toMSecsSinceEpoch() / 1000; // fileinfoevent gives file creation time as unix timestamp in seconds
		if (datetime > oldUnixtime)
		{
			// file on server is newer, download it
			requestServerEmoteJson(serverConnectionHandlerID, channelID, old.absolutePath());
		}
	}
	else
	{
		// file doesn't exist, download it
		// create subdir
		QDir dir = old.absoluteDir();
		if (!dir.exists())
			if (!dir.mkpath("."))
			{
				ts3Functions.logMessage("Could not create directory in template/Emotes", LogLevel_INFO, "BetterChat", 0);
				return;
			}

		requestServerEmoteJson(serverConnectionHandlerID, channelID, old.absolutePath());
	}
}

void PluginHelper::requestServerEmoteJson(uint64 serverConnectionHandlerID, uint64 channelID, const QString& filePath)
{
	std::string std_download_path = filePath.toStdString();
	anyID res;
	if (ts3Functions.requestFile(serverConnectionHandlerID, channelID, "", "/emotes.json", 1, 0, std_download_path.c_str(), &res, returnCodeEmoteFileRequest) == ERROR_ok)
	{
		downloads.append(res);
	}
	else
	{
		ts3Functions.logMessage("Could not start file transfer (emotes.json)", LogLevel_INFO, "BetterChat", 0);
	}
}


std::tuple<int, QString, QString> PluginHelper::getCurrentTab() const
{
	const int i = chatTabWidget->currentIndex();
	return getTab(i);
}

void PluginHelper::onLinkHovered(const QUrl &url) const
{
	QWidget* selectedchat = chatTabWidget->currentWidget();
	QMetaObject::invokeMethod(selectedchat, "highlighted", Q_ARG(QString, url.toString()));
}


void PluginHelper::onClientUrlClicked(const QUrl &url) const
{
	const static QRegularExpression re(R"(client://0\.0\.0\.(\d+)\/([\S]+)~(.+))");
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

void PluginHelper::onChannelUrlClicked(const QUrl& url) const
{
	const static QRegularExpression re(R"(channelid://0\.0\.0\.(\d+))");
	QRegularExpressionMatch match = re.match(url.toString(QUrl::PrettyDecoded));
	if (match.hasMatch())
	{
		uint64 id = match.captured(1).toULongLong();

		QWidget* selectedchat = chatTabWidget->currentWidget();
		QMetaObject::invokeMethod(selectedchat, "fireContextMenu", Q_ARG(uint64, id), Q_ARG(QWidget*, chat), Q_ARG(bool, false), Q_ARG(QString, ""), Q_ARG(QString, ""));
	}
}

void PluginHelper::onTransferFailure() const
{
	QMetaObject::invokeMethod(wObject, "downloadFailed");
}

// called when emote is clicked in html emote menu
void PluginHelper::onEmoticonAppend(const QString& e) const
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

void PluginHelper::onPrintConsoleMessage(uint64 serverConnectionHandlerID, QString message, int targetMode) const
{
	emit wObject->printConsoleMessage(getServerId(serverConnectionHandlerID), targetMode, "", message);
}

void PluginHelper::onPrintConsoleMessageToCurrentTab(const QString& message) const
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

void PluginHelper::textMessageReceived(uint64 serverConnectionHandlerID, anyID fromID, anyID toID, anyID targetMode, QString senderUniqueID, const QString& fromName, QString message, bool outgoing) const
{
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return;
	auto c = s->getClient(fromID);
	if (c == nullptr)
	{
		QSharedPointer<TsClient> client(new TsClient(fromName, senderUniqueID, fromID));
		c = client;
		servers.value(serverConnectionHandlerID)->addClient(fromID, client);
	}
	auto r = s->getClient(toID);
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

QString PluginHelper::getServerId(uint64 serverConnectionHandlerID) const
{
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return "MISSING-DEFAULT";
	return s->safeUniqueId();
}

void PluginHelper::serverConnected(uint64 serverConnectionHandlerID)
{
	char *res;
	if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_UNIQUE_IDENTIFIER, &res) == ERROR_ok)
	{
		auto myid = getOwnClientId(serverConnectionHandlerID);
		QSharedPointer<TsServer> server(new TsServer(serverConnectionHandlerID, res, myid, getAllVisibleClients(serverConnectionHandlerID)));
		emit wObject->addServer(server->safeUniqueId());
		servers.insert(serverConnectionHandlerID, server);
		free(res);

		char *msg;
		if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_WELCOMEMESSAGE, &msg) == ERROR_ok)
		{
			emit wObject->serverWelcomeMessage(getServerId(serverConnectionHandlerID), utils::time(), msg);
			free(msg);
		}
		if (ts3Functions.getServerVariableAsString(serverConnectionHandlerID, VIRTUALSERVER_NAME, &msg) == ERROR_ok)
		{
			emit wObject->serverConnected(getServerId(serverConnectionHandlerID), utils::time(), msg);
			free(msg);
		}
		getServerEmoteFileInfo(serverConnectionHandlerID);
	}
}

void PluginHelper::serverDisconnected(uint serverConnectionHandlerID) const
{
	if (servers.contains(serverConnectionHandlerID))
	{
		// don't spam "disconnected" in case connection was lost
		if (servers.value(serverConnectionHandlerID)->connected())
		{
			servers.value(serverConnectionHandlerID)->setDisconnected();
			emit wObject->serverDisconnected(getServerId(serverConnectionHandlerID), utils::time());
		}
	}
}

void PluginHelper::clientConnected(uint64 serverConnectionHandlerID, anyID clientID) const
{
	auto client = getClient(serverConnectionHandlerID, clientID);
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return;

	s->addClient(clientID, client);
	emit wObject->clientConnected(getServerId(serverConnectionHandlerID), utils::time(), client->clientLink(), client->name());
}

void PluginHelper::clientDisconnected(uint64 serverConnectionHandlerID, anyID clientID, QString message) const
{
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return;

	// don't print own disconnects
	if (clientID == s->myId())
		return;
	
	auto client = s->getClient(clientID);
	if (client == nullptr)
		return;

	emit wObject->clientDisconnected(getServerId(serverConnectionHandlerID), utils::time(), client->clientLink(), client->name(), message);
}

void PluginHelper::clientTimeout(uint64 serverConnectionHandlerID, anyID clientID) const
{
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return;
	auto c = s->getClient(clientID);
	if (c == nullptr)
		return;

	emit wObject->clientTimeout(getServerId(serverConnectionHandlerID), utils::time(), c->clientLink(), c->name());
}

// called when file transfer ends in some way
void PluginHelper::transferStatusChanged(anyID transferID, unsigned int status)
{
	if (downloads.contains(transferID))
	{
		downloads.removeOne(transferID);
		emit triggerReloadEmotes();
	}
	else
	{
		transfers->transferStatusChanged(transferID, status);
	}
}

void PluginHelper::clientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, QString displayName) const
{
	auto c = servers.value(serverConnectionHandlerID)->getClient(clientID);
	c->setName(displayName);
}

void PluginHelper::poked(uint64 serverConnectionHandlerID, anyID pokerID, const QString& pokerName, QString pokerUniqueID, QString pokeMessage) const
{
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return;

	auto c = s->getClient(pokerID);
	if (c == nullptr)
	{
		QSharedPointer <TsClient> client(new TsClient(pokerName, pokerUniqueID, pokerID));
		c = client;
		s->addClient(pokerID, client);
	}
	emit wObject->clientPoked(
		getServerId(serverConnectionHandlerID),
		utils::time(), 
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
	utils::makeEmoteJsonArray(pluginPath);
	emit wObject->loadEmotes();
}

void PluginHelper::fullReloadEmotes()
{
	uint64* servers;
	if (ts3Functions.getServerConnectionHandlerList(&servers) == ERROR_ok)
	{
		for (size_t i = 0; servers[i] != NULL; i++)
		{
			getServerEmoteFileInfo(servers[i]);
		}
		free(servers);
	}
	utils::makeEmoteJsonArray(pluginPath);
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
QMap<unsigned short, QSharedPointer<TsClient>> PluginHelper::getAllVisibleClients(uint64 serverConnectionHandlerID)
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

void PluginHelper::serverStopped(uint64 serverConnectionHandlerID, const QString& message) const
{
	emit wObject->serverStopped(getServerId(serverConnectionHandlerID), utils::time(), message);
}

// called when client enters view by joining the same channel or by this client subscribing to a channel
void PluginHelper::clientEnteredView(uint64 serverConnectionHandlerID, anyID clientID) const
{
	auto s = servers.value(serverConnectionHandlerID);
	if (s == nullptr)
		return;

	s->addClient(clientID, getClient(serverConnectionHandlerID, clientID));
}

anyID PluginHelper::getOwnClientId(uint64 serverConnectionHandlerID)
{
	anyID id;
	if (ts3Functions.getClientID(serverConnectionHandlerID, &id) != ERROR_ok)
	{
		return 0;
	}
	return id;
}
