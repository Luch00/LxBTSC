#pragma once

#include <QWidget>
#include "ui_QtGuiClass.h"

class QtGuiClass : public QWidget
{
	Q_OBJECT

public:
	QtGuiClass(QWidget *parent = Q_NULLPTR);
	~QtGuiClass();
	void messageReceived2(QString s, int id);
	void addTab(QString name, int id);
	TsTextEdit* getTextEdit();

	//protected slots:

	//void messageReceived(QString s);

public slots:
	void textGet(QString text);
	void tabSelected(int index);

signals:
	void tsTextMessage(QString text, int id);

private:
	Ui::QtGuiClass ui;
	QMap<int, QWebEngineView*> *tabs;
	int tabIndex;
};
