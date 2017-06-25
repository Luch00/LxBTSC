#pragma once

#include <QWidget>
#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QStackedWidget>
#include <TsTextEdit.h>
#include <TsChatTabWidget.h>
#include <TsTabWidget.h>
#include <TsWebEnginePage.h>

class QtGuiClass : public QWidget
{
	Q_OBJECT

public:
	QtGuiClass(QWidget *parent = Q_NULLPTR);
	QtGuiClass(unsigned long long serverID, QString path);
	~QtGuiClass();
	void messageReceived2(QString s, int id);
	void addTab(QString name, int id);
	TsTextEdit* getTextEdit();

	QVBoxLayout *verticalLayout;
	//QVBoxLayout *verticalLayout_2;
	//QVBoxLayout *verticalLayout_3;
	//QTabWidget *tabWidget;
	QStackedWidget *stack;
	//TsTextEdit *plainTextEdit;

signals:
	void tsTextMessage(QString text, int id);

public slots:
	void textGet(QString text);
	void tabSelected(int index);
	void tabLoaded(int index);

private:
	QMap<int, TsChatTabWidget*> *tabs;
	int tabIndex;
	unsigned long long serverID;
	void setupUi(QWidget *QtGuiClass);
	QString pathToPage;
};
