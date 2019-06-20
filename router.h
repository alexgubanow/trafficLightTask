#pragma once
#include <map>
#include <mutex>
#include <atomic>
#include "safePtr.h"

//class router_t
//{
//private:
//	std::map<int, int>::iterator TopIdx;
//	safe_ptr<std::map<int, int>> queue;
//public:
//	router_t();
//	std::map<int, int>::iterator getTopIdx();
//	std::map<int, int>::iterator getFqe();
//	std::map<int, int>::iterator getLqe();
//	void setTopIdx(std::map<int, int>::iterator newTop);
//	int nextPls();
//	std::map<int, int>::iterator pushRequest(std::pair<int, int> rq);
//};

	std::map<int, int>::iterator getTopIdx();
	std::map<int, int>::iterator getFqe();
	std::map<int, int>::iterator getLqe();
	void setTopIdx(std::map<int, int>::iterator newTop);
	int nextPls();
	std::map<int, int>::iterator pushRequest(std::pair<int, int> rq);