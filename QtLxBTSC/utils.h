#pragma once
#include <QRegExp>
#include <qtextstream.h>

namespace utils
{
	QString direction(bool direction);
	QString format(QString original);
	void checkEmoteSets(const QString &path);
	void printObjectDetails(QObject *object, QTextStream &stream);
}
