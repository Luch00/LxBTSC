/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "FullScreenWindow.h"
#include <QWebEngineView>
#include <QAction>

FullScreenWindow::FullScreenWindow(QWebEngineView* oldView, QWidget *parent)
	: QWidget(parent)
	, view(new QWebEngineView(this))
	, oldView(oldView)
	, oldGeometry(oldView->window()->geometry())
{
	auto exitAction = new QAction(this);
	exitAction->setShortcut(Qt::Key_Escape);
	connect(exitAction, &QAction::triggered, [this]() { view->triggerPageAction(QWebEnginePage::ExitFullScreen); });
	addAction(exitAction);
	view->setPage(oldView->page());
	setGeometry(oldGeometry);
	showFullScreen();
	oldView->window()->hide();
}

FullScreenWindow::~FullScreenWindow()
{
	oldView->setPage(view->page());
	oldView->window()->setGeometry(oldGeometry);
	oldView->window()->show();
	hide();
}

void FullScreenWindow::resizeEvent(QResizeEvent* event)
{
	QRect viewGeometry(QPoint(0, 0), size());
	view->setGeometry(viewGeometry);

	QWidget::resizeEvent(event);
}

