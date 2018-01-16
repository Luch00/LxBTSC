#pragma once
#include <qtextstream.h>

namespace utils
{
	void checkEmoteSets(const QString &path);
	void printObjectDetails(QObject *object, QTextStream &stream);
}
