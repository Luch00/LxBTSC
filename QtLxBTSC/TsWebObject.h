#pragma once

#include <QObject>

class TsWebObject : public QObject
{
	Q_OBJECT

public:
	TsWebObject(QObject *parent);
	~TsWebObject();
	Q_INVOKABLE void emoteClicked(QString e);
	
signals:
	void addServer(QString key);
	void tabChanged(QString key);
	void textMessageReceived(QString target, QString direction, QString time, QString name, QString userlink, QString message);
	void printConsoleMessage(QString target, QString message);
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
};
