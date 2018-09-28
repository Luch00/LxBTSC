/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "TsServer.h"
#include <QString>

TsServer::TsServer(unsigned long long serverId, QString uniqueId, unsigned short myId, QMap<unsigned short, QSharedPointer<TsClient>> clients, QObject *parent) 
	: QObject(parent)
	, serverId_(serverId)
	, uniqueId_(uniqueId)
	, myId_(myId)
	, clients_(clients)
	, safeUniqueId_(uniqueId.toLatin1().toBase64())
	, connected_(true)
{
}

TsServer::~TsServer()
{
	clients_.clear();
}

QString TsServer::uniqueId() const
{
	return uniqueId_;
}

QString TsServer::safeUniqueId() const
{
	return safeUniqueId_;
}

bool TsServer::connected() const
{
	return connected_;
}

unsigned short TsServer::myId() const
{
	return myId_;
}

void TsServer::setDisconnected()
{
	connected_ = false;
}

void TsServer::addClients(QMap<unsigned short, QSharedPointer<TsClient>> newClients)
{
	clients_ = newClients;
}

void TsServer::addClient(unsigned short clientId, QSharedPointer<TsClient> client)
{
	if (clients_.contains(clientId))
	{
		QSharedPointer<TsClient> old = clients_.take(clientId);
	}
	clients_.insert(clientId, client);
}

QSharedPointer<TsClient> TsServer::getClient(unsigned short clientId) const
{
	return clients_.value(clientId);
}

QSharedPointer<TsClient> TsServer::getClientByName(QString name) const
{
	for (QSharedPointer<TsClient> client : clients_)
	{
		if (client->name() == name)
		{
			return client;
		}
	}
	return QSharedPointer<TsClient>(nullptr);
}

