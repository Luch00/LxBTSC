#pragma once

#include <QWidget>
#include <QCheckBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <qfile.h>
#include <QJsonDocument>
#include <QJsonObject>

class ConfigWidget : public QWidget
{
	Q_OBJECT

public:
	ConfigWidget(QString path, QWidget *parent = 0);
	~ConfigWidget();

	void open();
signals:
	void configChanged();

private slots:
	void save();

private:
	QFormLayout* formLayout;
	QCheckBox* embeds;
	QCheckBox* favicons;
	QCheckBox* emoticons;
	QSpinBox* maxlines;
	QPushButton* saveButton;
	QString configPath;
	QJsonObject jsonObj;
};
