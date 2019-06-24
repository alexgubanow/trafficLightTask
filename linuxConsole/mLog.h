#pragma once
#include <fcntl.h>
#include <string>
int initLog(char* path);
int finishLog();
int inLog(std::string line, bool showInConsole);
int inLog(std::string line, int idx, bool showInConsole);