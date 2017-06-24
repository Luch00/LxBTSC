#include "MyClass.h"

MyClass::MyClass(QObject *parent)
	: QObject(parent)
{
}

MyClass::~MyClass()
{
}

void MyClass::receive(int index)
{
	emit changed(index);
}
