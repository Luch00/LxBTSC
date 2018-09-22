/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QProgressBar>
#include <QPushButton>

class FileTransferItemWidget : public QWidget
{
	Q_OBJECT

public:
	FileTransferItemWidget(QString name, unsigned short transferID, QWidget *parent = 0);
	~FileTransferItemWidget();

	bool done() const;

private:
	QProgressBar* bar;
	QPushButton* button;
	const unsigned short transferID;
	bool isDone = false;

public slots:
	void cancelClicked();
	void onTransferComplete(unsigned short transferId);
	void onTransferFailed(unsigned short transferId);

signals:
	void cancelTransfer(unsigned short);

};
