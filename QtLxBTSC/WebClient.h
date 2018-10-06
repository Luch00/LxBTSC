/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

class WebClient : public QObject
{
	Q_OBJECT

public:
	WebClient(QObject *parent = 0);
	~WebClient();

signals:
	void htmlData(QString data, QString url, qulonglong messageId);
	void fileData(QString dataType, QString url, qulonglong messageId);
	void emoteJson(QString data);
	void webError(QString errorMessage);

public slots:
	void onEmbedData(const QString& url, qulonglong messageId);
	void onEmoteData(QStringList urlList);

private slots:
	void onDownloadProgress(qint64 downloadedBytes, qint64 totalBytes);

private:
	QNetworkAccessManager networkManager;
	void getEmoteJson(const QNetworkRequest& request);
};
