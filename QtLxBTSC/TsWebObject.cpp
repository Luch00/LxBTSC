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

void TsWebObject::requestEmoteJson(QString url)
{
	emit getEmoteJson(url);
}
