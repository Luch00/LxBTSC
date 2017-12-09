#pragma once
#include <QString>

class File
{
public:
	File() : filename_(""), size_(""), serverConnectionHandlerId_(0) {}
	File(QString filename, QString size, uint64 serverConnectionHandlerId) : filename_(filename), size_(size), serverConnectionHandlerId_(serverConnectionHandlerId) {}
	~File(){}

	QString filename() const
	{
		return filename_;
	}

	QString size() const
	{
		return size_;
	}

	uint64 serverConnectionHandlerId() const
	{
		return serverConnectionHandlerId_;
	}

	bool operator==(const File & file) const
	{
		return this->filename_.compare(file.filename()) == 0 && this->size_.compare(file.size()) == 0;
	}
private:
	QString filename_;
	QString size_;
	uint64 serverConnectionHandlerId_;
};
