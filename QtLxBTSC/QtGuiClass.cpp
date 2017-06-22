#include "QtGuiClass.h"

QtGuiClass::QtGuiClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QObject::connect(ui.tabWidget, &QTabWidget::currentChanged, this, &QtGuiClass::tabSelected);
	QObject::connect(ui.plainTextEdit, &TsTextEdit::textSend, this, &QtGuiClass::textGet);
	tabs = new QMap<int, TsChatTabWidget*>();
	addTab("Server", -2);
	addTab("Channel", -1);
	//tabIndex = -2;
}

QtGuiClass::~QtGuiClass()
{
}

TsTextEdit* QtGuiClass::getTextEdit()
{
	return ui.plainTextEdit;
}

void QtGuiClass::tabSelected(int index)
{
	tabIndex = ui.tabWidget->currentWidget()->property("chatindex").toInt();
	//tabIndex = index;
}

void QtGuiClass::textGet(QString text)
{
	emit tsTextMessage(text, tabIndex);
}

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
		//tabs->value(id)->page()->runJavaScript(js);
		tabs->value(id)->addLine(js);
	}
}

void QtGuiClass::tabLoaded(int index)
{
	foreach(QString s, tabs->value(index)->getBuffer())
	{
		tabs->value(index)->page()->runJavaScript(s);
	}
	tabs->value(index)->isLoaded = true;
}

void QtGuiClass::addTab(QString name, int id)
{
	//QWebEnginePage *page = new QWebEnginePage();
	//page->setu
	//QWidget *tab = new QWidget();
	TsTabWidget *tab = new TsTabWidget();
	QObject::connect(tab, &TsTabWidget::tabLoaded, this, &QtGuiClass::tabLoaded);
	tab->setProperty("chatindex", id);
	tab->setObjectName(QStringLiteral("tab"));
	QVBoxLayout *verticalLayout_2 = verticalLayout_2 = new QVBoxLayout(tab);
	verticalLayout_2->setSpacing(1);
	verticalLayout_2->setContentsMargins(1, 1, 1, 1);
	verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
	//QWebEngineView *webEngineView = webEngineView = new QWebEngineView(tab);
	TsChatTabWidget *webEngineView = webEngineView = new TsChatTabWidget(tab);
	QObject::connect(webEngineView, &TsChatTabWidget::loadFinished, tab, &TsTabWidget::browserLoaded);
	webEngineView->setObjectName(QStringLiteral("webEngineView"));
	webEngineView->setUrl(QUrl(QStringLiteral("file:///C:/Users/TURSAS/AppData/Roaming/TS3Client/plugins/LxBTSC/template/chat.html")));
	//webEngineView->setu
	verticalLayout_2->addWidget(webEngineView);
	tabs->insert(id, webEngineView);
	ui.tabWidget->addTab(tab, name);
}
