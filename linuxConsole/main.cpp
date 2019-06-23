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
	lghtIOinit();
	/*
	//router instance
	router_t rtr;
	//init of random machine
	srand((unsigned char)time(NULL));
	//stack of all lights
	std::vector<lght_t> tLightStack;
	//stack of iterators for future queue
	std::vector<std::map<int, int>::iterator> iteratorStack;
	//lets generate some amount of light iterators
	for (int i = frstLght; i < maxLght; i++)
	{
		//just pushing pair of random prior and current idx to stack of light iterators
		iteratorStack.push_back(rtr.pushRequest(std::pair<int, int>(rand() % 100, i)));
	}	
	inLog(getStrQueue(&rtr));
	cout << getStrQueue(&rtr).c_str() << endl;
	//iterate over lights, create, init and run each
	for (size_t i = 0; i < iteratorStack.size(); i++)
	{
		//pushing to stack some blank light
		tLightStack.push_back(lght_t());
		//init of last light by given values
		tLightStack[i].init(lghtColor::Red, 100, iteratorStack[i]);
		//create thread with running wLoop of light, passing instance of safe_ptr<router_t>
		std::thread thr(&lght_t::wLoop, &(tLightStack[i]), &rtr);
		//lunch it independent
		thr.detach();
	}
	//set new king
	rtr.setTopIdx(rtr.getFqe());
	while (true)
	{
	}
	*/
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
		strQueue.append("idx#");
		strQueue.append(std::to_string(itr->second));
		strQueue.append("+");
		strQueue.append(std::to_string(itr->first));
		strQueue.append(", ");
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