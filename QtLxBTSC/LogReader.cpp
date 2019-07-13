#include "LogReader.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "globals.h"
#include <QRegularExpression>
#include <QBuffer>
#include <utils.h>

QByteArray LogReader::readLog(const QString& serverUniqueID)
{
	QJsonDocument doc;
	QJsonObject obj;
	const QString chatsPath = QString("%1chats/%2").arg(configPath).arg(serverUniqueID);
	QByteArray log = readFile(QString("%1/server.html").arg(chatsPath));
	QJsonArray array = parseMessages(log);
	obj.insert("server", array);

	log = readFile(QString("%1/channel.html").arg(chatsPath));
	array = parseMessages(log);
	obj.insert("channel", array);

	doc.setObject(obj);
	return doc.toJson();
}

QByteArray LogReader::readPrivateLog(const QString& serverUniqueID, const QString& clientUniqueID)
{
	QJsonDocument doc;
	QJsonObject obj;
	const QString filePath = QString("%1chats/%2/clients/%3.html").arg(configPath, serverUniqueID, clientUniqueID);
	//ts3Functions.logMessage(filePath.toLatin1(), LogLevel_DEVEL, "BetterChat", 0);
	QByteArray log = readFile(filePath);
	QJsonArray array = parseMessages(log);
	obj.insert("private", array);
	doc.setObject(obj);
	return doc.toJson();
}

QByteArray LogReader::readFile(const QString& filePath)
{
	//ts3Functions.logMessage("Opening logfile", LogLevel_DEVEL, "BetterChat", 0);
	QFile file(filePath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		ts3Functions.logMessage("LogReader: failed to open file", LogLevel_DEVEL, "BetterChat", 0);
		return "";
	}

	if (file.size() > maxBytesToRead)
	{
		file.seek(file.size() - maxBytesToRead);
	}

	QByteArray r = file.read(maxBytesToRead);
	file.close();
	return r;
}

QJsonArray LogReader::parseMessages(const QByteArray& log)
{
	//ts3Functions.logMessage("Parsing log", LogLevel_DEVEL, "BetterChat", 0);
	const static QRegularExpression re(R"(&lt;(.*)&gt;.*(client://\d+/(.+)~(.+))\">.*TextMessage_Text\">(.*?)</span>)");

	QJsonArray array;
	QBuffer buffer;
	buffer.open(QBuffer::ReadWrite);
	buffer.write(log);
	buffer.seek(0);
	//int i = 0;
	//int j = 0;
	while (buffer.canReadLine())
	{
		QByteArray line = buffer.readLine();
		QRegularExpressionMatch match = re.match(line);
		if (match.hasMatch())
		{
			QJsonObject message;
			QString time = match.captured(1);
			QString link = match.captured(2);
			QString uid = match.captured(3);
			QString name = match.captured(4);
			QString text = match.captured(5);

			message.insert("time", time);
			message.insert("link", link);
			message.insert("uid", utils::ts3WeirdBase16(uid));
			message.insert("name", name);
			message.insert("text", text);
			array.append(message);
			//++j;
		}
		//++i;
	}
	//ts3Functions.logMessage(QString::number(i).toLatin1(), LogLevel_DEVEL, "BetterChat", 0);
	//ts3Functions.logMessage(QString::number(j).toLatin1(), LogLevel_DEVEL, "BetterChat", 0);
	return array;
}
