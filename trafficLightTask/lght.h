#pragma once
//enum to describe possible colors of each traffic light
enum lghtColor { Red, Ylw, Grn };

class lght
{
private:
	lghtColor currLight;
	float delay;
	int priority;
	int isCanSw();
	int swLight(lghtColor);
	int swLight();
	int volatile isCanRun;
public:
	int idx;
	lght(lghtColor initColor, float _delay, int _priority, int _idx);
	int wLoop();
	int closeGate();
};