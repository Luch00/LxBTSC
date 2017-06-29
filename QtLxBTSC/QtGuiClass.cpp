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
	QWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
	
	
	verticalLayout->addWidget(view);
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
	TsWebEnginePage *page = new TsWebEnginePage();
	page->setUrl(QUrl(pathToPage));
	tabs.insert(key, page);
}
