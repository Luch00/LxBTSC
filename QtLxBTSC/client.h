#pragma once

#include <QString>

class Client
{
public:
	Client() : nickname_(""), uid_("") {}
	Client(QString nickname, QString uid, unsigned short id)
	{
		this->id_ = id;
		this->nickname_ = nickname;
		this->uid_ = uid;
		this->safe_uid_ = uid.replace(QRegExp("[+/=]"), "00");
	}
	~Client(){}

	void Client::set_nickname(QString nickname)
	{
		nickname_ = nickname;
	}

	QString Client::nickname() const
	{
		return nickname_;
	}

	QString Client::uid() const
	{
		return uid_;
	}

	QString Client::safe_uid() const
	{
		return safe_uid_;
	}

	QString Client::link() const
	{
		return QString("client://%1/%2~%3").arg(QString::number(id_), uid_, nickname_.toHtmlEscaped());
	}

private:
	QString nickname_;
	QString uid_;
	QString safe_uid_;
	unsigned short id_;
};
