/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QObject>

class TsClient
{

public:
	TsClient(const QString& name, const QString& uniqueId, unsigned short clientId);
	~TsClient();

	QString name() const;
	QString safeUniqueId() const;
	QString uniqueId() const;
	QString clientLink() const;
	bool historyRead() const;
	void setHistoryRead();

	void setName(QString newName);

	static QString link(unsigned short clientId, const QString& uniqueId, const QString& name)
	{
		return QString("client://%1/%2~%3").arg(QString::number(clientId), uniqueId, name.toHtmlEscaped());
	}

private:
	QString name_;
	const QString uniqueId_;
	QString safeUniqueId_;
	QString clientLink_;
	const unsigned short clientId_;
	bool historyRead_;
};
