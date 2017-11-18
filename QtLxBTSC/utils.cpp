#pragma once

#include <utils.h>
#include <QDir>
#include <qtextstream.h>

namespace utils
{
	QString direction(bool outgoing)
	{
		if (outgoing)
		{
			return "Outgoing";
		}
		return "Incoming";
	}

	QString format(QString original)
	{
		// escape newlines to not break javascript
		original.replace(QRegExp("[\r\n]"), "\\r\\n");

		// escape single quotes
		original.replace("'", "\\'");

		return original;
	}

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
}
