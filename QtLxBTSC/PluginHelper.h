#pragma once

#include "globals.h"
#include <QObject>
#include "ChatWidget.h"
#include <QInputDialog>
#include <QMainWindow>
#include "file.h"
#include "server.h"
#include <QPlainTextEdit>
#include <QApplication>
#include <QToolButton>

class PluginHelper : public QObject
{
	Q_OBJECT

public:
	PluginHelper(QString pluginPath, QObject *parent = nullptr);
	~PluginHelper();

	void findChatTabWidget();
	void findChatLineEdit();
	void findMainWindow();
	void findEmoticonButton();
	void toggleNormalChat();
	void initPwDialog();
	void waitForLoad();
	void appStateChanged(Qt::ApplicationState state);

	void pwDialogAccepted(const QString pw);
	void receiveEmoticonAppend(QString e);
	void receiveEmoticonButtonClick(bool c);
	void receiveTabChange(int i);
	void recheckSelectedTab();
	void receiveTabClose(int i);
	void receiveFileUrlClick(const QUrl &url);
	void onTransferCancelled(int id);

	uint64 currentServerID;
	ChatWidget *chat;
	QInputDialog *pwDialog;
	QMainWindow *mainwindow;

	QMap<anyID, File> filetransfers;
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
	Qt::ApplicationState currentState;
};
