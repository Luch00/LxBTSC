/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QWebEngineView>
#include <QVBoxLayout>
#include <QFrame>
#include <TsWebEnginePage.h>
#include <QMenu>
#include <QtWebChannel/qwebchannel.h>
#include <TsWebObject.h>
#include <QWebEngineFullScreenRequest>
#include "FullScreenWindow.h"

class ChatWidget : public QFrame
{
	Q_OBJECT

public:
	ChatWidget(const QString& path, TsWebObject* webObject, QWidget *parent = Q_NULLPTR);
	~ChatWidget();
	void reload() const;

	signals:
	void fileUrlClicked(const QUrl &url);
	void clientUrlClicked(const QUrl &url);
	void channelUrlClicked(const QUrl &url);
	void linkHovered(const QUrl &url);

	private slots:
	void onCopyActivated() const;
	void onCopyUrlActivated() const;
	void onShowContextMenu(const QPoint &) const;
	void onLinkHovered(const QUrl &);
	void onFullScreenRequested(QWebEngineFullScreenRequest request);

private:
	QVBoxLayout* verticalLayout;
	QWebEngineView* view;
	QScopedPointer<FullScreenWindow> fullScreenWindow;
	TsWebObject* wObject;
	TsWebEnginePage* page;
	const QString pathToPage;
	QUrl currentHoveredUrl;
	QMenu* menu;
	QAction* copyAction;
	QAction* copyUrlAction;
	QWebChannel* channel;
	bool loadComplete;

	void setupPage() const;
	void keyReleaseEvent(QKeyEvent* event) override;

	void waitloop() const;
};
