#pragma once

#include <utils.h>
#include <QDir>
#include <QMetaMethod>

namespace utils
{
	void checkEmoteSets(const QString &path)
	{
		QDir directory(path + "LxBTSC/template/Emotes");
		QStringList f = directory.entryList(QStringList("*.json"), QDir::Files, QDir::NoSort);
		QString json;
		if (f.isEmpty())
		{
			json = "[]";
		}
		else
		{
			json = "[\"";
			json.append(f.join("\",\""));
			json.append("\"]");
		}

		QFile file(path + "LxBTSC/template/emotesets.json");
		if (file.open(QIODevice::WriteOnly))
		{
			QTextStream stream(&file);
			stream << json << endl;
		}
	}

	QString ts3WeirdBase16(QString uid)
	{
		QString hexArray = "0123456789abcdef";
		QString replaceArray = "abcdefghijklmnop";
		QByteArray hex = QByteArray::fromBase64(uid.toLatin1()).toHex();
		QString str(hex);
		QString ret;
		for (QChar c : str)
		{
			int i = hexArray.indexOf(c);
			ret.append(replaceArray[i]);
		}
		return ret;
	}
}
