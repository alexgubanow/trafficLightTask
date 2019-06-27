#include <iostream>
#include <vector>
#include <time.h>
#include "lght.h"
#include <thread>
#include <signal.h>
#include <iterator>
#include "mLog.h"
#include "irq_handles.h"

using namespace std;

constexpr auto frstLght = 1;
constexpr auto maxLght = 5;

char* logFlName = (char*)"traflght.log";

std::string getStrQueue(router_t* rtr);
void setupOnExitHandlers();

int main(int argc, char* argv[])
{
	//setup on exit handlers
	setupOnExitHandlers();
	//main exiter
	atexit(mainExit);
	//init log funcs
	initLog(logFlName);
	//trying to communicate to lghtIO
	if (lghtIOinit() < 0)
	{
		inLog("Failed to load lghtIO driver", true);
		return -1;
	}
	inLog("lghtIO driver are alive", true);
	//router instance
	router_t rtr;
	//init of random machine
	srand((unsigned char)time(NULL));
	//stack of all lights
	std::vector<lght_t> tLightStack;
	//stack of iterators for future queue
	std::vector<std::map<int, int>::iterator> iteratorStack;

	//iterate over lights, create and init each
	for (int i = frstLght; i < maxLght; i++)
	{
		//pushing to stack some blank light
		tLightStack.push_back(lght_t());
		//init of last light by given values
		tLightStack.back().init(lghtColor::Red, 100, rtr.pushRequest(std::pair<int, int>(rand() % 100, i)));
		
	}	
	inLog(getStrQueue(&rtr), true);
	//iterate over lights, to run each
	for (std::vector<lght_t>::iterator it = tLightStack.begin(); it != tLightStack.end(); ++it) {
		/* std::cout << *it; ... */
		//create thread with running wLoop of light
		std::thread thr(&lght_t::wLoop, it, &rtr);
		//lunch it independent
		thr.detach();
	}
	//set new king
	rtr.setTopIdx(rtr.getFqe());
	while (true)
	{
	}
	
	return 0;
}
/*return string representation of queue*/
std::string getStrQueue(router_t* rtr)
{
	//initial preload by static phrase
	std::string strQueue = "queue now is: ";
	//iterate over queue and push formatted string representation of each member to strQueue
	for (auto itr = rtr->getFqe(); itr != rtr->getLqe(); itr++)
	{
		strQueue.append("idx#" + std::to_string(itr->second) + "+" + std::to_string(itr->first) + ", ");
	}
	//remove last coma and space
	strQueue.erase(strQueue.size() - 2, 2);
	return strQueue;
}

void setupOnExitHandlers()
{
	signal(SIGTERM, (__sighandler_t)& SIGTERM_Handler);
	signal(SIGINT, (__sighandler_t)& SIGINT_Handler);
	signal(SIGQUIT, (__sighandler_t)& SIGQUIT_Handler);
	signal(SIGKILL, (__sighandler_t)& SIGKILL_Handler);
	signal(SIGHUP, (__sighandler_t)& SIGHUP_Handler);
}