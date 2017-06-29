#include "TsWebEnginePage.h"

TsWebEnginePage::TsWebEnginePage(QObject *parent)
	: QWebEnginePage(parent)
{
	//copy = this->action(QWebEnginePage::Copy);
	//copy->setText("Copy");
	//copy->setShortcut(QKeySequence::Copy);
	//QObject::connect(copy, &QAction::triggered, this, &TsWebEnginePage::copied);
	QObject::connect(this, &TsWebEnginePage::loadFinished, this, &TsWebEnginePage::loaded);
}

TsWebEnginePage::~TsWebEnginePage()
{
}
void TsWebEnginePage::setIndex(int i)
{
	index = i;
}
int TsWebEnginePage::getIndex()
{
	return index;
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
	//emit pageLoaded(index);
}
//
//void TsWebEnginePage::copied(bool b)
//{
//	QClipboard *cb = QApplication::clipboard();
//	cb->setText(this->selectedText(), QClipboard::Clipboard);
//}

//void TsWebEnginePage::contextMenuEvent(QContextMenuEvent *event)
//{
//	//QMenu *menu = this->createStandardContextMenu();
//	//QMenu *menu = new QMenu();
//	//menu->addAction(copy);
//	//menu->popup(event->globalPos());
//	//const QList<QAction*> actions = menu->actions();
//}
