/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#include "TsServer.h"
#include <QString>

TsServer::TsServer(unsigned long long serverId, const QString& uniqueId) 
	: serverId_(serverId)
	, uniqueId_(uniqueId)
	, safeUniqueId_(uniqueId.toLatin1().toBase64())
	, connected_(true)
{
	updateClients();
	updateOwnId();
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

void TsServer::setConnected()
{
	connected_ = true;
}

QSharedPointer<TsClient> TsServer::addClient(unsigned short clientId)
{
	auto c = getClientInfo(clientId);
	c = addClient(clientId, c);
	return c;
}

QSharedPointer<TsClient> TsServer::addClient(unsigned short clientId, QSharedPointer<TsClient> client)
{
	clientIdCache_.insert(clientId, client->uniqueId());
	if (clients_.contains(client->uniqueId()))
	{
		auto old = clients_.value(client->uniqueId());
		old->setName(client->name());
		return old;
	}
	clients_.insert(client->uniqueId(), client);
	return client;
}

QSharedPointer<TsClient> TsServer::getClient(unsigned short clientId) const
{
	const QString uid = clientIdCache_.value(clientId);
	return clients_.value(uid);
}

QSharedPointer<TsClient> TsServer::getClientByName(const QString& name) const
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

QString TsServer::getChannelName(uint64 channelID)
{
	char* res;
	if (ts3Functions.getChannelVariableAsString(serverId_, channelID, CHANNEL_NAME, &res) != ERROR_ok)
	{
		return "unknown";
	}
	QString name = res;
	free(res);
	return name;
}

// cache all connected visible clients
void TsServer::updateClients()
{
	anyID* list;
	if (ts3Functions.getClientList(serverId_, &list) == ERROR_ok)
	{
		for (size_t i = 0; list[i] != NULL; i++)
		{
			auto c = getClientInfo(list[i]);
			clientIdCache_.insert(list[i], c->uniqueId());
			if (clients_.contains(c->uniqueId()))
			{
				clients_.value(c->uniqueId())->setName(c->name());
			}
			else
			{
				clients_.insert(c->uniqueId(), c);
			}
		}
		free(list);
	}
	else
	{
		//ts3Functions.logMessage("Failed to get clientlist", LogLevel_ERROR, "BetterChat", 0);
		logError("Failed to get clientlist");
	}
}

// Get the nickname and unique id of a client
QSharedPointer<TsClient> TsServer::getClientInfo(unsigned short clientId)
{
	char res[TS3_MAX_SIZE_CLIENT_NICKNAME];
	if (ts3Functions.getClientDisplayName(serverId_, clientId, res, TS3_MAX_SIZE_CLIENT_NICKNAME) != ERROR_ok)
	{
		//ts3Functions.logMessage("Failed to get client nickname", LogLevel_ERROR, "BetterChat", 0);
		logError("Failed to get client nickname");
	}

	char* uid;
	if (ts3Functions.getClientVariableAsString(serverId_, clientId, CLIENT_UNIQUE_IDENTIFIER, &uid) == ERROR_ok)
	{
		free(uid);
		return QSharedPointer<TsClient>(new TsClient(res, uid, clientId));
	}
	//ts3Functions.logMessage("Failed to get client unique id", LogLevel_ERROR, "BetterChat", 0);
	logError("Failed to get client unique id");
	return nullptr;
}

void TsServer::updateOwnId()
{
	anyID id;
	if (ts3Functions.getClientID(serverId_, &id) != ERROR_ok)
	{
		//ts3Functions.logMessage("Failed to get own client id", LogLevel_ERROR, "BetterChat", 0);
		logError("Failed to get own client id");
	}
	myId_ = id;
}
