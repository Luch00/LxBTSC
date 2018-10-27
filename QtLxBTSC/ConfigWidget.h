/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QCheckBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QJsonObject>
#include <QPlainTextEdit>
#include <QLineEdit>

class ConfigWidget : public QWidget
{
	Q_OBJECT

public:
	ConfigWidget(const QString& path, QWidget *parent = 0);
	~ConfigWidget();

	QString getConfigAsString(const QString& key);

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
	QCheckBox* stopGifs;
	QCheckBox* avatar;
	QSpinBox* maxlines;
	QPlainTextEdit* remotes;
	QPushButton* saveButton;
	QString configPath;
	QJsonObject jsonObj;
	QLineEdit* downloadDir;

	void readConfig();
};
