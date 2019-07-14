/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#pragma once

#include <qtextstream.h>
#include <QMainWindow>

namespace utils
{
	QMainWindow* findMainWindow();
	QWidget* findWidget(const QString& name, QWidget* parent);
	QString time();
	void makeEmoteJsonArray(const QString& path);
	QString ts3WeirdBase16(const QString& id);
}
