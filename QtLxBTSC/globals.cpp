/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#include "globals.h"

struct TS3Functions ts3Functions;
char returnCodeEmoteFileInfo[64];
char returnCodeEmoteFileRequest[64];
char pluginPath[PATH_BUFSIZE];
char configPath[PATH_BUFSIZE];

void logError(const QString& msg)
{
	ts3Functions.logMessage(msg.toLatin1(), LogLevel_ERROR, "BetterChat", 0);
}

void logInfo(const QString& msg)
{
	ts3Functions.logMessage(msg.toLatin1(), LogLevel_INFO, "BetterChat", 0);
}
