#pragma once

#include "globals.h"
#include "ChatWidget.h"
#include <QMainWindow>
#include "ConfigWidget.h"
#include "FileTransferListWidget.h"
#include "TsServer.h"
#include "WebClient.h"

class PluginHelper : public QObject
{
	Q_OBJECT

public:
	PluginHelper(QString pluginPath, QObject *parent = nullptr);
	~PluginHelper();

	void textMessageReceived(uint64 serverConnectionHandlerID, anyID fromID, anyID toID, anyID targetMode, QString senderUniqueID, QString fromName, QString message, bool outgoing) const;
	void serverConnected(uint64 serverConnectionHandlerID);
	void serverDisconnected(uint serverConnectionHandlerID) const;
	void clientConnected(uint64 serverConnectionHandlerID, anyID clientID) const;
	void clientDisconnected(uint64 serverConnectionHandlerID, anyID clientID, QString message) const;
	void clientEnteredView(uint64 serverConnectionHandlerID, anyID clientID) const;
	//void clientEnteredViewBySubscription(uint64 serverConnectionHandlerID, anyID clientID);
	void clientTimeout(uint64 serverConnectionHandlerID, anyID clientID) const;
	void clientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, QString displayName) const;
	void poked(uint64 serverConnectionHandlerID, anyID pokerID, QString pokerName, QString pokerUniqueID, QString pokeMessage) const;
	void transferStatusChanged(anyID transferID, unsigned int status) const;
	void toggleNormalChat() const;
	void reload() const;
	void reloadEmotes() const;
	void openConfig() const;
	void openTransfers() const;

	void serverStopped(uint64 serverConnectionHandlerID, QString message) const;

private slots:
	void onAppStateChanged(Qt::ApplicationState state);
	void onEmoticonAppend(QString e) const;
	void onEmoticonButtonClicked(bool c) const;
	void onTabChange(int i) const;
	void onTransferFailure() const;
	void onClientUrlClicked(const QUrl &url) const;
	void onChannelUrlClicked(const QUrl &url) const;
	void onLinkHovered(const QUrl &url) const;
	void onPrintConsoleMessageToCurrentTab(QString message) const;
	void onPrintConsoleMessage(uint64 serverConnectionHandlerID, QString message, int targetMode) const;
	void onConfigChanged() const;

private:
	QMainWindow* mainwindow;
	QTabWidget* chatTabWidget;
	QTextEdit* chatLineEdit;
	QToolButton* emoticonButton;

	TsWebObject* wObject;
	ConfigWidget* config;
	FileTransferListWidget* transfers;
	WebClient* client;
	QMenu* chatMenu;
	ChatWidget* chat;

	QMap<unsigned long long, QSharedPointer<TsServer>> servers;
	const QString pluginPath;
	Qt::ApplicationState currentState;

	void initUi();
	void insertMenu();
	void waitForLoad() const;
	QString getServerId(uint64 serverConnectionHandlerID) const;
	static QSharedPointer<TsClient> getClient(uint64 serverConnectionHandlerID, anyID id);
	static QMap<unsigned short, QSharedPointer<TsClient>> getAllClientNicks(uint64 serverConnectionHandlerID);
	static anyID getOwnClientId(uint64 serverConnectionHandlerID);
	std::tuple<int, QString, QString> getCurrentTab() const;
	std::tuple<int, QString, QString> getTab(int tabIndex) const;

	//QSharedPointer<TsServer> getCachedServer(uint64 serverConnectionHandlerID);
};
