/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QFile>

class LogReader
{
public:
	static QJsonObject readLog(const QString& serverUniqueID);
	static QJsonArray readPrivateLog(const QString& serverUniqueID, const QString& clientUniqueID);

private:
	const static int maxBytesToRead = 524288;
	static QByteArray readFile(const QString& filePath);
	static QJsonArray parseMessages(const QByteArray& log);
};