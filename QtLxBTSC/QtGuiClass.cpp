#include "QtGuiClass.h"
#include "QString"
#include <QMessageBox>

QtGuiClass::QtGuiClass(QString path, QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	pathToPage = QString("file:///%1LxBTSC/template/chat.html").arg(path);
	createPage();
	view->setPage(page);
}

QtGuiClass::~QtGuiClass()
{
}

void QtGuiClass::setupUi(QWidget *QtGuiClass)
{
	if (QtGuiClass->objectName().isEmpty())
		QtGuiClass->setObjectName(QStringLiteral("QtGuiClass"));
	QtGuiClass->resize(636, 534);
	verticalLayout = new QVBoxLayout(QtGuiClass);
	verticalLayout->setSpacing(1);
	verticalLayout->setContentsMargins(1, 1, 1, 1);
	verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
	view = new QWebEngineView(QtGuiClass);
	view->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
	copy = new QShortcut(QKeySequence::Copy, view);
	copyAction = new QAction("Copy", this);
	copyUrlAction = new QAction("Copy Link", this);
	
	QObject::connect(copyAction, &QAction::triggered, this, &QtGuiClass::copyActivated);
	QObject::connect(copyUrlAction, &QAction::triggered, this, &QtGuiClass::copyUrlActivated);
	QObject::connect(view, &QWebEngineView::customContextMenuRequested, this, &QtGuiClass::showContextMenu);
	QObject::connect(copy, &QShortcut::activated, this, &QtGuiClass::copyActivated);
	
	verticalLayout->addWidget(view);
}

void QtGuiClass::showContextMenu(const QPoint &p)
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

void QtGuiClass::linkHovered(QUrl u)
{
	currentHoveredUrl = u;
}

void QtGuiClass::copyActivated()
{
	QString s = view->selectedText();
	QGuiApplication::clipboard()->setText(s, QClipboard::Clipboard);
}

void QtGuiClass::copyUrlActivated()
{
	QGuiApplication::clipboard()->setText(currentHoveredUrl.toString(), QClipboard::Clipboard);
}

void QtGuiClass::addServer(unsigned long long serverId)
{
	page->runJavaScript(QString("AddServer('%1');").arg(serverId));
}

void QtGuiClass::switchTab(QString key)
{
	//QMessageBox::information(0, "debug", QString("tab_change: %1").arg(key), QMessageBox::Ok);
	page->runJavaScript(QString("ShowTarget('%1');").arg(key));
}

void QtGuiClass::nicknameChanged(QString key)
{
	/*if (tabs.contains(key))
	{
		TsWebEnginePage *tab = tabs.take(key);
		tabs.insert(key, tab);
	}*/
}

void QtGuiClass::messageReceived2(QString s, QString key)
{
	QString js = QString("AddLine('%1', '<div>%2</div>');").arg(key, s);
	page->runJavaScript(js);
}

void QtGuiClass::createPage()
{
	//QMessageBox::information(this, "tabname", key, QMessageBox::Ok);
	page = new TsWebEnginePage();
	QObject::connect(page, &TsWebEnginePage::linkHovered, this, &QtGuiClass::linkHovered);
	page->setUrl(QUrl(pathToPage));
}
