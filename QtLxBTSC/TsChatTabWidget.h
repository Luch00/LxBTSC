#pragma once

#include <QObject>
#include <QtWidgets\QWidget>
#include <QtWebEngineWidgets/QWebEngineView>

class TsChatTabWidget : public QWebEngineView
{
	Q_OBJECT

public:
	TsChatTabWidget(QWidget *parent);
	~TsChatTabWidget();
	bool isLoaded;
	void addLine(QString text);
	QList<QString> getBuffer();

private:
	QList<QString> buffer;
};
