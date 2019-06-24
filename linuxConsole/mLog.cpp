#include "mLog.h"
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

char* logFilePath;

int openLogFile(int maxTry);
std::string getHeader(std::string idx);
void healLogFile();

int initLog(char* _path)
{
	logFilePath = _path;
	return inLog("started here", false);
}
int finishLog()
{
	return inLog("finished here", false);
}

int inLog(std::string line, bool showInConsole)
{
	int fd = openLogFile(3);
	if (fd == -1) {
		printf("Giveup to open log file %s\n", logFilePath);
		return fd;
	}
	line.append("\r\n");
	if (flock(fd, 2) != 0)
	{
		printf("Giveup to lock log file %s\n", logFilePath);
		close(fd);
		return fd;
	}
	line.insert(0, getHeader(std::to_string(-13)));
	if (showInConsole)
	{
		printf("%s", line.c_str());
	}
	write(fd, line.c_str(), line.size());
	if (flock(fd, 8) != 0)
	{
		printf("Giveup to unlock log file %s\n", logFilePath);
		close(fd);
		return fd;
	}
	close(fd);
	return fd;
}

int inLog(std::string line, int idx, bool showInConsole)
{
	int fd = openLogFile(3);
	if (fd == -1) {
		printf("Giveup to open log file %s\n", logFilePath);
		return fd;
	}
	line.append("\r\n");
	line.insert(0, getHeader(std::to_string(idx)));
	if (flock(fd, 2) != 0)
	{
		perror("Log file giveup to lock\n");
		close(fd);
		return fd;
	}
	if (showInConsole)
	{
		printf("%s", line.c_str());
	}
	write(fd, line.c_str(), line.size());
	if (flock(fd, 8) != 0)
	{
		printf("Giveup to unlock log file %s\n", logFilePath);
		close(fd);
		return fd;
	}
	close(fd);
	return fd;
}

int openLogFile(int maxTry)
{
	int tryCount = 0;
	int fd = -1;
	while (fd == -1 && tryCount < maxTry)
	{
		fd = open(logFilePath, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1) {
			healLogFile();
		}
	}
	return fd;
}

std::string getHeader(std::string idx)
{
	std::string header;
	char timeChar[64];
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(timeChar, 64, "%FT%T%z", timeinfo);
	char buff[256];
	snprintf(buff, 256, "%s [%s] ", timeChar, idx.c_str());
	header.append(buff);
	return header;
}

void healLogFile()
{
	printf("Cannot open log file: %s\n", logFilePath);
	printf("Trying to delete log file: %s\n", logFilePath);
	if (remove(logFilePath) != 0)
	{
		printf("Error while deleting log file: %s\n", logFilePath);
	}
	else
	{
		printf("File %s successfully deleted\n", logFilePath);
	}
}