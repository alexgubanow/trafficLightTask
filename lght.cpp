#include "lght.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include "mLog.h"
using namespace std;

int lght_t::init(lghtColor initColor, int _delay, std::map<int, int>::iterator _Itr, router_t* _rtrI)
{
	rtrI = _rtrI;
	printf("init of lght idx#%d\n", _Itr->second);
	isCanRun = 1;
	Itr = _Itr;
	currLight = initColor;
	delay = _delay;
	sdelay = getSmallDelay(delay);
	return 0;
}
int lght_t::wLoop()
{
	while (isCanRun)
	{
		//can be replaced by listening some port or other external interface
		while (rtrI->getTopIdx() != Itr) {}
		//sw to green
		swLight(lghtColor::Grn);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//sw to red
		swLight(lghtColor::Red);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
	//turn on yellow
	inLog("now Yellow", Itr->second);
	printf("idx#%d become yellow\n", Itr->second);
	currLight = turnTo(lghtColor::Ylw);
	//need to choose switching style, can all be yellow or not
	//calling nextPls here will make swithching on all yellow
	//if (target == lghtColor::Red) { rtrI->nextPls(); }
	//wait for pretty transition
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	//turn on target color
	if (target == lghtColor::Grn)
	{
		printf("idx#%d green\n", Itr->second);
		inLog("now Green", Itr->second);
	}
	else
	{
		printf("idx#%d red\n", Itr->second);
		inLog("now Red", Itr->second);
	}
	currLight = turnTo(target);
	//need to choose switching style, can all be yellow or not
	//calling nextPls here will make swithching on all red
	if (target == lghtColor::Red) { rtrI->nextPls(); }
	return 0;
}

int inline lght_t::getSmallDelay(int OrigDelay)
{
	return (OrigDelay / 10) > 0 ? (OrigDelay / 10) : 1;
}
