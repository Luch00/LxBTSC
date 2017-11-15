/*
* Teamspeak 3 chat plugin
* HTML chatbox using WebEngine
*
* Copyright (c) 2017 Luch
*/

#pragma once

#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/qwebenginesettings.h>
#include <QtWebEngineWidgets/qwebengineprofile.h>
#include <QtWidgets/QVBoxLayout>
#include <QStackedWidget>
#include <TsWebEnginePage.h>
#include <QShortcut>
#include <QClipboard>
#include <QGuiApplication>
#include <QMenu>
#include <QtWebChannel/qwebchannel.h>
#include <TsWebObject.h>

class ChatWidget : public QFrame
{
	Q_OBJECT

public:
	ChatWidget(QString path, QWidget *parent = Q_NULLPTR);
	~ChatWidget();
	void messageReceived(QString target, QString direction, QString time, QString name, QString message);
	void statusReceived(QString target, QString time, QString type, QString message);
	void createPage();
	void switchTab(QString key);
	void addServer(QString key);
	void openCloseEmoteMenu();

	QVBoxLayout *verticalLayout;
	QWebEngineView *view;
	TsWebObject *wObject;

	private slots:
	void copyActivated();
	void copyUrlActivated();
	void showContextMenu(const QPoint &);
	void linkHovered(QUrl);

private:
	TsWebEnginePage *page;
	void setupUi(QWidget *ChatWidget);
	QString pathToPage;
	QUrl currentHoveredUrl;
	QShortcut *copy;
	QAction *copyAction;
	QAction *copyUrlAction;
	QWebChannel *channel;
};
