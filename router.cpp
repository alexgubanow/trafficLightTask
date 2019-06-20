#include "router.h"

//router_t::router_t()
//{
//}
//
//std::map<int, int>::iterator router_t::getTopIdx()
//{
//	return TopIdx;
//}
//
//std::map<int, int>::iterator router_t::getFqe()
//{
//	return queue->begin();
//}
//
//std::map<int, int>::iterator router_t::getLqe()
//{
//	return std::prev(queue->end());
//}
//
//void router_t::setTopIdx(std::map<int, int>::iterator newTop)
//{
//	TopIdx = newTop;
//}
//
//int router_t::nextPls()
//{
//	if (TopIdx != getLqe())
//	{
//		TopIdx++;
//	}
//	else
//	{
//		TopIdx = queue->begin();
//	}
//	//in future can return time to wait until
//	return 0;
//}
//
//std::map<int, int>::iterator router_t::pushRequest(std::pair<int, int> rq)
//{
//	std::map<int, int>::iterator itr = queue->insert(queue->lower_bound(rq.first), rq);
//	printf("queue now is: ");
//	for (auto itr = queue->begin(); itr != queue->end(); itr++)
//	{
//		printf("idx#%d+%d, ", itr->second, itr->first);
//	}
//	printf("\n");
//	return itr;
//}

std::map<int, int>::iterator TopIdx;
safe_ptr<std::map<int, int>> queue;

std::map<int, int>::iterator getTopIdx()
{
	return TopIdx;
}

std::map<int, int>::iterator getFqe()
{
	return queue->begin();
}

std::map<int, int>::iterator getLqe()
{
	return std::prev(queue->end());
}

void setTopIdx(std::map<int, int>::iterator newTop)
{
	TopIdx = newTop;
}

int nextPls()
{
	if (TopIdx != getLqe())
	{
		TopIdx++;
	}
	else
	{
		TopIdx = queue->begin();
	}
	//in future can return time to wait until
	return 0;
}

std::map<int, int>::iterator pushRequest(std::pair<int, int> rq)
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