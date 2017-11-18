#pragma once

#include <QString>

class Client
{
public:
	Client() : nickname_(""), uid_("") {}
	Client(QString nickname, QString uid)
	{
		this->nickname_ = nickname;
		this->uid_ = uid;
		this->safe_uid_ = uid.replace(QRegExp("[+/=]"), "0");
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

private:
	QString nickname_;
	QString uid_;
	QString safe_uid_;
};
