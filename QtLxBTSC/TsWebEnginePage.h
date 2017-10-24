/*
* Teamspeak 3 chat plugin
* HTML chatbox using WebEngine
*
* Copyright (c) 2017 Luch
*/

#pragma once

#include <QObject>
#include <QtWebEngineWidgets\QWebEnginePage>
#include <QDesktopServices>
#include <QShortcut>

class TsWebEnginePage : public QWebEnginePage
{
	Q_OBJECT

public:
	TsWebEnginePage(QObject *parent = 0);
	~TsWebEnginePage();
	
	// clicked links open in external browser
	bool acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool isMainFrame)
	{
		if (type == QWebEnginePage::NavigationType::NavigationTypeLinkClicked && isMainFrame == true)
		{
			QDesktopServices::openUrl(url);
			return false;
		}
		return true;
	}

private:
	QShortcut *copy;
};
