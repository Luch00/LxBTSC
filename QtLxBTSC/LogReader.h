#pragma once

#include <QFile>

class LogReader
{
public:
	static QByteArray readLog(const QString& serverUniqueID);
	static QByteArray readPrivateLog(const QString& serverUniqueID, const QString& clientUniqueID);

private:
	const static int maxBytesToRead = 524288;
	static QByteArray readFile(const QString& filePath);
	static QJsonArray parseMessages(const QByteArray& log);
};