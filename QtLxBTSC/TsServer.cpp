#include "TsServer.h"

TsServer::TsServer(QObject *parent)	: QObject(parent), serverId_(99999), uniqueId_("DEFAULT"), safeUniqueId_("DEFAULT")
{
}

TsServer::TsServer(unsigned long long serverId, QString uniqueId, QMap<unsigned short, QSharedPointer<TsClient>> clients, QObject *parent) : QObject(parent), serverId_(serverId), uniqueId_(uniqueId), clients_(clients)
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
	for each (QSharedPointer<TsClient> client in clients_)
	{
		if (client->name() == name)
		{
			return client;
		}
	}
	return QSharedPointer<TsClient>(new TsClient());
}

