#include "ConfigWidget.h"

ConfigWidget::ConfigWidget(QString path, QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle("Better Chat Settings");
	this->setFixedSize(300, 250);
	configPath = QString("%1LxBTSC/template/config.json").arg(path);
	formLayout = new QFormLayout(this);
	embeds = new QCheckBox("Enable embeds", this);
	embeds->setChecked(true);
	favicons = new QCheckBox("Enable favicons for links", this);
	favicons->setChecked(false);
	emoticons = new QCheckBox("Enable emotes", this);
	emoticons->setChecked(true);
	maxlines = new QSpinBox(this);
	maxlines->setMinimum(50);
	maxlines->setMaximum(1000);
	maxlines->setValue(500);
	remotes = new QPlainTextEdit(this);
	remotes->setMinimumHeight(70);
	remotes->setLineWrapMode(QPlainTextEdit::WidgetWidth);
	remotes->setPlaceholderText("Separate multiple urls with '|'");

	saveButton = new QPushButton("Save", this);
	connect(saveButton, &QPushButton::clicked, this, &ConfigWidget::save);

	QHBoxLayout* horizontal = new QHBoxLayout(this);
	horizontal->addSpacing(200);
	horizontal->addWidget(saveButton);
	formLayout->addRow(embeds);
	formLayout->addRow(favicons);
	formLayout->addRow(emoticons);
	formLayout->addRow(new QLabel("Max lines in tab:", this), maxlines);
	formLayout->addRow(new QLabel("Remote emote definitions:"));
	formLayout->addRow(remotes);
	formLayout->addItem(new QSpacerItem(0, 50));
	formLayout->addRow(horizontal);
}

ConfigWidget::~ConfigWidget()
{
}

void ConfigWidget::open()
{
	QFile file(configPath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString jsonText = file.readAll();
		file.close();
		QJsonDocument document = QJsonDocument::fromJson(jsonText.toUtf8());
		jsonObj = document.object();
		embeds->setChecked(jsonObj.value("EMBED_ENABLED").toBool());
		favicons->setChecked(jsonObj.value("FAVICONS_ENABLED").toBool());
		emoticons->setChecked(jsonObj.value("EMOTICONS_ENABLED").toBool());
		maxlines->setValue(jsonObj.value("MAX_LINES").toInt());
		QJsonArray remotejson = jsonObj.value("REMOTE_EMOTES").toArray();
		QStringList list;
		foreach(const QJsonValue &v, remotejson) 
		{
			list.append(v.toString());
		}
		remotes->setPlainText(list.join('|'));
	}
	this->show();
}

void ConfigWidget::save()
{
	jsonObj.insert("EMBED_ENABLED", embeds->isChecked());
	jsonObj.insert("FAVICONS_ENABLED", favicons->isChecked());
	jsonObj.insert("EMOTICONS_ENABLED", emoticons->isChecked());
	jsonObj.insert("MAX_LINES", maxlines->value());
	if (remotes->toPlainText().length() > 1)
	{
		jsonObj.insert("REMOTE_EMOTES", QJsonArray::fromStringList(remotes->toPlainText().split('|')));
	}
	else
	{
		jsonObj.insert("REMOTE_EMOTES", QJsonArray());
	}
	QJsonDocument doc(jsonObj);
	QFile file(configPath);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(doc.toJson());
		file.close();
		this->close();
		emit configChanged();
	}
}


