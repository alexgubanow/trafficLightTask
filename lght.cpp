#include "lght.h"
#include <stdio.h>
#include <chrono>
#include <thread>
using namespace std;

int lght_t::init(lghtColor initColor, int _delay, int _priority, int _idx, router_t* _routerInst)
{
	printf("init of lght#: %d\n", _idx);
	isCanRun = 1;
	routerInst = _routerInst;
	idx = _idx;
	currLight = initColor;
	delay = _delay;
	priority = _priority;
	return 0;
}
int lght_t::wLoop()
{
	rqForG request;
	while (isCanRun)
	{
		//update info for request
		request.idx = idx;
		request.priority = priority + idx;
		//pushing request (idx+priority) to queue
		routerInst->pushRequest(request);
		//can be replaced by listening some port or other external interface
		while (routerInst->getCurrIdx() != idx) {}
		//sw to green
		swLight(lghtColor::Grn);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		//sw to red
		swLight(lghtColor::Red);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	return closeGate();
}
int lght_t::closeGate()
{
	//going to red
	swLight(lghtColor::Red);
	//prevent to run main loop
	return isCanRun = 0;
}

int lght_t::swLight(lghtColor target)
{
	//remove self from Queue
	routerInst->clearQueuePlace(idx);
	//turn on yellow
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