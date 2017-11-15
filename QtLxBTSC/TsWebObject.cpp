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
