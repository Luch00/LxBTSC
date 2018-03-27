#include "ConfigWidget.h"

ConfigWidget::ConfigWidget(QString path, QWidget *parent)
	: QWidget(parent)
{
	this->setWindowTitle("Better Chat Settings");
	this->setFixedSize(300, 310);
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
	formLayout->addRow(favicons);
	formLayout->addRow(emoticons);
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
		favicons->setChecked(jsonObj.value("FAVICONS_ENABLED").toBool());
		emoticons->setChecked(jsonObj.value("EMOTICONS_ENABLED").toBool());
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
	jsonObj.insert("FAVICONS_ENABLED", favicons->isChecked());
	jsonObj.insert("EMOTICONS_ENABLED", emoticons->isChecked());
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

QString ConfigWidget::getConfigAsString(QString key)
{
	return jsonObj.value(key).toString();
}


