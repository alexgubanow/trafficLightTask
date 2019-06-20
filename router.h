#pragma once
#include <map>
#include <mutex>

struct rqForG
{
	int idx;
	int priority;
};

class router_t
{
private:
	std::map<int, int> queue;
public:
	router_t();
	std::mutex queueMtx;
	int getCurrIdx();
	void clearQueuePlace(int targetIdx);
	int pushRequest(int targetIdx, int targetPrior);
};