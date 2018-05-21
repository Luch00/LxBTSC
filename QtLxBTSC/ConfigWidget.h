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
#include <QPlainTextEdit>
#include <QJsonArray>
#include <QLineEdit>
#include <QFileDialog>

class ConfigWidget : public QWidget
{
	Q_OBJECT

public:
	ConfigWidget(QString path, QWidget *parent = 0);
	~ConfigWidget();

	QString getConfigAsString(QString key);

signals:
	void configChanged();

private slots:
	void save();
	void browseDirectory();

private:
	QFormLayout* formLayout;
	QCheckBox* embeds;
	QCheckBox* generics;
	QCheckBox* favicons;
	QCheckBox* emoticons;
	QCheckBox* avatar;
	QSpinBox* maxlines;
	QPlainTextEdit* remotes;
	QPushButton* saveButton;
	QString configPath;
	QJsonObject jsonObj;
	QLineEdit* downloadDir;

	void readConfig();
};
