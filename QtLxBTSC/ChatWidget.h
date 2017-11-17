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
	void messageReceived(const QString &target, const QString &direction, const QString &time, const QString &name, const QString &message);
	void statusReceived(const QString &target, const QString &time, const QString &type, const QString &message);
	void createPage();
	void switchTab(const QString &key);
	void addServer(const QString &key);
	void openCloseEmoteMenu();

	QVBoxLayout *verticalLayout;
	QWebEngineView *view;
	TsWebObject *wObject;

	private slots:
	void copyActivated();
	void copyUrlActivated();
	void showContextMenu(const QPoint &);
	void linkHovered(const QUrl &);

private:
	TsWebEnginePage *page;
	void setupUi(QWidget *ChatWidget);
	QString pathToPage;
	QUrl currentHoveredUrl;
	QMenu * menu;
	QShortcut *copy;
	QAction *copyAction;
	QAction *copyUrlAction;
	QWebChannel *channel;
};
