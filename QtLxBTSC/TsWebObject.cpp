/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "TsWebObject.h"

TsWebObject::TsWebObject(QObject *parent)
	: QObject(parent)
{
}

TsWebObject::~TsWebObject()
{
}

void TsWebObject::emoteClicked(QString e)
{
	emit emoteSignal(e);
}

void TsWebObject::requestEmbedData(QString url, qulonglong messageId)
{
	emit getEmbedData(url, messageId);
}

void TsWebObject::requestEmoteJson(QStringList url)
{
	emit getEmoteJson(url);
}

void TsWebObject::setDone(bool value)
{
	done = value;
}

bool TsWebObject::getDone() const
{
	return done;
}
