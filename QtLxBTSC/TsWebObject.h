#pragma once

#include <QObject>

class TsWebObject : public QObject
{
	Q_OBJECT

public:
	TsWebObject(QObject *parent);
	~TsWebObject();
	Q_INVOKABLE void emoteClicked(QString e);
	Q_INVOKABLE void cancelTransfer(int download_id);
	
signals:
	void addServer(QString key);
	void tabChanged(QString key);
	void textMessageReceived(QString target, QString direction, QString time, QString name, QString userlink, QString message);
	//void statusMessageReceived(QString target, QString time, QString type, QString message, bool parseBBCode);
	void printConsoleMessage(QString target, QString message);
	void toggleEmoteMenu();
	void emoteSignal(QString e);
	void transferCancelled(int download_id);
	void loadEmotes();

	void serverWelcomeMessage(QString target, QString time, QString message);
	void serverConnected(QString target, QString time, QString serverName);
	void serverDisconnected(QString target, QString time);

	void clientConnected(QString target, QString time, QString clientLink, QString clientName);
	void clientDisconnected(QString target, QString time, QString clientLink, QString clientName, QString disconnectMessage);
	void clientTimeout(QString target, QString time, QString clientLink, QString clientName);

	void downloadStarted(QString message_id, int download_id);
	void downloadStartFailed(QString message_id);
	void downloadFinished(int download_id);
	void downloadCancelled(int download_id);
	void downloadFailed(int download_id);
};
