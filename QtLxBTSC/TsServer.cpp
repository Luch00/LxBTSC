#include "TsServer.h"

TsServer::TsServer(QObject *parent)	: QObject(parent), serverId_(99999), uniqueId_("DEFAULT"), myId_(999), safeUniqueId_("DEFAULT")
{
}

TsServer::TsServer(unsigned long long serverId, QString uniqueId, unsigned short myId, QMap<unsigned short, QSharedPointer<TsClient>> clients, QObject *parent) : QObject(parent), serverId_(serverId), uniqueId_(uniqueId), myId_(myId), clients_(clients)
{
	QString s = uniqueId_;
	safeUniqueId_ = QString(s.toLatin1().toBase64());
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
	for each (QSharedPointer<TsClient> client in clients_)
	{
		if (client->name() == name)
		{
			return client;
		}
	}
	return QSharedPointer<TsClient>(new TsClient());
}

