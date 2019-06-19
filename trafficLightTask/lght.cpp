#include "lght.h"
#include <stdio.h>

lght::lght(lghtColor initColor, float _delay, int _priority, int _idx)
{
	isCanRun = 1;
	idx = _idx;
	currLight = initColor;
	delay = _delay;
	priority = _priority;
}

int lght::wLoop()
{
	while (isCanRun)
	{
		//sw to green
		//wait for allowed delay
		//sw to red
	}
	return closeGate();
}

int lght::closeGate()
{
	swLight(lghtColor::Red);
	return isCanRun = 0;
}

int lght::isCanSw()
{
	return 0;
}

int lght::swLight(lghtColor)
{
	//recognize direction of transition
	//sw to yel
	//sw to target
	return 0;
}
int lght::swLight()
{
	return 0;
}