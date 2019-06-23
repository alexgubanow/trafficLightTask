#include "mLog.h"
#include <sys/file.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

char* path;

int initLog(char* _path)
{
	path = _path;
	return inLog("started here");
}

int inLog(std::string line)
{
	int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY | O_APPEND, 0666);
	if (fd != -1) {
		line.push_back('\r');
		line.push_back('\n');
		if (flock(fd, 2) != 0)
		{
			perror("Log file giveup to lock");
			close(fd);
			return fd;
		}
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%FT%T%z ", timeinfo);
		line.insert(0, buffer);
		write(fd, line.c_str(), line.size());
		if (flock(fd, 8) != 0)
		{
			perror("Log file giveup to unlock");
			close(fd);
			return fd;
		}
		close(fd);
	}
	else {
		std::cout << "Cannot open file " << path << std::endl;
		std::cout << "trying to delete it " << path << std::endl;
		if (remove(path) != 0)
		{
			perror("Error deleting file");
		}
		else
		{
			puts("File successfully deleted");
		}
	}
	return fd;
}

int inLog(std::string line, int idx)
{
	int fd = open(path, O_WRONLY | O_CREAT | O_APPEND);
	if (fd != -1) {
		std::string header;
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, 80, "%FT%T%z ", timeinfo);
		header.append(buffer);
		header.append("[");
		header.append(std::to_string(idx));
		header.append("] ");
		line.insert(0, header);
		line.push_back('\r');
		line.push_back('\n');
		if (flock(fd, 2) != 0)
		{
			perror("Log file giveup to lock");
			close(fd);
			return fd;
		}
		write(fd, line.c_str(), line.size());
		if (flock(fd, 8) != 0)
		{
			perror("Log file giveup to unlock");
			close(fd);
			return fd;
		}
		close(fd);
	}
	else {
		std::cout << "Cannot open file " << path << std::endl;
		std::cout << "trying to delete it " << path << std::endl;
		if (remove(path) != 0)
		{
			perror("Error deleting file");
		}
		else
		{
			puts("File successfully deleted");
		}
	}
	return fd;
}

int finishLog()
{
	return inLog("finished here");
}