#include "lght.h"
#include <stdio.h>
#include <chrono>
#include <thread>
using namespace std;

lght_t::lght_t(lghtColor initColor, float _delay, int _priority, int _idx, int * _TopIdx)
{
	isCanRun = 1;
	TopIdx = _TopIdx;
	idx = _idx;
	currLight = initColor;
	delay = _delay;
	priority = _priority;
}

int lght_t::wLoop()
{
	while (isCanRun)
	{
		//pushing request (idx+priority) to queue
		pushRequest();
		//can be replaced by listening some port or other external interface
		while (*TopIdx != idx) { }
		//sw to green
		swLight(lghtColor::Grn);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		//sw to red
		swLight(lghtColor::Grn);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	return closeGate();
}

int lght_t::closeGate()
{
	swLight(lghtColor::Red);
	return isCanRun = 0;
}

int lght_t::swLight(lghtColor target)
{
	//sw to yel
	clearQueuePlace();
	//recognize direction of transition
	//sw to target
	return 0;
}

int lght_t::pushRequest()
{
	return 0;
}

int lght_t::clearQueuePlace()
{
	return 0;
}
