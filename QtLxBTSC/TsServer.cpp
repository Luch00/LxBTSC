#include "TsServer.h"

TsServer::TsServer(QObject *parent)	: QObject(parent), serverId_(99999), uniqueId_("DEFAULT"), safeUniqueId_("DEFAULT")
{
}

TsServer::TsServer(unsigned long long serverId, QString uniqueId, QMap<unsigned short, TsClient*> clients, QObject *parent) : QObject(parent), serverId_(serverId), uniqueId_(uniqueId), clients_(clients)
{
	QString s = uniqueId_;
	safeUniqueId_ = s.replace(QRegExp("[+/=]"), "00");
}

TsServer::TsServer(unsigned long long serverId, QString uniqueId, QObject *parent) : QObject(parent), serverId_(serverId), uniqueId_(uniqueId)
{
	QString s = uniqueId_;
	safeUniqueId_ = s.replace(QRegExp("[+/=]"), "00");
}

TsServer::~TsServer()
{
	qDeleteAll(clients_);
}

QString TsServer::uniqueId() const
{
	return uniqueId_;
}

QString TsServer::safeUniqueId() const
{
	return safeUniqueId_;
}

void TsServer::addClients(QMap<unsigned short, TsClient*> newClients)
{
	clients_ = newClients;
}

void TsServer::addClient(unsigned short clientId, TsClient* client)
{
	if (clients_.contains(clientId))
	{
		TsClient* old = clients_.take(clientId);
		delete old;
	}
	clients_.insert(clientId, client);
}

TsClient* TsServer::getClient(unsigned short clientId) const
{
	return clients_.value(clientId);
}

TsClient* TsServer::getClientByName(QString name) const
{
	for each (TsClient* client in clients_)
	{
		if (client->name() == name)
		{
			return client;
		}
	}
	return nullptr;
}

