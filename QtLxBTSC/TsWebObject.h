#pragma once

#include <QObject>

class TsWebObject : public QObject
{
	Q_OBJECT

public:
	TsWebObject(QObject *parent);
	~TsWebObject();
	Q_INVOKABLE void emoteClicked(QString e);
	Q_INVOKABLE void requestEmbedData(QString url, qulonglong messageId);
	Q_INVOKABLE void requestEmoteJson(QString url);
	
signals:
	void addServer(QString key);
	void tabChanged(QString key, int mode, QString client);
	void textMessageReceived(QString target, QString direction, QString time, QString name, QString userlink, QString message, int mode, QString senderClient, QString receiverClient);
	void printConsoleMessage(QString target, int mode, QString client, QString message);
	void toggleEmoteMenu();
	void emoteSignal(QString e);
	void loadEmotes();
	void configChanged();

	void serverWelcomeMessage(QString target, QString time, QString message);
	void serverConnected(QString target, QString time, QString serverName);
	void serverDisconnected(QString target, QString time);
	void serverStopped(QString target, QString time, QString message);
	//void serverConnectionLost(QString target, QString time);

	void clientConnected(QString target, QString time, QString clientLink, QString clientName);
	void clientDisconnected(QString target, QString time, QString clientLink, QString clientName, QString disconnectMessage);
	void clientTimeout(QString target, QString time, QString clientLink, QString clientName);

	void clientPoked(QString target, QString time, QString clientLink, QString clientName, QString message);

	void downloadFailed();

	void getEmbedData(QString url, qulonglong messageId);
	void getEmoteJson(QString url);


	void htmlData(QString data, QString url, qulonglong messageId);
	void fileData(QString dataType, QString url, qulonglong messageId);
	void emoteJson(QString json);
	void webError(QString errorMessage);
};
