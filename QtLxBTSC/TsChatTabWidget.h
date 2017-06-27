#pragma once

#include <QObject>
#include <QtWidgets\QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QAction>
#include <qclipboard.h>
#include <QApplication>
#include <QMenu>
#include <QContextMenuEvent>

class TsChatTabWidget : public QWebEngineView
{
	Q_OBJECT

public:
	TsChatTabWidget(QWidget *parent);
	~TsChatTabWidget();
	bool isLoaded;
	void addLine(QString text);
	QList<QString> getBuffer();
	virtual void contextMenuEvent(QContextMenuEvent *e);

private:
	QList<QString> buffer;
};
