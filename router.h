#pragma once

struct rqForG
{
	int idx;
	int priority;
};

class router_t
{
private:
	int TopIdx;
public:
	router_t();
	int getCurrIdx();
	void clearQueuePlace(int targetIdx);
	int pushRequest(rqForG rq);
};