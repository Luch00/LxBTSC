/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "ChatWidget.h"
#include "FileTransferListWidget.h"
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QWebEngineSettings>


ChatWidget::ChatWidget(QString path, TsWebObject* webObject, QWidget *parent)
    : QFrame(parent)
	, wObject(webObject)
	, pathToPage(QString("file:///%1LxBTSC/template/chat.html").arg(path))
	, view(new QWebEngineView(this))
	, verticalLayout(new QVBoxLayout(this))
	, menu(new QMenu(view))
	, copyAction(new QAction("Copy", this))
	, copyUrlAction(new QAction("Copy Link", this))
	, page(new TsWebEnginePage(view))
	, channel(new QWebChannel(page))
{
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("ChatWidget"));
	this->setStyleSheet("border: 1px solid gray");

	verticalLayout->setSpacing(1);
	verticalLayout->setContentsMargins(1, 1, 1, 1);
	verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	verticalLayout->addWidget(view);

	view->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	connect(copyAction, &QAction::triggered, this, &ChatWidget::onCopyActivated);
	connect(copyUrlAction, &QAction::triggered, this, &ChatWidget::onCopyUrlActivated);
	connect(view, &QWebEngineView::customContextMenuRequested, this, &ChatWidget::onShowContextMenu);
	connect(view, &QWebEngineView::loadFinished, this, [=]() { ts3Functions.logMessage("Page load finished", LogLevel_INFO, "BetterChat", 0); });

	setupPage();
	view->setPage(page);
}

ChatWidget::~ChatWidget()
{
}

void ChatWidget::setupPage() const
{
	//page->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
	page->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
	page->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
	page->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);

	connect(page, &TsWebEnginePage::fullScreenRequested, this, &ChatWidget::onFullScreenRequested);
	connect(page, &TsWebEnginePage::linkHovered, this, &ChatWidget::onLinkHovered);
	connect(page, &TsWebEnginePage::fileUrlClicked, this, &ChatWidget::fileUrlClicked);
	connect(page, &TsWebEnginePage::clientUrlClicked, this, &ChatWidget::clientUrlClicked);
	connect(page, &TsWebEnginePage::channelUrlClicked, this, &ChatWidget::channelUrlClicked);

	page->setWebChannel(channel);
	channel->registerObject("wObject", wObject);
	ts3Functions.logMessage("Page load start", LogLevel_INFO, "BetterChat", 0);
	page->load(QUrl(pathToPage));
}

void ChatWidget::keyReleaseEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_C && QApplication::keyboardModifiers().testFlag(Qt::ControlModifier) == true)
	{
		onCopyActivated();
		return;
	}
	QFrame::keyReleaseEvent(event);
}

void ChatWidget::onShowContextMenu(const QPoint &p) const
{	
	menu->clear();
	if (page->hasSelection())
	{
		menu->addAction(copyAction);
	}
	if (currentHoveredUrl.isEmpty() == false)
	{
		menu->addAction(copyUrlAction);
	}
	if (menu->actions().isEmpty() == false)
	{
		menu->popup(view->mapToGlobal(p));
	}
}

void ChatWidget::onLinkHovered(const QUrl &u)
{
	currentHoveredUrl = u;
	emit linkHovered(u);
}

void ChatWidget::onCopyActivated() const
{
	QGuiApplication::clipboard()->setText(page->selectedText(), QClipboard::Clipboard);
}

void ChatWidget::onCopyUrlActivated() const
{
	QGuiApplication::clipboard()->setText(currentHoveredUrl.toString(), QClipboard::Clipboard);
}

void ChatWidget::reload() const
{
	view->reload();
}

void ChatWidget::onFullScreenRequested(QWebEngineFullScreenRequest request)
{
	if (request.toggleOn())
	{
		if (fullScreenWindow)
			return;
		request.accept();
		fullScreenWindow.reset(new FullScreenWindow(view));
	}
	else
	{
		if (!fullScreenWindow)
			return;
		request.accept();
		fullScreenWindow.reset();
	}
}
