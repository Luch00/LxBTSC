/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "WebClient.h"
#include <QtNetwork/QNetworkReply>
#include "globals.h"

WebClient::WebClient(QObject *parent)
	: QObject(parent)
{
}

WebClient::~WebClient()
{
}

void WebClient::onEmoteData(QStringList urlList)
{
	for (const QString& url : urlList)
	{
		QNetworkRequest request;
		request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
		request.setUrl(QUrl(url));
		getEmoteJson(request);
	}
}

void WebClient::getEmoteJson(const QNetworkRequest& request)
{
	QNetworkReply* reply = networkManager.get(request);
	connect(reply, &QNetworkReply::downloadProgress, this, &WebClient::onDownloadProgress);
	connect(reply, &QNetworkReply::finished, [=]()
	{
		QNetworkReply::NetworkError headError = reply->error();
		if (headError == QNetworkReply::NoError)
		{
			emit emoteJson(reply->readAll());
		}
		else
		{
			ts3Functions.logMessage("Emote get failed", LogLevel_INFO, "BetterChat", 0);
			//getEmoteJson(reply->request()); // retry?
			emit webError("Emote load failed, try reloading");
		}
		reply->deleteLater();
	});
}

void WebClient::onEmbedData(const QString& url, qulonglong messageId)
{
	QNetworkRequest headRequest;
	headRequest.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	//headRequest.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.170 Safari/537.36 OPR/53.0.2907.57");
	headRequest.setRawHeader("User-Agent", "Twitterbot/1.0");
	headRequest.setUrl(QUrl(url));
	QNetworkReply* headReply = networkManager.head(headRequest);
	connect(headReply, &QNetworkReply::finished, [this, headReply, messageId]()
	{
		//int statusCode = headReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
		QNetworkReply::NetworkError headError = headReply->error();
		if (headError != QNetworkReply::NoError)
		{
			// head was not successful
			emit webError(headReply->errorString());
			headReply->deleteLater();
			return;
		}

		QString contentType = headReply->header(QNetworkRequest::KnownHeaders::ContentTypeHeader).toString();

		// linked content is not html
		if (!contentType.startsWith("text/html"))
		{
			emit fileData(contentType, headReply->url().toString(), messageId);
			headReply->deleteLater();
			return;
		}

		// get the html body
		QNetworkReply* getReply = networkManager.get(headReply->request());
		connect(getReply, &QNetworkReply::downloadProgress, this, &WebClient::onDownloadProgress);
		connect(getReply, &QNetworkReply::finished, [this, getReply, messageId]()
		{
			QNetworkReply::NetworkError getError = getReply->error();
			if (getError != QNetworkReply::NoError)
			{
				// get was not successful
				emit webError(getReply->errorString());
				getReply->deleteLater();
				return;
			}
			emit htmlData(getReply->readAll(), getReply->url().toString(), messageId);
			getReply->deleteLater();
		});

		headReply->deleteLater();
	});
}

void WebClient::onDownloadProgress(qint64 downloadedBytes, qint64 totalBytes)
{
	// if size is already known
	if (totalBytes > 5242880)
	{
		auto reply = static_cast<QNetworkReply*>(sender());
		reply->abort();
		return;
	}

	// else check current progress and cancel when limit is exceeded
	if (downloadedBytes > 5242880)
	{
		auto* reply = static_cast<QNetworkReply*>(sender());
		reply->abort();
	}	
}
