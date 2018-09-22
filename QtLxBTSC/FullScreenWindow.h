/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QWidget>

class QWebEngineView;

class FullScreenWindow : public QWidget
{
	Q_OBJECT

public:
	FullScreenWindow(QWebEngineView* oldView, QWidget *parent = nullptr);
	~FullScreenWindow();

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	QWebEngineView* view;
	QWebEngineView* oldView;
	QRect oldGeometry;
};
