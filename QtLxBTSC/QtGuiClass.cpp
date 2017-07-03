#include "QtGuiClass.h"
#include "QString"
#include <QMessageBox>

QtGuiClass::QtGuiClass(QString path, QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	pathToPage = QString("file:///%1LxBTSC/template/chat.html").arg(path);
	addTab("0");
	addTab("1");
	view->setPage(tabs.value("0"));
}

QtGuiClass::~QtGuiClass()
{
	//qDeleteAll(tabs);
	//tabs.clear();
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

void QtGuiClass::switchTab(QString key)
{
	if (tabs.contains(key))
	{
		view->setPage(tabs.value(key));
	}
	else
	{
		addTab(key);
		view->setPage(tabs.value(key));
	}
}

void QtGuiClass::nicknameChanged(QString key)
{
	if (tabs.contains(key))
	{
		TsWebEnginePage *tab = tabs.take(key);
		tabs.insert(key, tab);
	}
}

void QtGuiClass::messageReceived2(QString s, QString key)
{
	//QString js = "AddServerLine(\"<div>" + s + "</div>\");";

	QString js = QString("AddServerLine('<div>%1</div>');").arg(s);

	if (tabs.contains(key))
	{
		//tabs->value(id)->page()->runJavaScript(js);
		tabs.value(key)->runJavaScript(js);
	}
	else
	{
		addTab(key);
		tabs.value(key)->addBufferLine(js);
	}
}

void QtGuiClass::addTab(QString key)
{
	//QMessageBox::information(this, "tabname", key, QMessageBox::Ok);
	TsWebEnginePage *page = new TsWebEnginePage();
	QObject::connect(page, &TsWebEnginePage::linkHovered, this, &QtGuiClass::linkHovered);
	page->setUrl(QUrl(pathToPage));
	tabs.insert(key, page);
}
