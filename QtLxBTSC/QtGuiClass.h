#pragma once

#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/qwebenginesettings.h>
#include <QtWebEngineWidgets/qwebengineprofile.h>
#include <QtWidgets/QVBoxLayout>
#include <QStackedWidget>
#include <TsWebEnginePage.h>

class QtGuiClass : public QWidget
{
	Q_OBJECT

public:
	QtGuiClass(QString path, QWidget *parent = Q_NULLPTR);
	~QtGuiClass();
	void messageReceived2(QString s, QString key);
	void addTab(QString key);
	void switchTab(QString key);
	void nicknameChanged(QString key);

	QVBoxLayout *verticalLayout;
	QWebEngineView *view;

private:
	QMap<QString, TsWebEnginePage*> tabs;
	void setupUi(QWidget *QtGuiClass);
	QString pathToPage;
};
