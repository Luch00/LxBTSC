/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QObject>

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
	void textMessageReceived(QString target, QString direction, QString time, QString name, QString userlink, QString message, int mode, QString senderClient, QString receiverClient);
	void printConsoleMessage(QString target, int mode, QString client, QString message);
	void toggleEmoteMenu();
	void emoteSignal(QString e);
	void loadEmotes();
	void configChanged();

	void serverWelcomeMessage(QString target, QString time, QString message);
	void serverConnected(QString target, QString time, QString serverName);
	void serverDisconnected(QString target, QString time);
	void serverStopped(QString target, QString time, QString message);
	//void serverConnectionLost(QString target, QString time);

	void clientConnected(QString target, QString time, QString clientLink, QString clientName);
	void clientDisconnected(QString target, QString time, QString clientLink, QString clientName, QString disconnectMessage);
	void clientTimeout(QString target, QString time, QString clientLink, QString clientName);
	void clientKickedFromChannel(QString target, QString time, QString clientLink, QString name, QString kickerLink, QString kickerName, QString kickMessage);
	void clientKickedFromServer(QString target, QString time, QString clientLink, QString name, QString kickerLink, QString kickerName, QString kickMessage);
	void clientBannedFromServer(QString target, QString time, QString clientLink, QString name, QString kickerLink, QString kickerName, QString kickMessage);

	void clientMovedBySelf(QString target, QString time, QString clientLink, QString clientName, QString oldChannelLink, QString newChannelLink, QString oldChannelName, QString newChannelName);
	void clientMovedByOther(QString target, QString time, QString clientLink, QString clientName, QString moverLink, QString moverName, QString oldChannelLink, QString newChannelLink, QString oldChannelName, QString newChannelName, QString moveMessage);
	void channelCreated(QString target, QString time, QString channelLink, QString channelName, QString creatorLink, QString creatorName);
	void channelDeleted(QString target, QString time, QString channelLink, QString channelName, QString deleterLink, QString deleterName);

	void clientPoked(QString target, QString time, QString clientLink, QString clientName, QString message);

	void logRead(QString target, QByteArray log);
	void privateLogRead(QString target, QString client, QByteArray log);

private:
	bool done = false;
};
