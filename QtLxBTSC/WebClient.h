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
	void onEmbedData(QString url, qulonglong messageId);
	void onEmoteData(QString url);

private slots:
	void onDownloadProgress(qint64 downloadedBytes, qint64 totalBytes);

private:
	QNetworkAccessManager networkManager;
};
