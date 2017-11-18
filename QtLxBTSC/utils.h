#pragma once
#include <QString>
#include <QRegExp>

namespace utils
{
	QString direction(bool direction);
	QString format(QString original);
	void checkEmoteSets(const QString &path);
}
