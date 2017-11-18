#pragma once
#include "client.h"
#include <teamspeak/public_rare_definitions.h>
#include <QMap>

class Server
{
public:
	Server(QString uid, QMap<anyID, Client> clients)
	{
		this->clients_ = clients;
		this->uid_ = uid;
		this->safe_uid_ = uid.replace(QRegExp("[+/=]"), "0");
	}
	Server() : uid_("") {}
	~Server() {}

	void Server::set_clients(QMap<anyID, Client> clients)
	{
		clients_ = clients;
	}

	void Server::add_client(anyID clientID, Client client)
	{
		clients_.insert(clientID, client);
	}

	// this is the uid teamspeak uses
	QString Server::uid() const
	{
		return uid_;
	}

	// this uid works in html by replacing bad characters
	QString Server::safe_uid() const
	{
		return safe_uid_;
	}

	Client Server::get_client(anyID clientID) const
	{
		return clients_.value(clientID);
	}

	Client Server::get_client_by_nickname(const QString &nickname) const
	{
		for each (const Client & c in clients_)
		{
			if (c.nickname() == nickname)
			{
				return c;
			}
		}
		return Client("", "");
	}

	bool operator==(const Server & server) const
	{
		return this->uid_ == server.uid();
	}

private:
	QMap<anyID, Client> clients_;
	QString uid_;
	QString safe_uid_;
};
