/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "TsClient.h"
#include "utils.h"

TsClient::TsClient(QString name, QString uniqueId, unsigned short clientId, QObject *parent) 
	: QObject(parent)
	, name_(name)
	, uniqueId_(uniqueId)
	, safeUniqueId_(utils::ts3WeirdBase16(uniqueId))
	, clientLink_(link())
	, clientId_(clientId)
{
}

TsClient::~TsClient()
{
}

QString TsClient::link() const
{
	return QString("client://%1/%2~%3").arg(QString::number(clientId_), uniqueId_, name_.toHtmlEscaped());
}

void TsClient::setName(QString newName)
{
	name_ = newName;
	clientLink_ = link();
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
