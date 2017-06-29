#pragma once

#include <QWidget>
#include <QtCore/QVariant>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/qwebenginesettings.h>
#include <QtWebEngineWidgets/qwebengineprofile.h>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QStackedWidget>
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
	void messageReceived2(QString s, QString key);
	void addTab(QString key);
	void switchTab(QString key);
	void nicknameChanged(QString key);

	QVBoxLayout *verticalLayout;
	QStackedWidget *stack;
	QWebEngineView *view;

signals:
	//void tsTextMessage(QString text, int id);

public slots:
	void tabSelected(int index);
	//void tabLoaded(int index);

private:
	//QMap<int, TsChatTabWidget*> *tabs;
	QMap<QString, TsWebEnginePage*> *tabs;
	int tabIndex;
	unsigned long long serverID;
	void setupUi(QWidget *QtGuiClass);
	QString pathToPage;
};
