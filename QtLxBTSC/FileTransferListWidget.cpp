/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "FileTransferListWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>
#include <QStandardPaths>
#include <QUrlQuery>

FileTransferListWidget::FileTransferListWidget(QWidget *parent)
	: QWidget(parent)
	, list(new QListWidget)
	, directory(new QLineEdit(""))
{
	initPwDialog();
	initOverwriteDialog();
	this->setWindowTitle("Better Chat File Transfers");
	QLabel* title = new QLabel("Transfers:");
	QPushButton* button = new QPushButton("Clear");
	connect(button, &QPushButton::clicked, this, &FileTransferListWidget::onClear);
	directory->setDisabled(true);
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(title);
	layout->addWidget(list);
	layout->addWidget(directory);
	layout->addWidget(button);
	this->setLayout(layout);
	this->setMinimumWidth(400);
}

FileTransferListWidget::~FileTransferListWidget()
{
}

void FileTransferListWidget::setDownloadDirectory(QString dir) const
{
	directory->setText(dir);
}

void FileTransferListWidget::onClear() const
{
	QList<QListWidgetItem*> toDelete;
	for (int i = 0; i < list->count(); ++i)
	{
		QListWidgetItem* item = list->item(i);
		FileTransferItemWidget* fileItem = qobject_cast<FileTransferItemWidget*>(list->itemWidget(item));
		if (fileItem->done())
		{
			toDelete.append(item);
		}
	}
	for (QListWidgetItem* item : toDelete)
	{
		delete item;
	}
}

void FileTransferListWidget::addTransferItem(anyID transferId, QString filename)
{
	FileTransferItemWidget* item = new FileTransferItemWidget(filename, transferId);
	filetransfers[transferId].setListWidget(item);
	connect(item, &FileTransferItemWidget::cancelTransfer, this, &FileTransferListWidget::onTransferCancelled);
	connect(this, &FileTransferListWidget::transferComplete, item, &FileTransferItemWidget::onTransferComplete);
	connect(this, &FileTransferListWidget::transferCancelled, item, &FileTransferItemWidget::onTransferFailed);
	QListWidgetItem* listitem = new QListWidgetItem(list);
	listitem->setSizeHint(item->minimumSizeHint());
	list->addItem(listitem);
	list->setItemWidget(listitem, item);
}

// called when 'ok' is pressed in password dialog
void FileTransferListWidget::onPwDialogAccepted(const QString &pw)
{
	temp.setPassword(pw);
	startDownload();
}

void FileTransferListWidget::onOwDialogAccepted()
{
	checkForPassword();
}

// set up the dialog for file transfer passwords
void FileTransferListWidget::initPwDialog()
{
	pwDialog = new QInputDialog(this);
	pwDialog->setInputMode(QInputDialog::TextInput);
	pwDialog->setLabelText("Password");
	pwDialog->setTextEchoMode(QLineEdit::Password);
	connect(pwDialog, &QInputDialog::textValueSelected, this, &FileTransferListWidget::onPwDialogAccepted);
	pwDialog->setModal(true);
}

void FileTransferListWidget::initOverwriteDialog()
{
	owDialog = new QMessageBox(this);
	owDialog->setText("File exists");
	owDialog->setInformativeText("Overwrite?");
	QPushButton* okButton = new QPushButton("OK");
	owDialog->addButton(okButton, QMessageBox::AcceptRole);
	owDialog->setStandardButtons(QMessageBox::Cancel);
	owDialog->setModal(true);
	owDialog->setDefaultButton(okButton);
	connect(okButton, &QPushButton::clicked, this, &FileTransferListWidget::onOwDialogAccepted);
}

// user clicked cancel on transfer
void FileTransferListWidget::onTransferCancelled(int id) const
{
	if (filetransfers.contains(id))
	{
		File f = filetransfers.value(id);
		ts3Functions.haltTransfer(f.serverConnectionHandlerId(), id, 1, nullptr);
	}
}

void FileTransferListWidget::onFileUrlClicked(const QUrl &url)
{
	if (url.hasQuery())
	{
		QUrlQuery query;
		query.setQuery(url.query());
		QString filename = query.queryItemValue("filename", QUrl::FullyDecoded);
		QString size = query.queryItemValue("size", QUrl::FullyDecoded);
		QString serveruid = query.queryItemValue("serverUID", QUrl::FullyDecoded);
		QString filepath = query.queryItemValue("path", QUrl::FullyDecoded);
		QString channelid = query.queryItemValue("channel", QUrl::FullyDecoded);

		File file;
		file.setFilename(filename);
		file.setSize(size);
		file.setServerUId(serveruid);
		file.setPath(filepath);
		file.setChannelId(channelid.toULongLong());

		if (filetransfers.values().contains(file))
		{
			// this file is already being transferred -> cancel
			return;
		}

		// check if file of same name already on disk
		QString dir = directory->text();
		if (dir.isEmpty())
		{
			dir = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DownloadLocation);
			directory->setText(dir);
		}

		temp = file;

		if (QFile::exists(dir + "/" + filename))
		{
			// ask for overwrite
			owDialog->show();
			return;
		}

		checkForPassword();
	}
}

void FileTransferListWidget::checkForPassword()
{
	// get serverconnectionhandlerid for this file
	uint64 schi = NULL;
	uint64* idList;
	if (ts3Functions.getServerConnectionHandlerList(&idList) != ERROR_ok)
	{
		// failed to get connected servers -> cancel
		return;
	}
	for (size_t i = 0; idList[i] != NULL; i++)
	{
		char *uid;
		if (ts3Functions.getServerVariableAsString(idList[i], VIRTUALSERVER_UNIQUE_IDENTIFIER, &uid) != ERROR_ok)
		{
			// failed to get server uid -> cancel
			return;
		}
		if (QString(uid) == temp.serverUId())
		{
			schi = idList[i];
		}
		free(uid);

	}
	free(idList);

	if (schi == NULL)
	{
		// failed to get serverconnectionhandlerid -> cancel 
		return;
	}
	temp.setServerConnectionHandler(schi);

	// CHECK FOR PASSWORD REQUIREMENT
	int has_password = 0;
	if (ts3Functions.getChannelVariableAsInt(schi, temp.channelId(), CHANNEL_FLAG_PASSWORD, &has_password) != ERROR_ok)
	{
		// failed to get channel information -> cancel
		return;
	}
	
	if (has_password == 1)
	{
		pwDialog->show();
		return;
	}
	temp.setPassword("");
	startDownload();
}

void FileTransferListWidget::startDownload()
{
	QString full_path;
	if (temp.path() == "/")
	{
		full_path = QString("/%1").arg(temp.filename());
	}
	else
	{
		full_path = QString("%1/%2").arg(temp.path(), temp.filename());
	}
	std::string std_filepath = full_path.toStdString();
	QString download_path = directory->text();
	if (download_path.isEmpty())
	{
		download_path = QStandardPaths::writableLocation(QStandardPaths::StandardLocation::DownloadLocation);
		directory->setText(download_path);
	}
	std::string std_download_path = download_path.toStdString();
	std::string std_password = temp.password().toStdString();

	anyID res;
	if (ts3Functions.requestFile(temp.serverConnectionHandlerId(), temp.channelId(), std_password.c_str(), std_filepath.c_str(), 1, 0, std_download_path.c_str(), &res, nullptr) == ERROR_ok)
	{
		filetransfers.insert(res, temp);
		addTransferItem(res, temp.filename());
		this->show();
	}
	else
	{
		emit transferFailed();
	}
}

// called when file transfer ends in some way
void FileTransferListWidget::transferStatusChanged(anyID transferID, unsigned status)
{
	if (filetransfers.contains(transferID))
	{
		File file = filetransfers.take(transferID);
		switch (status)
		{
			case ERROR_file_transfer_complete:
			{
					emit transferComplete(transferID);
					emit showTransferCompletePop(file.filename());
					break;
			}
			case ERROR_file_transfer_canceled:
			{
				emit transferCancelled(transferID);
				break;
			}
			default:
			{
				emit transferCancelled(transferID);
				emit transferFailed();
				break;
			}
		}
	}
}
