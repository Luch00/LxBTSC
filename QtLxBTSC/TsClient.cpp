#include "TsClient.h"
#include "utils.h"

TsClient::TsClient(QObject *parent)
	: QObject(parent), uniqueId_("DEFAULT"), safeUniqueId_("DEFAULT"), clientId_(99999)
{
}

TsClient::TsClient(QString name, QString uniqueId, unsigned short clientId, QObject *parent) : QObject(parent), name_(name), uniqueId_(uniqueId), clientId_(clientId)
{
	QString s = uniqueId;
	safeUniqueId_ = utils::ts3WeirdBase16(s);
	clientLink_ = link();
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
