/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include "TsClient.h"

class TsServer : public QObject
{
	Q_OBJECT

public:
	TsServer(unsigned long long serverId, QString uniqueId, unsigned short myId, QMap<unsigned short, QSharedPointer<TsClient>> clients, QObject *parent = 0);
	~TsServer();

	QString uniqueId() const;
	QString safeUniqueId() const;
	bool connected() const;
	unsigned short myId() const;
	void setDisconnected();
	void addClients(QMap<unsigned short, QSharedPointer<TsClient>> newClients);
	void addClient(unsigned short clientId, QSharedPointer<TsClient>);
	QSharedPointer<TsClient> getClient(unsigned short clientId) const;
	QSharedPointer<TsClient> getClientByName(QString name) const;

private:
	unsigned long long serverId_;
	const QString uniqueId_;
	QString safeUniqueId_;
	bool connected_;
	unsigned short myId_;
	QMap<unsigned short, QSharedPointer<TsClient>> clients_;
};
