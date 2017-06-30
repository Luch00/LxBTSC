#pragma once

#include <QObject>
#include <QtWebEngineWidgets\QWebEnginePage>
#include <QDesktopServices>

class TsWebEnginePage : public QWebEnginePage
{
	Q_OBJECT

public:
	TsWebEnginePage(QObject *parent = 0);
	~TsWebEnginePage();
	void addBufferLine(QString);
	
	// clicked links open in external browser
	bool acceptNavigationRequest(const QUrl & url, QWebEnginePage::NavigationType type, bool isMainFrame)
	{
		if (type == QWebEnginePage::NavigationType::NavigationTypeLinkClicked && isMainFrame == true)
		{
			QDesktopServices::openUrl(url);
			return false;
		}
		/*if (isMainFrame == true)
		{
			QDesktopServices::openUrl(url);
			return false;
		}*/
		return true;
	}

public slots:
	void loaded(bool);

private:
	QList<QString> buffer;
};
