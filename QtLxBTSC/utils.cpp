#pragma once

#include <utils.h>
#include <QDir>
#include <QMetaMethod>

namespace utils
{
	QString direction(bool outgoing)
	{
		if (outgoing)
		{
			return "Outgoing";
		}
		return "Incoming";
	}

	QString format(QString original)
	{
		// escape single quotes
		original.replace("'", "&#39;");
		original.replace("\\", "&#92;");

		// escape newlines to not break javascript
		original.replace(QRegExp("[\r\n]"), "\\r\\n");

		return original;
	}

	void checkEmoteSets(const QString &path)
	{
		QDir directory(path + "LxBTSC/template/Emotes");
		QStringList f = directory.entryList(QStringList("*.json"), QDir::Files, QDir::NoSort);
		QString json;
		if (f.isEmpty())
		{
			json = "[]";
		}
		else
		{
			json = "[\"";
			json.append(f.join("\",\""));
			json.append("\"]");
		}

		QFile file(path + "LxBTSC/template/emotesets.json");
		if (file.open(QIODevice::WriteOnly))
		{
			QTextStream stream(&file);
			stream << json << endl;
		}
	}

	// helper function to print some object info
	void printObjectDetails(QObject *object, QTextStream &stream)
	{
		stream << "objectname: " << object->objectName() << endl;
		const QMetaObject *mo = object->metaObject();
		stream << "classname: " << mo->className() << endl;
		stream << "-------properties-----------" << endl;
		for (size_t j = 0; j < mo->propertyCount(); ++j)
		{
			QMetaProperty p = mo->property(j);

			QVariant v = object->property(p.name());
			stream << QString("%1: %2").arg(p.name()).arg(v.toString()) << endl;
		}
		stream << "-------dynamics-----------" << endl;
		QList<QByteArray> by = object->dynamicPropertyNames();

		for each (QByteArray var in by)
		{
			stream << var << endl;
		}
		stream << "-----------methods-----------" << endl;
		for (int k = mo->methodOffset(); k < mo->methodCount(); ++k)
		{
			int return_type = mo->method(k).returnType();
			QMetaMethod::Access access = mo->method(k).access();
			QMetaMethod::MethodType method_type = mo->method(k).methodType();
			QList<QByteArray> param_names = mo->method(k).parameterNames();
			stream << QMetaType::typeName(return_type) << " ";
			stream << QString::fromLatin1(mo->method(k).methodSignature());
			for (int h = 0; h < param_names.count(); ++h)
			{
				stream << param_names[h] << " ";
			}
			switch (access)
			{
			case QMetaMethod::Private:
				stream << "private";
				break;

			case QMetaMethod::Protected:
				stream << "protected";
				break;

			case QMetaMethod::Public:
				stream << "public";
				break;
			}
			stream << " ";
			switch (method_type)
			{
			case QMetaMethod::Constructor:
				stream << "constructor";
				break;

			case QMetaMethod::Method:
				stream << "method";
				break;

			case QMetaMethod::Signal:
				stream << "signal";
				break;

			case QMetaMethod::Slot:
				stream << "slot";
				break;
			}
			stream << endl;
		}
		stream << endl;
		QObjectList list = object->children();
		for (int v = 0; v < list.count(); ++v)
		{
			printObjectDetails(list[v], stream);
		}
	}
}
