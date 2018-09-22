/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "FileTransferItemWidget.h"
#include <QHBoxLayout>
#include <QLabel>

FileTransferItemWidget::FileTransferItemWidget(QString name, unsigned short transferID, QWidget *parent)
	: QWidget(parent)
	, bar(new QProgressBar(this))
	, button(new QPushButton("Cancel"))
	, transferID(transferID)
{
	bar->setMinimum(0);
	bar->setMaximum(0);
	bar->setFixedWidth(150);
	bar->setAlignment(Qt::AlignCenter);

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

void FileTransferItemWidget::onTransferComplete(unsigned short transferID)
{
	if (transferID == this->transferID && isDone == false)
	{
		isDone = true;
		button->setDisabled(true);
		bar->setFormat("Done");
		bar->setMaximum(100);
		bar->setValue(100);
	}
}

void FileTransferItemWidget::onTransferFailed(unsigned short transferID)
{
	if (transferID == this->transferID && isDone == false)
	{
		isDone = true;
		button->setDisabled(true);
		bar->setFormat("Cancelled");
		bar->setStyleSheet("QProgressBar::chunk {background-color: #E90707;}");
		bar->setMaximum(100);
		bar->setValue(100);
	}
}

void FileTransferItemWidget::cancelClicked()
{
	emit cancelTransfer(transferID);
}

bool FileTransferItemWidget::done() const
{
	return isDone;
}
