#include "TsChatTabWidget.h"

TsChatTabWidget::TsChatTabWidget(QWidget *parent)
	: QWebEngineView(parent)
{
	isLoaded = false;
}

TsChatTabWidget::~TsChatTabWidget()
{
}

void TsChatTabWidget::addLine(QString text)
{
	buffer.append(text);
}

QList<QString> TsChatTabWidget::getBuffer()
{
	return buffer;
}
