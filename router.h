#pragma once
#include <map>
#include <mutex>
#include <atomic>
#include "safePtr.h"

class router_t
{
private:
public:
	safe_ptr<std::map<int, int>> queue;
	router_t();
	int getCurrIdx();
	void clearQueuePlace(int targetIdx);
	int pushRequest(int targetIdx, int targetPrior);
};