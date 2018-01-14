// http://www.qtcentre.org/threads/3901-Redirect-printf-to-QTextEdit?p=21330#post21330
#pragma once

#include <QObject>
#include <QString>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>

class StdOutRedirector : public QObject
{
	Q_OBJECT
public:
	StdOutRedirector()
	{
		// Redirect
		if (_pipe(fdguistd, 4096, _O_BINARY) == -1)
			printf("failed!");
		//int tr = fcntl(fdguistd, O_NONBLOCK);
		// Duplicate stdout file descriptor (next line will close original)
		fdStdOut = _dup(_fileno(stdout));
		// Duplicate write end of pipe to stdout file descriptor
		if (_dup2(fdguistd[1], _fileno(stdout)) != 0)
			printf("failed!");
		// Close original 
		_close(1);
		// Duplicate write end of original
		_dup2(fdguistd[1], 1);

	}

	public slots:
	QString readOuts()
	{
		int n_out;
		char *buffer = new char[4096];
		QString str;
		//char buffer[512];
		printf("\n");
		fflush(stdout);

		n_out = _read(fdguistd[0], buffer, 4096);

		if (n_out <= 0)
			return "";
		if (n_out > 1) {
			str.append(QString(buffer));
			int con = str.lastIndexOf('\n');
			int remv = str.at(con - 1) == '/n' ? 1 : 0;
			if (con) {
				str = str.remove(con - remv, str.length());
				return str;
			}
		}
		return "";
	}
private:
	int fdStdOut;
	int fdguistd[2];
};