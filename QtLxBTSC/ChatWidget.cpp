/*
* Teamspeak 3 chat plugin
* HTML chatbox using WebEngine
*
* Copyright (c) 2017 Luch
*/

#include "ChatWidget.h"
#include "QString"
//#include <QMessageBox>

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
	QMenu *menu = new QMenu(this);
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

void ChatWidget::linkHovered(QUrl u)
{
	currentHoveredUrl = u;
}

void ChatWidget::copyActivated()
{
	QString s = view->selectedText();
	QGuiApplication::clipboard()->setText(s, QClipboard::Clipboard);
}

void ChatWidget::copyUrlActivated()
{
	QGuiApplication::clipboard()->setText(currentHoveredUrl.toString(), QClipboard::Clipboard);
}

void ChatWidget::addServer(unsigned long long serverId)
{
	page->runJavaScript(QString("AddServer('%1');").arg(serverId));
}

void ChatWidget::switchTab(QString key)
{
	//QMessageBox::information(0, "debug", QString("tab_change: %1").arg(key), QMessageBox::Ok);
	page->runJavaScript(QString("ShowTarget('%1');").arg(key));
}

//void ChatWidget::messageReceived(QString s, QString key)
//{
//	QString js = QString("AddLine('%1', '<div>%2</div>');").arg(key, s);
//	page->runJavaScript(js);
//}

void ChatWidget::messageReceived(QString target, QString direction, QString time, QString name, QString message)
{
	QString js = QString("AddLine('%1', '%2', '%3', '%4', '%5');").arg(target, direction, time, name, message);
	page->runJavaScript(js);
}

void ChatWidget::statusReceived(QString target, QString time, QString type, QString message)
{
	QString js = QString("AddStatusLine('%1', '%2', '%3', '%4');").arg(target, time, type, message);
	page->runJavaScript(js);
}

void ChatWidget::createPage()
{
	page = new TsWebEnginePage();
	page->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
	page->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
	QObject::connect(page, &TsWebEnginePage::linkHovered, this, &ChatWidget::linkHovered);
	page->setUrl(QUrl(pathToPage));
}
