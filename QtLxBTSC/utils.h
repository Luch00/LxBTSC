/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <qtextstream.h>
#include <QMainWindow>

namespace utils
{
	QMainWindow* findMainWindow();
	QWidget* findWidget(QString name, QWidget* parent);
	QString time();
	void checkEmoteSets(const QString &path);
	QString ts3WeirdBase16(QString id);
}
