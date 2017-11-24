/*
* Teamspeak 3 chat plugin
* HTML chatbox using WebEngine
*
* Copyright (c) 2017 Luch
*/

#include "ChatWidget.h"

ChatWidget::ChatWidget(QString path, QWidget *parent)
	: QFrame(parent)
{
	setupUi(this);
	pathToPage = QString("file:///%1LxBTSC/template/chat.html").arg(path);
	createPage();
	view->setPage(page);
}

ChatWidget::~ChatWidget()
{
}

void ChatWidget::setupUi(QWidget *ChatWidget)
{
	if (ChatWidget->objectName().isEmpty())
		ChatWidget->setObjectName(QStringLiteral("ChatWidget"));
	verticalLayout = new QVBoxLayout(ChatWidget);
	verticalLayout->setSpacing(1);
	verticalLayout->setContentsMargins(1, 1, 1, 1);
	verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	view = new QWebEngineView(ChatWidget);

	view->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	menu = new QMenu(this);
	copy = new QShortcut(QKeySequence::Copy, view);
	copyAction = new QAction("Copy", this);
	copyUrlAction = new QAction("Copy Link", this);

	QObject::connect(copyAction, &QAction::triggered, this, &ChatWidget::copyActivated);
	QObject::connect(copyUrlAction, &QAction::triggered, this, &ChatWidget::copyUrlActivated);
	QObject::connect(view, &QWebEngineView::customContextMenuRequested, this, &ChatWidget::showContextMenu);
	QObject::connect(copy, &QShortcut::activated, this, &ChatWidget::copyActivated);

	verticalLayout->addWidget(view);
}

void ChatWidget::showContextMenu(const QPoint &p)
{
	menu->clear();
	if (view->hasSelection())
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

void ChatWidget::linkHovered(const QUrl &u)
{
	currentHoveredUrl = u;
}

void ChatWidget::onFileUrlClicked(const QUrl & url)
{
	emit fileUrlClicked(url);
}

void ChatWidget::copyActivated()
{
	QGuiApplication::clipboard()->setText(view->selectedText(), QClipboard::Clipboard);
}

void ChatWidget::copyUrlActivated()
{
	QGuiApplication::clipboard()->setText(currentHoveredUrl.toString(), QClipboard::Clipboard);
}

void ChatWidget::createPage()
{
	page = new TsWebEnginePage();
	page->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
	page->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
	page->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
	QObject::connect(page, &TsWebEnginePage::linkHovered, this, &ChatWidget::linkHovered);
	QObject::connect(page, &TsWebEnginePage::fileUrlClicked, this, &ChatWidget::onFileUrlClicked);
	page->setUrl(QUrl(pathToPage));
	channel = new QWebChannel(page);

	page->setWebChannel(channel);
	wObject = new TsWebObject(channel);
	channel->registerObject("wObject", wObject);
}