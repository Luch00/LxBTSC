/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#include "TsClient.h"
#include "utils.h"

TsClient::TsClient(const QString& name, const QString& uniqueId, unsigned short clientId) 
	: name_(name)
	, uniqueId_(uniqueId)
	, safeUniqueId_(utils::ts3WeirdBase16(uniqueId))
	, clientLink_(link(clientId, uniqueId, name))
	, clientId_(clientId)
	, historyRead_(false)
{
}

TsClient::~TsClient()
{
}

void TsClient::setName(QString newName)
{
	name_ = newName;
	//clientLink_ = link();
	clientLink_ = link(clientId_, uniqueId_, name_);
}

QString TsClient::name() const
{
	return name_;
}

QString TsClient::uniqueId() const
{
	return uniqueId_;
}

QString TsClient::safeUniqueId() const
{
	return safeUniqueId_;
}

QString TsClient::clientLink() const
{
	return clientLink_;
}

bool TsClient::historyRead() const
{
	return historyRead_;
}

void TsClient::setHistoryRead()
{
	historyRead_ = true;
}