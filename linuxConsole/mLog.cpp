#include "mLog.h"
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

/*Path to logfile*/
char* logFilePath;

/*Method to try open specified logfile*/
int openLogFile(int maxTry);
/*generate header for log entry, with given idx*/
std::string getHeader(std::string idx);
/*trying to heal connection to log file, by deleting it, LOL*/
void healLogFile();

/*Writing start mark to logfile*/
int initLog(char* _path)
{
	logFilePath = _path;
	return inLog("started here", false);
}
/*Writing finish mark to logfile*/
int finishLog()
{
	return inLog("finished here", false);
}
/*Write to logfile given line, with marked by idx*/
int inLog(std::string line, int idx, bool showInConsole)
{
	//trying to open logfile, max 3 times
	int fd = openLogFile(3);
	if (fd == -1) { printf("Giveup to open log file %s\n", logFilePath); return fd; }
	//trying to lock logfile
	if (flock(fd, 2) != 0) { printf("Giveup to lock log file %s\n", logFilePath); close(fd); return fd; }
	//generating header for log entry and pushing it to buffer
	line.insert(0, getHeader(std::to_string(idx)));
	//show generated entry in console, if specified
	if (showInConsole) { printf("%s", line.c_str()); }
	//writing data to file
	write(fd, (line + "\r\n").c_str(), line.size());
	//trying to unlock file
	if (flock(fd, 8) != 0) { printf("Giveup to unlock log file %s\n", logFilePath); close(fd); return fd; }
	//close file
	close(fd);
	return fd;
}
/*Write to logfile given line*/
int inLog(std::string line, bool showInConsole)
{
	//just call method above with idx = -13
	return inLog(line, -13, showInConsole);
}
/*Method to try open specified logfile*/
int openLogFile(int maxTry)
{
	int tryCount = 0;
	int fd = -1;
	//controling try time
	while (fd == -1 && tryCount < maxTry)
	{
		//opening file
		fd = open(logFilePath, O_WRONLY | O_CREAT | O_APPEND, 0666);
		//heal it if needed
		if (fd == -1) { healLogFile(); }
	}
	return fd;
}
/*generate header for log entry, with given idx*/
std::string getHeader(std::string idx)
{
	//buffer for final result
	std::string header;
	//buffer for string representation of timeNow
	char timeChar[64];
	//getting time now
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	//parse it to string, by format year-month-dayThour:minute:second:time zone
	strftime(timeChar, 64, "%FT%T%z", timeinfo);
	char buff[256];
	//make string with time now and given idx
	snprintf(buff, 256, "%s [%s] ", timeChar, idx.c_str());
	//push result to std::string 
	header.append(buff);
	return header;
}
/*trying to heal connection to log file, by deleting it, LOL*/
void healLogFile()
{
	printf("Cannot open log file: %s\n", logFilePath);
	printf("Trying to delete log file: %s\n", logFilePath);
	if (remove(logFilePath) != 0) { printf("Error while deleting log file: %s\n", logFilePath); }
	else { printf("File %s successfully deleted\n", logFilePath); }
}