#pragma once
#include <QString>

class File
{
public:
	File() : filename_(""), size_("") {}
	File(QString filename, QString size) : filename_(filename), size_(size)	{}
	~File(){}

	QString filename() const
	{
		return filename_;
	}

	QString size() const
	{
		return size_;
	}

	bool operator==(const File & file) const
	{
		return this->filename_.compare(file.filename()) == 0 && this->size_.compare(file.size()) == 0;
	}
private:
	QString filename_;
	QString size_;
};
