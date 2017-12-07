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
	void textMessageReceived(QString target, QString direction, QString time, QString name, QString message);
	void statusMessageReceived(QString target, QString time, QString type, QString message);
	void toggleEmoteMenu();
	void emoteSignal(QString e);
	void loadEmotes();
	void downloadStarted(QString message_id, int download_id);
	void downloadStartFailed(QString message_id);
	void downloadFinished(int download_id);
	void downloadCancelled(int download_id);
	void downloadFailed(int download_id);
};
