/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <globals.h>
#include <QListWidget>
#include <file.h>
#include <QInputDialog>
#include <QMessageBox>

class FileTransferListWidget : public QWidget
{
	Q_OBJECT

public:
	FileTransferListWidget(QWidget *parent = 0);
	~FileTransferListWidget();

	void transferStatusChanged(anyID transferID, unsigned status);
	void setDownloadDirectory(QString dir) const;

signals:
	void showTransferCompletePop(QString filename);
	void transferComplete(unsigned short transferId);
	void transferCancelled(unsigned short transferId);
	void transferFailed();

public slots :
	void onFileUrlClicked(const QUrl &url);

private slots:
	void onPwDialogAccepted(const QString &pw);
	void onOwDialogAccepted();
	void onTransferCancelled(int id) const;
	void onClear() const;

private:
	QListWidget* list;
	QMap<anyID, File> filetransfers;
	QInputDialog* pwDialog;
	QMessageBox* owDialog;
	QLineEdit* directory;
	File temp;

	void initPwDialog();
	void initOverwriteDialog();
	void checkForPassword();
	void startDownload();
	void addTransferItem(anyID transferId, QString filename);
};
