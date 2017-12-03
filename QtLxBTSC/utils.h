#pragma once
#include <qtextstream.h>

namespace utils
{
	QString direction(bool direction);
	void checkEmoteSets(const QString &path);
	void printObjectDetails(QObject *object, QTextStream &stream);
}
