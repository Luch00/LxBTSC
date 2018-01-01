#pragma once

#include "globals.h"
#include <QObject>
#include "ChatWidget.h"
#include <QInputDialog>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QApplication>
#include <QToolButton>
#include <QMetaMethod>
#include "file.h"
#include "server.h"

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
	void clientTimeout(uint64 serverConnectionHandlerID, anyID clientID);
	void clientDisplayNameChanged(uint64 serverConnectionHandlerID, anyID clientID, QString displayName);
	void transferStatusChanged(anyID transferID, unsigned int status);
	void toggleNormalChat() const;
	void recheckSelectedTab();
	void reload() const;
	void reloadEmotes() const;

	void onDebugMessage(QString message);

private slots:
	void onAppStateChanged(Qt::ApplicationState state);
	void onPwDialogAccepted(const QString pw);
	void onEmoticonAppend(QString e) const;
	void onEmoticonButtonClicked(bool c) const;
	void onTabChange(int i);
	void onTabClose(int i);
	void onFileUrlClicked(const QUrl &url);
	void onTransferCancelled(int id) const;
	void onClientUrlClicked(const QUrl &url);
	void onChannelUrlClicked(const QUrl &url);
	void onLinkHovered(const QUrl &url);
	void onPrintConsoleMessageToCurrentTab(QString message);
	void onPrintConsoleMessage(uint64 serverConnectionHandlerID, QString message, int targetMode);

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
	QInputDialog* pwDialog;

	uint64 currentServerID;
	QMap<anyID, File> filetransfers;
	QMap<uint64, Server> servers;
	QString pathToPlugin;
	bool first = true;
	Qt::ApplicationState currentState;
	QString currentTabName;

	void initUi();
	void initPwDialog();
	void waitForLoad() const;
	void disconnect() const;
	QString getMessageTarget(uint64 serverConnectionHandlerID, anyID targetMode, anyID clientID);
	QMainWindow* findMainWindow() const;
	static QWidget* findWidget(QString name, QWidget* parent);
	static Client getClient(uint64 serverConnectionHandlerID, anyID id);
	static QMap<unsigned short, Client> getAllClientNicks(uint64 serverConnectionHandlerID);
	void dynamicConnect(const QString &signalName, const QString &slotName);
	QString time();
};
