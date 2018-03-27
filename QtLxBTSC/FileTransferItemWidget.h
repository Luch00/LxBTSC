#pragma once

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QHBoxLayout>

class FileTransferItemWidget : public QWidget
{
	Q_OBJECT

public:
	FileTransferItemWidget(QString name, unsigned short transferID, QWidget *parent = 0);
	~FileTransferItemWidget();

	bool done();

private:
	QProgressBar* bar;
	QPushButton* button;
	unsigned short transferID;
	bool isDone = false;

public slots:
	void setDone();
	void cancelClicked();
	//void onTransferComplete(unsigned short transferId);

signals:
	void transferCancel(unsigned short);


};
