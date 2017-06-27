#pragma once

#include <QObject>
#include <QtWebEngineWidgets\QWebEnginePage>
#include <QDesktopServices>
#include <QAction>
#include <QMenu>
#include <QApplication>
#include <QClipboard>
#include <QContextMenuEvent>

class TsWebEnginePage : public QWebEnginePage
{
	Q_OBJECT

public:
	TsWebEnginePage(QObject *parent = 0);
	~TsWebEnginePage();
	virtual void contextMenuEvent(QContextMenuEvent *e);
	
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

public slots:
	void copied(bool);

private:
	QAction *copy;
};
