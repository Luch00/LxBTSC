#pragma once

#include <QObject>
#include <QtCore/QVariant>
#include <QtWidgets/QWidget>

class TsTabWidget : public QWidget
{
	Q_OBJECT

public:
	TsTabWidget(QWidget *parent);
	TsTabWidget();
	~TsTabWidget();

	public slots:
	void browserLoaded(bool ok);

signals:
	void tabLoaded(int id);
};
