#pragma once
#include "router.h"
#include "lightDriver.h"

class lght_t
{
private:
	/*pointer to instanse of router*/
	router_t* routerInst;
	/*current color of light*/
	lghtColor currLight;
	/*setted delay*/
	int delay;
	/*setted priority*/
	int priority;
	/*Method to switch color from current to target, transition going with yellow in middle
	* args:
	* target - desired color
	*/
	int swLight(lghtColor target);
	/*Method to get some small delay for yellow color on state*/
	int getSmallDelay();
	/*flag of working posibility*/
	int volatile isCanRun;
public:
	/*index of this*/
	int idx;
	lght_t(lghtColor initColor, float _delay, int _priority, int _idx, router_t* _routerInst);
	/*Method with main loop, can be stoped by switching isCanRun to 0*/
	int wLoop();
	/*Method to stop running main loop
	* draft version
	*/
	int closeGate();
};