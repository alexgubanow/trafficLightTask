#pragma once
#include "router.h"
#include "lightDriver.h"

class lght_t
{
private:
	/*current color of light*/
	lghtColor currLight;
	/*setted delay*/
	int delay;
	/*small delay for yellow*/
	int sdelay;
	/*Method to switch color from current to target, transition going with yellow in middle
	* args:
	* target - desired color
	*/
	int swLight(lghtColor target, router_t* rtrI);
	int getSmallDelay(int OrigDelay);
	/*flag of working posibility*/
	int volatile isCanRun;
public:
	/*iterator of this in global queue*/
	std::map<int, int>::iterator Itr;
	/*init method*/
	int init(lghtColor initColor, int _delay, std::map<int, int>::iterator _Itr);
	/*Method with main loop, can be stoped by switching isCanRun to 0*/
	int wLoop(router_t* rtrI);
	/*Method to stop running main loop
	* draft version
	*/
	int closeGate(router_t* rtrI);
};