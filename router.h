#pragma once
#include <map>
#include "safePtr.h"
#include "safeItr.h"

/*Router to manage swithing quene of traffic lights*/
class router_t
{
private:
	/*iterator of active member in queue*/
	safe_ptr<SafeItr> TopIdx;
	/*sorted queue, first is priority, second is idx*/
	std::map<int, int> queue;
public:
	/*return iterator to active member in queue*/
	std::map<int, int>::iterator getTopIdx();
	/*return iterator to first member in queue*/
	std::map<int, int>::iterator getFqe();
	/*return iterator to last member in queue*/
	std::map<int, int>::iterator getLqe();
	/*Setup active iterator in queue*/
	void setTopIdx(std::map<int, int>::iterator newTop);
	/*Moving active iterator in queue*/
	int nextPls();
	/*Pushing given iterator into queue*/
	std::map<int, int>::iterator pushRequest(std::pair<int, int> rq);
};
