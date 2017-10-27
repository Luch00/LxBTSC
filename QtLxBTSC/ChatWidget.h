/*
* Teamspeak 3 chat plugin
* HTML chatbox using WebEngine
*
* Copyright (c) 2017 Luch
*/

#pragma once

#include <QFrame>
#include <QtWebEngineWidgets/QWebEngineView>
//#include <QtWebEngineWidgets/qwebenginesettings.h>
//#include <QtWebEngineWidgets/qwebengineprofile.h>
#include <QtWidgets/QVBoxLayout>
//#include <QWidget>
#include <TsWebEnginePage.h>
#include <QShortcut>
#include <QClipboard>
#include <QGuiApplication>
#include <QMenu>

class ChatWidget : public QFrame
{
	Q_OBJECT

public:
	ChatWidget(QString path, QWidget *parent = Q_NULLPTR);
	~ChatWidget();
	void messageReceived(QString s, QString key);
	void createPage();
	void switchTab(QString key);
	void addServer(unsigned long long);

	QVBoxLayout *verticalLayout;
	QWebEngineView *view;

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
};
