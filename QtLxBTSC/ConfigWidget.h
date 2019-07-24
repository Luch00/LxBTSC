/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
*/

#pragma once

#include <QCheckBox>
#include <QSpinBox>
#include <QFormLayout>
#include <QPushButton>
#include <QJsonObject>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QTabWidget>

class ConfigWidget : public QWidget
{
	Q_OBJECT

public:
	ConfigWidget(const QString& path, QWidget *parent = 0);
	~ConfigWidget();

	QString getConfigAsString(const QString& key);
	bool getConfigAsBool(const QString& key);

signals:
	void configChanged();

private slots:
	void save();
	void browseDirectory();

private:
	QTabWidget* tabWidget;
	QFormLayout* configLayout;
	// general tab
	QWidget* generalTab;
	QFormLayout* formLayout;
	QCheckBox* embeds;
	QCheckBox* generics;
	QCheckBox* favicons;
	QCheckBox* emoticons;
	QCheckBox* stopGifs;
	QCheckBox* avatar;
	QCheckBox* history;
	QSpinBox* maxlines;
	QSpinBox* maxHistory;
	QSpinBox* fontsize;
	QPlainTextEdit* remotes;
	QPushButton* saveButton;
	QString configPath;
	QJsonObject jsonObj;
	QLineEdit* downloadDir;
	// events tab
	QWidget* eventTab;
	QFormLayout* eventLayout;
	QCheckBox* kickEvent;
	QCheckBox* banEvent;
	QCheckBox* moveSelfEvent;
	QCheckBox* moveOtherEvent;
	QCheckBox* channelCreatedEvent;
	QCheckBox* channelDeletedEvent;
	QCheckBox* clientConnectedEvent;
	QCheckBox* clientDisconnectedEvent;
	QCheckBox* ownDisconnectedEvent;
	QCheckBox* ownConnectedEvent;

	void readConfig();
};
