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

//void TsChatTabWidget::contextMenuEvent(QContextMenuEvent *event)
//{
//	//QMenu *menu = this->createStandardContextMenu();
//	QMenu *menu = new QMenu();
//	menu->addAction(page()->action(TsWebEnginePage::Copy));
//	menu->addAction(page()->action(TsWebEnginePage::WebAction::CopyLinkToClipboard));
//	menu->popup(event->globalPos());
//	//const QList<QAction*> actions = menu->actions();
//}
