#include "router.h"

router_t::router_t()
{
}

int router_t::getCurrIdx()
{
	return queue.back().idx;
}

void router_t::clearQueuePlace(int targetIdx)
{
	//possible low perfomance, has to be replaced
	using Iter = std::vector<rqForG>::const_iterator;
	for (Iter it = queue.begin(); it != queue.end(); it++) {
		if ((*it).idx == targetIdx)
		{
			queue.erase(it);
		}
	}
}
int router_t::pushRequest(rqForG rq)
{
	//possible low perfomance, has to be replaced
	using Iter = std::vector<rqForG>::const_iterator;
	Iter bestPlace = queue.begin();
	for (Iter it = queue.begin() + 1; it != queue.end(); it++)
	{
		if ((*(it)).priority > rq.priority)
		{
			break;
		}
		else
		{
			bestPlace = it - 1;
		}
	}
	queue.insert(bestPlace, rq);
	//in future can return time to wait until
	return 0;
}