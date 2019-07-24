/*
 * Better Chat plugin for TeamSpeak 3
 * GPLv3 license
 *
 * Copyright (C) 2019 Luch (https://github.com/Luch00)
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
	//this->setFixedSize(300, 410);
	generalTab = new QWidget();
	formLayout = new QFormLayout(generalTab);
	generalTab->setLayout(formLayout);
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
	history = new QCheckBox("Load chat history", this);
	history->setChecked(false);
	maxlines = new QSpinBox(this);
	maxlines->setMinimum(50);
	maxlines->setMaximum(1000);
	maxlines->setValue(500);
	maxHistory = new QSpinBox(this);
	maxHistory->setMinimum(10);
	maxHistory->setMaximum(500);
	maxHistory->setValue(50);
	fontsize = new QSpinBox(this);
	fontsize->setMinimum(6);
	fontsize->setMaximum(34);
	fontsize->setValue(12);
	downloadDir = new QLineEdit("", this);
	downloadDir->setDisabled(true);
	QPushButton* browseButton = new QPushButton("...", this);
	browseButton->setToolTip("Browse folder");
	browseButton->setFixedWidth(40);
	remotes = new QPlainTextEdit(this);
	remotes->setMaximumHeight(70);
	remotes->setLineWrapMode(QPlainTextEdit::WidgetWidth);
	remotes->setPlaceholderText("Separate multiple urls with '|'");

	eventTab = new QWidget();
	eventLayout = new QFormLayout(eventTab);
	eventTab->setLayout(eventLayout);
	kickEvent = new QCheckBox("Show kicks");
	banEvent = new QCheckBox("Show bans");
	moveSelfEvent = new QCheckBox("Show own move");
	moveOtherEvent = new QCheckBox("Show others move");
	channelCreatedEvent = new QCheckBox("Show channel created");
	channelDeletedEvent = new QCheckBox("Show channel deleted");
	clientConnectedEvent = new QCheckBox("Show client connect");
	clientDisconnectedEvent = new QCheckBox("Show client disconnect");
	ownDisconnectedEvent = new QCheckBox("Show own disconnect");
	ownConnectedEvent = new QCheckBox("Show own connect");

	eventLayout->addRow(kickEvent);
	eventLayout->addRow(banEvent);
	eventLayout->addRow(moveSelfEvent);
	eventLayout->addRow(moveOtherEvent);
	eventLayout->addRow(channelCreatedEvent);
	eventLayout->addRow(channelDeletedEvent);
	eventLayout->addRow(clientConnectedEvent);
	eventLayout->addRow(clientDisconnectedEvent);
	eventLayout->addRow(ownConnectedEvent);
	eventLayout->addRow(ownDisconnectedEvent);

	saveButton = new QPushButton("Save", this);
	connect(saveButton, &QPushButton::clicked, this, &ConfigWidget::save);
	connect(browseButton, &QPushButton::clicked, this, &ConfigWidget::browseDirectory);

	QHBoxLayout* horizontal = new QHBoxLayout();
	horizontal->addSpacing(200);
	horizontal->addWidget(saveButton);
	formLayout->addRow(embeds);
	formLayout->addRow(generics);
	formLayout->addRow(favicons);
	formLayout->addRow(emoticons);
	formLayout->addRow(avatar);
	formLayout->addRow(stopGifs);
	formLayout->addRow(history);
	formLayout->addRow(new QLabel("Max lines in tab:", this), maxlines);
	formLayout->addRow(new QLabel("Max lines of history:", this), maxHistory);
	formLayout->addRow(new QLabel("Font size:", this), fontsize);
	formLayout->addRow(new QLabel("Download directory:"));
	formLayout->addRow(downloadDir);
	formLayout->addRow(browseButton);
	formLayout->addRow(new QLabel("Remote emote definitions:"));
	formLayout->addRow(remotes);
	formLayout->addItem(new QSpacerItem(0, 10));
	//formLayout->addRow(horizontal);
	tabWidget = new QTabWidget(this);
	tabWidget->addTab(generalTab, "General");
	tabWidget->addTab(eventTab, "Events");
	configLayout = new QFormLayout(this);
	this->setLayout(configLayout);
	configLayout->addRow(tabWidget);
	configLayout->addRow(horizontal);

	//this->adjustSize();
	//this->setFixedSize(sizeHint().width(), sizeHint().height());
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
		history->setChecked(jsonObj.value("HISTORY_ENABLED").toBool());
		maxlines->setValue(jsonObj.value("MAX_LINES").toInt());
		maxHistory->setValue(jsonObj.value("MAX_HISTORY").toInt(50));
		fontsize->setValue(jsonObj.value("FONT_SIZE").toInt());
		downloadDir->setText(jsonObj.value("DOWNLOAD_DIR").toString());

		kickEvent->setChecked(jsonObj.value("EVENT_KICK").toBool());
		banEvent->setChecked(jsonObj.value("EVENT_BAN").toBool());
		moveSelfEvent->setChecked(jsonObj.value("EVENT_MOVESELF").toBool());
		moveOtherEvent->setChecked(jsonObj.value("EVENT_MOVEOTHER").toBool());
		channelCreatedEvent->setChecked(jsonObj.value("EVENT_CHANNELCREATE").toBool());
		channelDeletedEvent->setChecked(jsonObj.value("EVENT_CHANNELDELETE").toBool());
		clientConnectedEvent->setChecked(jsonObj.value("EVENT_CLIENTCONNECT").toBool());
		clientDisconnectedEvent->setChecked(jsonObj.value("EVENT_CLIENTDISCONNECT").toBool());
		ownConnectedEvent->setChecked(jsonObj.value("EVENT_SELFCONNECT").toBool());
		ownDisconnectedEvent->setChecked(jsonObj.value("EVENT_SELFDISCONNECT").toBool());

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
	jsonObj.insert("HISTORY_ENABLED", history->isChecked());
	jsonObj.insert("MAX_LINES", maxlines->value());
	jsonObj.insert("MAX_HISTORY", maxHistory->value());
	jsonObj.insert("FONT_SIZE", fontsize->value());
	jsonObj.insert("DOWNLOAD_DIR", downloadDir->text());

	jsonObj.insert("EVENT_KICK", kickEvent->isChecked());
	jsonObj.insert("EVENT_BAN", banEvent->isChecked());
	jsonObj.insert("EVENT_MOVESELF", moveSelfEvent->isChecked());
	jsonObj.insert("EVENT_MOVEOTHER", moveOtherEvent->isChecked());
	jsonObj.insert("EVENT_CHANNELCREATE", channelCreatedEvent->isChecked());
	jsonObj.insert("EVENT_CHANNELDELETE", channelDeletedEvent->isChecked());
	jsonObj.insert("EVENT_CLIENTCONNECT", clientConnectedEvent->isChecked());
	jsonObj.insert("EVENT_CLIENTDISCONNECT", clientDisconnectedEvent->isChecked());
	jsonObj.insert("EVENT_SELFCONNECT", ownConnectedEvent->isChecked());
	jsonObj.insert("EVENT_SELFDISCONNECT", ownDisconnectedEvent->isChecked());

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

bool ConfigWidget::getConfigAsBool(const QString& key)
{
	return jsonObj.value(key).toBool();
}
