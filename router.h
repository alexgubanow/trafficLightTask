#pragma once
#include <vector>

struct rqForG
{
	int idx;
	int priority;
};

class router_t
{
private:
	std::vector<rqForG> queue;
public:
	router_t();
	int getCurrIdx();
	void clearQueuePlace(int targetIdx);
	int pushRequest(rqForG rq);
};