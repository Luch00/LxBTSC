#include "TsWebEnginePage.h"

TsWebEnginePage::TsWebEnginePage(QObject *parent)
	: QWebEnginePage(parent)
{
	copy = this->action(QWebEnginePage::Copy);
	copy->setText("Copy");
	copy->setShortcut(QKeySequence::Copy);
	QObject::connect(copy, &QAction::triggered, this, &TsWebEnginePage::copied);
}

TsWebEnginePage::~TsWebEnginePage()
{
}

void TsWebEnginePage::copied(bool b)
{
	QClipboard *cb = QApplication::clipboard();
	cb->setText(this->selectedText(), QClipboard::Clipboard);
}

void TsWebEnginePage::contextMenuEvent(QContextMenuEvent *event)
{
	//QMenu *menu = this->createStandardContextMenu();
	QMenu *menu = new QMenu();
	menu->addAction(copy);
	menu->popup(event->globalPos());
	//const QList<QAction*> actions = menu->actions();
}
