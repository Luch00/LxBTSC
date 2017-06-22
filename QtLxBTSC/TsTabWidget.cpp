#include "TsTabWidget.h"

TsTabWidget::TsTabWidget(QWidget *parent)
	: QWidget(parent)
{
}

TsTabWidget::TsTabWidget()
{

}

TsTabWidget::~TsTabWidget()
{
}

void TsTabWidget::browserLoaded(bool ok)
{
	int index = this->property("chatindex").toInt();
	emit tabLoaded(index);
}
