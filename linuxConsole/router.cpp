#include "router.h"
#include <thread>
#include "mLog.h"

/*return iterator to active member in queue*/
std::map<int, int>::iterator router_t::getTopIdx()
{
	return TopIdx;
}

/*return iterator to first member in queue*/
std::map<int, int>::iterator router_t::getFqe()
{
	return queue.begin();
}
/*return iterator to last member in queue*/
std::map<int, int>::iterator router_t::getLqe()
{
	return queue.end();
}
/*Setup active iterator in queue*/
void router_t::setTopIdx(std::map<int, int>::iterator newTop)
{
	//set active iterator in queue to given one
	TopIdx = newTop;
}

/*Moving active iterator in queue*/
int router_t::nextPls()
{
	//increment iterator of active member
	TopIdx = std::next(TopIdx);
	//check if currently last member in queue is active
	if (TopIdx == std::next(std::next(queue.end())))
	{
		//set iterator of active member to first
		TopIdx = queue.begin();
	}
	inLog("next idx", TopIdx->second, true);
	//in future can return time to wait until
	return 0;
}
/*Pushing given iterator into queue*/
std::map<int, int>::iterator router_t::pushRequest(std::pair<int, int> rq)
{
	//finding best place as first element equal to or greater than given priority, or end()
	return queue.insert(queue.lower_bound(rq.first), rq);
}