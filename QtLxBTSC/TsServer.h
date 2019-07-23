/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include <globals.h>
#include "TsClient.h"

class TsServer
{

public:
	TsServer(unsigned long long serverId, const QString& uniqueId);
	~TsServer();

	QString uniqueId() const;
	QString safeUniqueId() const;
	bool connected() const;
	unsigned short myId() const;
	void setDisconnected();
	void setConnected();
	QSharedPointer<TsClient> addClient(unsigned short clientId);
	QSharedPointer<TsClient> addClient(unsigned short clientId, QSharedPointer<TsClient> client);
	QSharedPointer<TsClient> getClient(unsigned short clientId) const;
	QSharedPointer<TsClient> getClientByName(const QString& name) const;
	QString getChannelName(uint64 channelID);
	void updateClients();
	void updateOwnId();

private:
	unsigned long long serverId_;
	const QString uniqueId_;
	QString safeUniqueId_;
	bool connected_;
	unsigned short myId_;
	QMap<unsigned short, QString> clientIdCache_;
	QMap<QString, QSharedPointer<TsClient>> clients_;

	QSharedPointer<TsClient> getClientInfo(unsigned short clientId);
};
