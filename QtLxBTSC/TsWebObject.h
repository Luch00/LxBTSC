/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QObject>
#include <QJsonObject>

class TsWebObject : public QObject
{
	Q_OBJECT

public:
	TsWebObject(QObject *parent);
	~TsWebObject();
	Q_INVOKABLE void emoteClicked(QString e);
	Q_INVOKABLE bool getDone() const;
	Q_PROPERTY(bool done READ getDone WRITE setDone);
	void setDone(bool);
	
signals:
	void addServer(QString key);
	void tabChanged(QString key, int mode, QString client);
	void toggleEmoteMenu();
	void emoteSignal(QString e);
	void loadEmotes();
	void configChanged();

	void sendMessage(QJsonObject json);

private:
	bool done = false;
};
