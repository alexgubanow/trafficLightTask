#pragma once
#include <fcntl.h>
#include <string>
int initLog(char* path);
int inLog(std::string line);
int finishLog();