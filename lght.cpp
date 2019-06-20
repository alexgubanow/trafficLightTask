#include "lght.h"
#include <stdio.h>
#include <chrono>
#include <thread>
using namespace std;

int lght_t::init(lghtColor initColor, int _delay, std::map<int, int>::iterator _Itr)
{
	printf("init of lght idx#%d\n", _Itr->second);
	isCanRun = 1;
	Itr = _Itr;
	//routerInst = _routerInst;
	currLight = initColor;
	delay = _delay;
	return 0;
}
int lght_t::wLoop()
{
	while (isCanRun)
	{
		//printf("waiting idx#%d\n", Itr->second);
		//can be replaced by listening some port or other external interface
		while (getTopIdx() != Itr) {
		}
		//sw to green
		printf("idx#%d become green\n", Itr->second);
		swLight(lghtColor::Grn);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		//sw to red
		printf("idx#%d become red\n", Itr->second);
		swLight(lghtColor::Red);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
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
	nextPls();
	//turn on yellow
	//printf("idx#%d become yellow\n", Itr->second);
	currLight = turnTo(lghtColor::Ylw);
	//wait for pretty transition
	std::this_thread::sleep_for(std::chrono::milliseconds(getSmallDelay()));
	//turn on target color
	currLight = turnTo(target);
	return 0;
}
int lght_t::getSmallDelay()
{
	//calc small delay as 1/4 from setted delay
	int smallDelay = delay / 4;
	//in case if setted delay less than 4, small delay equal to 1
	if (smallDelay < 1)
	{
		smallDelay = 1;
	}
	//or maybe it has to be zero
	//smallDelay = 0;
	return smallDelay;
}