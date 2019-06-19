#pragma once
//enum to describe possible colors of each traffic light
enum lghtColor { Red, Ylw, Grn };

class lght_t
{
private:
	lghtColor currLight;
	int delay;
	int* TopIdx;
	int priority;
	int swLight(lghtColor target);
	int pushRequest();
	int clearQueuePlace();
	int volatile isCanRun;
public:
	int idx;
	lght_t(lghtColor initColor, float _delay, int _priority, int _idx, int* _TopIdx);
	int wLoop();
	int closeGate();
};