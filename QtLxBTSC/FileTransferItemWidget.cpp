#include "FileTransferItemWidget.h"

FileTransferItemWidget::FileTransferItemWidget(QString name, unsigned short transferID, QWidget *parent)
	: QWidget(parent)
{
	this->transferID = transferID;
	bar = new QProgressBar(this);
	bar->setMinimum(0);
	bar->setMaximum(0);
	bar->setFixedWidth(150);
	bar->setAlignment(Qt::AlignCenter);
	button = new QPushButton("Cancel");
	button->setFixedWidth(50);
	connect(button, &QPushButton::clicked, this, &FileTransferItemWidget::cancelClicked);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(new QLabel(name));
	layout->addWidget(bar);
	layout->addWidget(button);
	this->setLayout(layout);
	this->setToolTip(name);
}

FileTransferItemWidget::~FileTransferItemWidget()
{
}

void FileTransferItemWidget::setDone()
{	
	isDone = true;
	button->setDisabled(true);
	bar->setFormat("Done");
	bar->setMaximum(100);
	bar->setValue(100);
}

/*void FileTransferItemWidget::onTransferComplete(unsigned short transferID)
{
	if (transferID == this->transferID && isDone == false)
	{
		isDone = true;
		button->setDisabled(true);
		bar->setFormat("Done");
		bar->setMaximum(100);
		bar->setValue(100);
	}
}*/

void FileTransferItemWidget::cancelClicked()
{
	isDone = true;
	button->setDisabled(true);
	bar->setFormat("Cancelled");
	bar->setStyleSheet("QProgressBar::chunk {background-color: #E90707;}");
	bar->setMaximum(100);
	bar->setValue(100);
	emit transferCancel(transferID);
}

bool FileTransferItemWidget::done()
{
	return isDone;
}
