#include "lght.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include "mLog.h"
using namespace std;

int lght_t::init(lghtColor initColor, int _delay, std::map<int, int>::iterator _Itr)
{
	inLog("init of lght", _Itr->second, true);
	isCanRun = 1;
	Itr = _Itr;
	currLight = initColor;
	delay = _delay;
	sdelay = getSmallDelay(delay);
	return 0;
}
int lght_t::wLoop(router_t* rtrI)
{
	while (isCanRun)
	{
		//can be replaced by listening some port or other external interface
		while (rtrI->getTopIdx() != Itr) {}
		//sw to green
		swLight(lghtColor::Grn, rtrI);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//sw to red
		swLight(lghtColor::Red, rtrI);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return closeGate(rtrI);
}
int lght_t::closeGate(router_t* rtrI)
{
	/*its not thread safe, has to be rethinked*/
	//going to red
	swLight(lghtColor::Red, rtrI);
	//prevent to run main loop
	return isCanRun = 0;
}

int lght_t::swLight(lghtColor target, router_t* rtrI)
{
	//turn on yellow
	inLog("now Yellow", Itr->second, true);
	currLight = setLght(lghtColor::Ylw, Itr->second);
	//need to choose switching style, can all be yellow or not
	//calling nextPls here will make swithching on all yellow
	//if (target == lghtColor::Red) { rtrI->nextPls(); }
	//wait for pretty transition
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	//turn on target color
	if (target == lghtColor::Grn)
	{
		inLog("now Green", Itr->second, true);
	}
	else
	{
		inLog("now Red", Itr->second, true);
	}
	currLight = setLght(target, Itr->second);
	//need to choose switching style, can all be yellow or not
	//calling nextPls here will make swithching on all red
	if (target == lghtColor::Red) { rtrI->nextPls(); }
	return 0;
}

int inline lght_t::getSmallDelay(int OrigDelay)
{
	return (OrigDelay / 10) > 0 ? (OrigDelay / 10) : 1;
}