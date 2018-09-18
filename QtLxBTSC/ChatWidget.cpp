/*
* Teamspeak 3 chat plugin
* HTML chatbox using WebEngine
*
* Copyright (c) 2017 Luch
*/

#include "ChatWidget.h"
#include "FileTransferListWidget.h"
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QWebEngineSettings>


ChatWidget::ChatWidget(QString path, TsWebObject* webObject, QWidget *parent)
	: QFrame(parent)
{
	setupUi();
	pathToPage = QString("file:///%1LxBTSC/template/chat.html").arg(path);
	wObject = webObject;
	createPage();
	view->setPage(page);
}

ChatWidget::~ChatWidget()
{
}

void ChatWidget::setupUi()
{
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("ChatWidget"));

	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(1);
	verticalLayout->setContentsMargins(1, 1, 1, 1);
	verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	view = new QWebEngineView(this);
	verticalLayout->addWidget(view);
	view->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	menu = new QMenu(view);
	copyAction = new QAction("Copy", this);
	copyUrlAction = new QAction("Copy Link", this);

	connect(copyAction, &QAction::triggered, this, &ChatWidget::onCopyActivated);
	connect(copyUrlAction, &QAction::triggered, this, &ChatWidget::onCopyUrlActivated);
	connect(view, &QWebEngineView::customContextMenuRequested, this, &ChatWidget::onShowContextMenu);
	connect(view, &QWebEngineView::loadFinished, this, &ChatWidget::chatLoaded);
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

void ChatWidget::onShowContextMenu(const QPoint &p)
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

void ChatWidget::onCopyActivated()
{
	QGuiApplication::clipboard()->setText(page->selectedText(), QClipboard::Clipboard);
}

void ChatWidget::onCopyUrlActivated()
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

void ChatWidget::createPage()
{
	page = new TsWebEnginePage(view);
	//page->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
	page->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
	page->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
	page->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);
	connect(page, &TsWebEnginePage::fullScreenRequested, this, &ChatWidget::onFullScreenRequested);
	connect(page, &TsWebEnginePage::linkHovered, this, &ChatWidget::onLinkHovered);
	connect(page, &TsWebEnginePage::fileUrlClicked, this, &ChatWidget::fileUrlClicked);
	connect(page, &TsWebEnginePage::clientUrlClicked, this, &ChatWidget::clientUrlClicked);
	connect(page, &TsWebEnginePage::channelUrlClicked, this, &ChatWidget::channelUrlClicked);
	//page->setUrl(QUrl(pathToPage));
	channel = new QWebChannel(page);
	page->setWebChannel(channel);
	//wObject = new TsWebObject(channel);
	channel->registerObject("wObject", wObject);
	page->load(QUrl(pathToPage));
}


