/*
* Teamspeak 3 chat plugin
* HTML chatbox using WebEngine
*
* Copyright (c) 2017 Luch
*/

#pragma once

//#include <QObject>
#include <QtWebEngineWidgets/QWebEnginePage>
#include <QDesktopServices>

class TsWebEnginePage : public QWebEnginePage
{
	Q_OBJECT

public:
	TsWebEnginePage(QObject *parent = 0);
	~TsWebEnginePage();
	
	// clicked links open in external browser
	bool acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool isMainFrame) override
	{
		if (type == NavigationTypeLinkClicked && isMainFrame == true)
		{
			if (url.scheme() == "ts3file")
			{
				emit fileUrlClicked(url);
				return false;
			}
			if (url.scheme() == "client")
			{
				emit clientUrlClicked(url);
				return false;
			}
			if (url.scheme() == "channelid")
			{
				emit channelUrlClicked(url);
				return false;
			}
			QDesktopServices::openUrl(url);
			return false;
		}
		return true;
	}

	// required to open links from iframes
	QWebEnginePage* TsWebEnginePage::createWindow(WebWindowType type) override
	{
		return new TsWebEnginePage();
	}

	signals:
	void fileUrlClicked(const QUrl url);
	void clientUrlClicked(const QUrl url);
	void channelUrlClicked(const QUrl url);
};
