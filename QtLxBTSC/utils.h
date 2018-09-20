#pragma once

#include <qtextstream.h>
#include <QMainWindow>

namespace utils
{
	QMainWindow* findMainWindow();
	QWidget* findWidget(QString name, QWidget* parent);
	QString time();
	void checkEmoteSets(const QString &path);
	QString ts3WeirdBase16(QString id);
}
