#pragma once

#include <utils.h>
#include <QDir>
#include <QMetaMethod>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	/*int b(QChar a)
	{
		const char* base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		int b = 0;
		while (b < 64) {
			if (base64[b] == a) return b;
			b++;
		}
		return 0;
	}*/

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
		/*QString ret;uid.
		int i, o, p = 0;
		//char uniqueID[200]; 
		const char *uniqueID = uid.toLocal8Bit().constData();
		char base16[6];
		//fgets(uniqueID, 200, stdin);
		while (i = 0, p = 0, o < strlen(uniqueID) - 4) {
			i = b(uniqueID[o + 3]) | (b(uniqueID[o + 2]) << 6)
				| (b(uniqueID[o + 1]) << 12) | (b(uniqueID[o]) << 18);
			if (uniqueID[o + 3] == '=') {
				if (uniqueID[o + 2] == '=') {
					base16[3] = 0;
					p++;
					i >>= 4;
				}
				if ((i & 255) == 0) {
					base16[4] = 0;
					p++;
					i >>= 4;
				}
				base16[5] = 0;
				p++;
				i >>= 4;
			}
			while (p < 6) {
				base16[5 - p] = ('a' + (i & 15));
				i >>= 4;
				p++;
			}
			//fputs(base16, stdout);
			p = 0;
			while (p<6)
			{
				//putchar(base16[p]); 
				ret.append(base16[p]);
				p++;
			}
			o += 4;
		}
		//putchar('\n');
		return ret;*/
	}
}
