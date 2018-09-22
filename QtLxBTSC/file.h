/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QString>
#include <FileTransferItemWidget.h>

class File
{
public:
	File() 
	: filename_("")
	, size_("")
	, serverConnectionHandlerId_(0) {}

	~File(){}

	QString filename() const
	{
		return filename_;
	}

	QString size() const
	{
		return size_;
	}
	QString password() const
	{
		return password_;
	}
	QString path() const
	{
		return path_;
	}
	QString serverUId() const
	{
		return serverUId_;
	}
	quint64 serverConnectionHandlerId() const
	{
		return serverConnectionHandlerId_;
	}
	quint64 channelId() const
	{
		return channelId_;
	}
	FileTransferItemWidget* listWidget() const
	{
		return item_;
	}

	void setListWidget(FileTransferItemWidget* item)
	{
		this->item_ = item;
	}
	void setFilename(QString filename)
	{
		this->filename_ = filename;
	}
	void setSize(QString size)
	{
		this->size_ = size;
	}
	void setServerConnectionHandler(quint64 id)
	{
		this->serverConnectionHandlerId_ = id;
	}
	void setPassword(QString password)
	{
		this->password_ = password;
	}
	void setServerUId(QString id)
	{
		this->serverUId_ = id;
	}
	void setChannelId(quint64 id)
	{
		this->channelId_ = id;
	}
	void setPath(QString path)
	{
		this->path_ = path;
	}

	bool operator==(const File & file) const
	{
		return this->filename_.compare(file.filename()) == 0 && this->size_.compare(file.size()) == 0;
	}
	
private:
	QString filename_;
	QString size_;
	QString password_;
	QString path_;
	QString serverUId_;
	quint64 serverConnectionHandlerId_;
	quint64 channelId_;
	FileTransferItemWidget* item_;
};
