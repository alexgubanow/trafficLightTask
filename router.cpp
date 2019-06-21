#include "router.h"
#include <thread>
router_t::router_t()
{
}

std::map<int, int>::iterator router_t::getTopIdx()
{
	//std::lock_guard<decltype(TopIdx)> lock(TopIdx);
	return TopIdx->getItr();
}

std::map<int, int>::iterator router_t::getFqe()
{
	return queue->begin();
}

std::map<int, int>::iterator router_t::getLqe()
{
	return std::prev(queue->end());
}

void router_t::setTopIdx(std::map<int, int>::iterator newTop)
{
	//std::lock_guard<decltype(TopIdx)> lock(TopIdx);
	TopIdx->setItr(newTop);
}

int router_t::nextPls()
{
	//std::lock_guard<decltype(TopIdx)> lock(TopIdx);
	std::this_thread::sleep_for(std::chrono::nanoseconds(100));
	//printf("before TopIdx#%d, ", TopIdx->getItr()->second);
	if (TopIdx->getItr() != getLqe())
	{
		TopIdx->incItr();
	}
	else
	{
		TopIdx->setItr(queue->begin());
	}
	//printf("after TopIdx#%d\n", TopIdx->getItr()->second);
	//in future can return time to wait until
	return 0;
}

std::map<int, int>::iterator router_t::pushRequest(std::pair<int, int> rq)
{
	std::map<int, int>::iterator itr = queue->insert(queue->lower_bound(rq.first), rq);
	printf("queue now is: ");
	for (auto itr = queue->begin(); itr != queue->end(); itr++)
	{
		printf("idx#%d+%d, ", itr->second, itr->first);
	}
	printf("\n");
	return itr;
}