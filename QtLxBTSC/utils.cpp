/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <utils.h>
#include <QDirIterator>
#include <QApplication>
#include <QTime>

namespace utils
{
	// find mainwindow of ts
	QMainWindow* findMainWindow()
	{
		foreach(QWidget *widget, qApp->topLevelWidgets())
		{
			if (QMainWindow* m = qobject_cast<QMainWindow*>(widget))
			{
				return m;
			}
		}
		return nullptr;
	}

	// find widget by object name
	QWidget* findWidget(const QString& name, QWidget* parent)
	{
		QList<QWidget*> children = parent->findChildren<QWidget*>();
		for (int i = 0; i < children.count(); ++i)
		{
			if (children[i]->objectName() == name)
			{
				return children[i];
			}
		}
		return nullptr;
	}

	// get current time as string
	QString time()
	{
		return QTime::currentTime().toString("hh:mm:ss");
	}
	
	/*void checkEmoteSets(const QString& path)
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
	}*/

	// make a list of all local emotesets so javascript can load them
	void makeEmoteJsonArray(const QString& path)
	{
		QString json;
		QDir emotePath(path + "LxBTSC/template/Emotes", "*.json", QDir::NoSort, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
		QDirIterator it(emotePath, QDirIterator::Subdirectories);
		if (it.hasNext())
		{
			json = "[\"";
			QStringList files;
			while (it.hasNext())
			{
				it.next();
				QFileInfo fileInfo(it.fileInfo());
				files.append(emotePath.relativeFilePath(fileInfo.filePath()));
			}
			json.append(files.join("\",\""));
			json.append("\"]");
		}
		else
		{
			json = "[]";
		}

		QFile file(path + "LxBTSC/template/emotesets.json");
		if (file.open(QIODevice::WriteOnly))
		{
			QTextStream stream(&file);
			stream << json << endl;
		}
	}

	// string used for avatar filenames
	QString ts3WeirdBase16(const QString& uid)
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
