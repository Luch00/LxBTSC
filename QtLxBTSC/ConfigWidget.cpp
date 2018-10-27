/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2018 Luch (https://github.com/Luch00)
*/

#include "ConfigWidget.h"
#include <QLabel>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>

ConfigWidget::ConfigWidget(const QString& path, QWidget *parent)
	: QWidget(parent)
	, configPath(QString("%1LxBTSC/template/config.json").arg(path))
{
	this->setWindowTitle("Better Chat Settings");
	this->setFixedSize(300, 390);
	formLayout = new QFormLayout(this);
	embeds = new QCheckBox("Enable embeds", this);
	embeds->setChecked(true);
	generics = new QCheckBox("Disable generic embeds", this);
	generics->setChecked(false);
	favicons = new QCheckBox("Enable favicons for links", this);
	favicons->setChecked(false);
	emoticons = new QCheckBox("Enable emotes", this);
	emoticons->setChecked(true);
	avatar = new QCheckBox("Avatars in chat", this);
	avatar->setChecked(false);
	stopGifs = new QCheckBox("Play gifs only on hover", this);
	stopGifs->setChecked(false);
	maxlines = new QSpinBox(this);
	maxlines->setMinimum(50);
	maxlines->setMaximum(1000);
	maxlines->setValue(500);
	downloadDir = new QLineEdit("", this);
	downloadDir->setDisabled(true);
	QPushButton* browseButton = new QPushButton("...", this);
	browseButton->setToolTip("Browse folder");
	browseButton->setFixedWidth(40);
	remotes = new QPlainTextEdit(this);
	remotes->setMinimumHeight(70);
	remotes->setLineWrapMode(QPlainTextEdit::WidgetWidth);
	remotes->setPlaceholderText("Separate multiple urls with '|'");

	saveButton = new QPushButton("Save", this);
	connect(saveButton, &QPushButton::clicked, this, &ConfigWidget::save);
	connect(browseButton, &QPushButton::clicked, this, &ConfigWidget::browseDirectory);

	QHBoxLayout* horizontal = new QHBoxLayout(this);
	horizontal->addSpacing(200);
	horizontal->addWidget(saveButton);
	formLayout->addRow(embeds);
	formLayout->addRow(generics);
	formLayout->addRow(favicons);
	formLayout->addRow(emoticons);
	formLayout->addRow(avatar);
	formLayout->addRow(stopGifs);
	formLayout->addRow(new QLabel("Max lines in tab:", this), maxlines);
	formLayout->addRow(new QLabel("Download directory:"));
	formLayout->addRow(downloadDir);
	formLayout->addRow(browseButton);
	formLayout->addRow(new QLabel("Remote emote definitions:"));
	formLayout->addRow(remotes);
	formLayout->addItem(new QSpacerItem(0, 50));
	formLayout->addRow(horizontal);
	readConfig();
}

ConfigWidget::~ConfigWidget()
{
}

void ConfigWidget::readConfig()
{
	QFile file(configPath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString jsonText = file.readAll();
		file.close();
		QJsonDocument document = QJsonDocument::fromJson(jsonText.toUtf8());
		jsonObj = document.object();
		embeds->setChecked(jsonObj.value("EMBED_ENABLED").toBool());
		generics->setChecked(jsonObj.value("GENERICS_DISABLED").toBool());
		favicons->setChecked(jsonObj.value("FAVICONS_ENABLED").toBool());
		emoticons->setChecked(jsonObj.value("EMOTICONS_ENABLED").toBool());
		avatar->setChecked(jsonObj.value("AVATARS_ENABLED").toBool());
		stopGifs->setChecked(jsonObj.value("HOVER_ANIMATES_GIFS").toBool());
		maxlines->setValue(jsonObj.value("MAX_LINES").toInt());
		downloadDir->setText(jsonObj.value("DOWNLOAD_DIR").toString());
		QJsonArray remotejson = jsonObj.value("REMOTE_EMOTES").toArray();
		QStringList list;
		foreach(const QJsonValue &v, remotejson) 
		{
			list.append(v.toString());
		}
		remotes->setPlainText(list.join('|'));
	}
}

void ConfigWidget::browseDirectory()
{
	QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", "", QFileDialog::ShowDirsOnly);
	downloadDir->setText(dir);
}

void ConfigWidget::save()
{
	jsonObj.insert("EMBED_ENABLED", embeds->isChecked());
	jsonObj.insert("GENERICS_DISABLED", generics->isChecked());
	jsonObj.insert("FAVICONS_ENABLED", favicons->isChecked());
	jsonObj.insert("EMOTICONS_ENABLED", emoticons->isChecked());
	jsonObj.insert("AVATARS_ENABLED", avatar->isChecked());
	jsonObj.insert("HOVER_ANIMATES_GIFS", stopGifs->isChecked());
	jsonObj.insert("MAX_LINES", maxlines->value());
	jsonObj.insert("DOWNLOAD_DIR", downloadDir->text());
	if (remotes->toPlainText().length() > 1)
	{
		jsonObj.insert("REMOTE_EMOTES", QJsonArray::fromStringList(remotes->toPlainText().split('|')));
	}
	else
	{
		jsonObj.insert("REMOTE_EMOTES", QJsonArray());
	}
	
	QFile file(configPath);
	if (file.open(QIODevice::WriteOnly))
	{
		QJsonDocument doc(jsonObj);
		file.write(doc.toJson());
		file.close();
		this->close();
		emit configChanged();
	}
}

QString ConfigWidget::getConfigAsString(const QString& key)
{
	return jsonObj.value(key).toString();
}


