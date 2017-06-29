#include "QtGuiClass.h"
#include "QString"
#include <QMessageBox>

QtGuiClass::QtGuiClass(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	//tabs = new QMap<int, TsChatTabWidget*>();
	addTab("0");
	addTab("1");
}

QtGuiClass::QtGuiClass(unsigned long long server, QString path)
	: QWidget()
{
	setupUi(this);
	serverID = server;
	pathToPage = QString("file:///%1LxBTSC/template/chat.html").arg(path);
	tabs = new QMap<QString, TsWebEnginePage*>();
	addTab("0");
	addTab("1");
	view->setPage(tabs->value("0"));
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
	QWebEngineProfile::defaultProfile()->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
	//stack = new QStackedWidget(QtGuiClass);
	//stack->setObjectName(QStringLiteral("myStack"));
	
	verticalLayout->addWidget(view);
	//verticalLayout->addWidget(stack);

	//QtGuiClass->setWindowTitle(QApplication::translate("QtGuiClass", "QtGuiClass", 0));

	//stack->setCurrentIndex(0);

	//QMetaObject::connectSlotsByName(QtGuiClass);
}

void QtGuiClass::tabSelected(int index)
{
	
	if (index == 0)
	{
		index = -2;
	}
	else if (index == 1)
	{
		index = -1;
	}
	/*if (tabs->contains(index))
	{
		view->setPage(tabs->value(index));
	}
	tabIndex = tabs->value(index)->getIndex();*/
}

void QtGuiClass::switchTab(QString key)
{
	if (tabs->contains(key))
	{
		view->setPage(tabs->value(key));
	}
	else
	{
		addTab(key);
		view->setPage(tabs->value(key));
	}
}

void QtGuiClass::nicknameChanged(QString key)
{
	if (tabs->contains(key))
	{
		TsWebEnginePage *tab = tabs->take(key);
		tabs->insert(key, tab);
	}
}

//void QtGuiClass::tabLoaded(int index)
//{
//	foreach(QString s, tabs->value(index)->getBuffer())
//	{
//		tabs->value(index)->page()->runJavaScript(s);
//	}
//	tabs->value(index)->isLoaded = true;
//}

void QtGuiClass::messageReceived2(QString s, QString key)
{
	//QString js = "AddServerLine(\"<div>" + s + "</div>\");";

	QString js = QString("AddServerLine('<div>%1</div>');").arg(s);

	if (tabs->contains(key))
	{
		//tabs->value(id)->page()->runJavaScript(js);
		tabs->value(key)->runJavaScript(js);
	}
	else
	{
		addTab(key);
		tabs->value(key)->addBufferLine(js);
	}
}

void QtGuiClass::addTab(QString key)
{
	//TsTabWidget *tab = new TsTabWidget();
	QWidget *tab = new QWidget(this);
	//QObject::connect(tab, &TsTabWidget::tabLoaded, this, &QtGuiClass::tabLoaded);
	//tab->setProperty("chatindex", id);
	tab->setObjectName(QStringLiteral("tab"));
	QVBoxLayout *verticalLayout_2 = new QVBoxLayout(tab);
	verticalLayout_2->setSpacing(1);
	verticalLayout_2->setContentsMargins(1, 1, 1, 1);
	verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
	
	//TsChatTabWidget *webEngineView = new TsChatTabWidget(tab);

	// for some reason this causes a crash on exit?
	TsWebEnginePage *page = new TsWebEnginePage();
	//page->setIndex(id);

	//QObject::connect(page, &TsWebEnginePage::pageLoaded, this, &QtGuiClass::tabLoaded);
	page->setUrl(QUrl(pathToPage));
	//webEngineView->setPage(page);
	//webEngineView->setPage(new TsWebEnginePage());
	
	//QObject::connect(webEngineView, &TsChatTabWidget::loadFinished, tab, &TsTabWidget::browserLoaded);
	//webEngineView->setObjectName(QStringLiteral("webEngineView"));
	//webEngineView->setUrl(QUrl(QStringLiteral("file:///C:/Users/TURSAS/AppData/Roaming/TS3Client/plugins/LxBTSC/template/chat.html")));
	//webEngineView->setUrl(QUrl(pathToPage));
	//verticalLayout_2->addWidget(webEngineView);
	tabs->insert(key, page);
	//stack->addWidget(tab);
}
