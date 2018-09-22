/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QObject>

class TsClient : public QObject
{
	Q_OBJECT

public:
	TsClient(QString name, QString uniqueId, unsigned short clientId, QObject *parent = 0);
	~TsClient();

	QString name() const;
	QString safeUniqueId() const;
	QString uniqueId() const;
	QString clientLink() const;

	void setName(QString newName);

private:
	QString name_;
	const QString uniqueId_;
	QString safeUniqueId_;
	QString clientLink_;
	const unsigned short clientId_;

	QString link() const;
};
