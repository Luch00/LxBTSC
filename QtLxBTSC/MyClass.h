#pragma once

#include <QObject>

class MyClass : public QObject
{
	Q_OBJECT

public:
	MyClass(QObject *parent = 0);
	~MyClass();

	public slots:
	void receive(int index);

signals:
	void changed(int);
};
