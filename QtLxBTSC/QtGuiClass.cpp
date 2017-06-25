#include "QtGuiClass.h"

QtGuiClass::QtGuiClass(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	tabs = new QMap<int, TsChatTabWidget*>();
	addTab("Server", -2);
	addTab("Channel", -1);
}

QtGuiClass::QtGuiClass(unsigned long long server, QString path)
	: QWidget()
{
	setupUi(this);
	serverID = server;
	pathToPage = QString("file:///%1LxBTSC/template/chat.html").arg(path);
	tabs = new QMap<int, TsChatTabWidget*>();
	addTab("Server", -2);
	addTab("Channel", -1);
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
	stack = new QStackedWidget(QtGuiClass);
	stack->setObjectName(QStringLiteral("myStack"));
	
	verticalLayout->addWidget(stack);

	QtGuiClass->setWindowTitle(QApplication::translate("QtGuiClass", "QtGuiClass", 0));

	stack->setCurrentIndex(0);

	QMetaObject::connectSlotsByName(QtGuiClass);
}

void QtGuiClass::tabSelected(int index)
{
	stack->setCurrentIndex(index);
	tabIndex = stack->currentWidget()->property("chatindex").toInt();
}

void QtGuiClass::tabLoaded(int index)
{
	foreach(QString s, tabs->value(index)->getBuffer())
	{
		tabs->value(index)->page()->runJavaScript(s);
	}
	tabs->value(index)->isLoaded = true;
}

//void QtGuiClass::textGet(QString text)
//{
//	emit tsTextMessage(text, tabIndex);
//}

void QtGuiClass::messageReceived2(QString s, int id)
{
	QString js = "AddServerLine('<div>" + s + "</div>');";

	if (tabs->contains(id))
	{
		tabs->value(id)->page()->runJavaScript(js);
	}
	else
	{
		addTab("Private", id);
		tabs->value(id)->addLine(js);
	}
}

void QtGuiClass::addTab(QString name, int id)
{
	TsTabWidget *tab = new TsTabWidget();
	QObject::connect(tab, &TsTabWidget::tabLoaded, this, &QtGuiClass::tabLoaded);
	tab->setProperty("chatindex", id);
	tab->setObjectName(QStringLiteral("tab"));
	QVBoxLayout *verticalLayout_2 = new QVBoxLayout(tab);
	verticalLayout_2->setSpacing(1);
	verticalLayout_2->setContentsMargins(1, 1, 1, 1);
	verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

	TsChatTabWidget *webEngineView = new TsChatTabWidget(tab);

	// for some reason this causes a crash on exit?
	webEngineView->setPage(new TsWebEnginePage());
	
	QObject::connect(webEngineView, &TsChatTabWidget::loadFinished, tab, &TsTabWidget::browserLoaded);
	webEngineView->setObjectName(QStringLiteral("webEngineView"));
	//webEngineView->setUrl(QUrl(QStringLiteral("file:///C:/Users/TURSAS/AppData/Roaming/TS3Client/plugins/LxBTSC/template/chat.html")));
	webEngineView->setUrl(QUrl(pathToPage));
	verticalLayout_2->addWidget(webEngineView);
	tabs->insert(id, webEngineView);
	stack->addWidget(tab);
}
