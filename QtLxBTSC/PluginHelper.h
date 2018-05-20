#pragma once

#include "globals.h"
#include <QObject>
#include "ChatWidget.h"
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QApplication>
#include <QToolButton>
#include <QMetaMethod>
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

	void currentServerChanged(uint64 serverConnectionHandlerID);
	void textMessageReceived(uint64 serverConnectionHandlerID, anyID fromID, anyID toID, anyID targetMode, QString senderUniqueID, QString fromName, QString message, bool outgoing);
	void serverConnected(uint64 serverConnectionHandlerID);
	void serverDisconnected(uint serverConnectionHandlerID);
	void clientConnected(uint64 serverConnectionHandlerID, anyID clientID);
	void clientDisconnected(uint64 serverConnectionHandlerID, anyID clientID, QString message);
	void clientEnteredView(uint64 serverConnectionHandlerID, anyID clientID) const;
	//void clientEnteredViewBySubscription(uint64 serverConnectionHandlerID, anyID clientID);
	void clientTimeout(uint64 serverConnectionHandlerID, anyID clientID);
	void clientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, QString displayName) const;
	void poked(uint64 serverConnectionHandlerID, anyID pokerID, QString pokerName, QString pokerUniqueID, QString pokeMessage);
	void transferStatusChanged(anyID transferID, unsigned int status);
	void toggleNormalChat() const;
	void recheckSelectedTab();
	void reload() const;
	void reloadEmotes() const;
	void openConfig() const;
	void openTransfers() const;

	void serverStopped(uint64 serverConnectionHandlerID, QString message);

private slots:
	void onAppStateChanged(Qt::ApplicationState state);
	void onEmoticonAppend(QString e) const;
	void onEmoticonButtonClicked(bool c) const;
	void onTabChange(int i);
	void onTabClose(int i);
	void onTransferCompleted(QString filename) const;
	void onTransferFailure() const;
	void onClientUrlClicked(const QUrl &url);
	void onChannelUrlClicked(const QUrl &url);
	void onLinkHovered(const QUrl &url);
	void onPrintConsoleMessageToCurrentTab(QString message);
	void onPrintConsoleMessage(uint64 serverConnectionHandlerID, QString message, int targetMode);
	void onConfigChanged() const;

private:
	QMainWindow* mainwindow;
	QTabWidget* chatTabWidget;
	QTextEdit* chatLineEdit;
	QToolButton* emoticonButton;
	QMetaObject::Connection c;
	QMetaObject::Connection d;
	QMetaObject::Connection e;
	QMetaObject::Connection g;

	ChatWidget* chat;
	ConfigWidget* config;
	FileTransferListWidget* transfers;
	WebClient* client;
	TsWebObject* wObject;

	//uint64 currentServerID;
	QMap<unsigned long long, QSharedPointer<TsServer>> servers;
	QString pathToPlugin;
	bool first = true;
	Qt::ApplicationState currentState;
	QString currentTabName;

	void initUi();
	void waitForLoad() const;
	void disconnect() const;
	//QString getMessageTarget(uint64 serverConnectionHandlerID, anyID targetMode, anyID clientID);
	QString getServerId(uint64 serverConnectionHandlerID);
	//QSharedPointer<TsClient> getOrCreateClient(uint64 serverConnectionHandlerID, anyID clientID, QString fromName, QString senderUniqueID);
	QMainWindow* findMainWindow() const;
	static QWidget* findWidget(QString name, QWidget* parent);
	static QSharedPointer<TsClient> getClient(uint64 serverConnectionHandlerID, anyID id);
	static QMap<unsigned short, QSharedPointer<TsClient>> getAllClientNicks(uint64 serverConnectionHandlerID);
	void dynamicConnect(const QString &signalName, const QString &slotName);
	static QString time();
	anyID getOwnClientId(uint64 serverConnectionHandlerID) const;
};
