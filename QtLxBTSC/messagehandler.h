#pragma once
#include "PluginHelper.h"

namespace messageHandler
{
	PluginHelper* helper;

	inline void handler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
	{
		switch (type) 
		{ 
		case QtDebugMsg: 
			helper->onDebugMessage("Debug: " + msg);
			break;
		case QtWarningMsg:
			helper->onDebugMessage("Warning: " + msg);
			break;
		case QtCriticalMsg: 
			helper->onDebugMessage("Critical: " + msg);
			break;
		case QtFatalMsg: 
			helper->onDebugMessage("Fatal: " + msg);
			break;
		case QtInfoMsg: 
			helper->onDebugMessage("Info: " + msg);
			break;
		default: 
			helper->onDebugMessage("Debug: " + msg);
			break;
		}
	}

}
