#include "lght.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include "mLog.h"
using namespace std;

int lght_t::init(lghtColor initColor, int _delay, std::map<int, int>::iterator _Itr)
{
	inLog("init of lght", _Itr->second);
	printf("init of lght idx#%d\n", _Itr->second);
	isCanRun = 1;
	Itr = _Itr;
	currLight = initColor;
	delay = _delay;
	return 0;
}
int lght_t::wLoop(safe_ptr<router_t> rtrI)
{
	while (isCanRun)
	{
		//can be replaced by listening some port or other external interface
		while (rtrI->getTopIdx() != Itr) {		}
		//sw to green
		swLight(lghtColor::Grn);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//sw to red
		rtrI->nextPls();
		swLight(lghtColor::Red);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}
	return closeGate();
}
int lght_t::closeGate()
{
	/*its not thread safe, has to be rethinked*/
	//going to red
	swLight(lghtColor::Red);
	//prevent to run main loop
	return isCanRun = 0;
}

int lght_t::swLight(lghtColor target)
{
	//remove self from Queue
	//turn on yellow
	printf("idx#%d become yellow\n", Itr->second);
	currLight = turnTo(lghtColor::Ylw);
	//wait for pretty transition
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	//turn on target color
	if (target == lghtColor::Grn)
	{
		printf("idx#%d green\n", Itr->second);
	}
	else
	{
		printf("idx#%d red\n", Itr->second);
	}
	currLight = turnTo(target);
	return 0;
}