#pragma once

#include <QProgressBar>
#include <QPushButton>

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
	const unsigned short transferID;
	bool isDone = false;

public slots:
	void cancelClicked();
	void onTransferComplete(unsigned short transferId);
	void onTransferFailed(unsigned short transferId);

signals:
	void cancelTransfer(unsigned short);

};
