#pragma once

#include <QObject>
#include <QtWidgets/QPlainTextEdit>

class TsTextEdit : public QPlainTextEdit
{
	Q_OBJECT

public:
	TsTextEdit(QWidget *parent);
	~TsTextEdit();

	void TsTextEdit::keyPressEvent(QKeyEvent *event)
	{
		if (event->key() == Qt::Key::Key_Return || event->key() == Qt::Key::Key_Enter)
		{
			emit textSend(this->toPlainText());
			clear();
		}
		else
		{
			QPlainTextEdit::keyPressEvent(event);
		}
	}

signals:
	void textSend(QString text);
};
