#pragma once
#include <map>
class SafeItr
{
private:
	std::map<int, int>::iterator itr;
public:
	SafeItr() {};
	~SafeItr() {};
	void setItr(std::map<int, int>::iterator newItr)
	{
		itr = newItr;
	}
	void incItr()
	{
		itr++;
	}
	std::map<int, int>::iterator getItr()
	{
		return itr;
	}
};