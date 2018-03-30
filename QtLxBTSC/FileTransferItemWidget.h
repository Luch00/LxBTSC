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

	bool done() const;

private:
	QProgressBar* bar;
	QPushButton* button;
	unsigned short transferID;
	bool isDone = false;

public slots:
	void cancelClicked();
	void onTransferComplete(unsigned short transferId);
	void onTransferFailed(unsigned short transferId);

signals:
	void cancelTransfer(unsigned short);


};
