#include "TsWebEnginePage.h"

TsWebEnginePage::TsWebEnginePage(QObject *parent)
	: QWebEnginePage(parent)
{
	QObject::connect(this, &TsWebEnginePage::loadFinished, this, &TsWebEnginePage::loaded);
}

TsWebEnginePage::~TsWebEnginePage()
{
}

void TsWebEnginePage::addBufferLine(QString line)
{
	buffer.append(line);
}

void TsWebEnginePage::loaded(bool loaded)
{
	foreach(QString line, buffer)
	{
		runJavaScript(line);
	}
}
