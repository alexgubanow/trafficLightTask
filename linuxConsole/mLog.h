#pragma once
#include <fcntl.h>
#include <string>

/*Writing start mark to logfile*/
int initLog(char* _path);
/*Writing finish mark to logfile*/
int finishLog();
/*Write to logfile given line, with marked by idx*/
int inLog(std::string line, int idx, bool showInConsole);
/*Write to logfile given line*/
int inLog(std::string line, bool showInConsole);