#include <iostream>
#include <vector>
#include <cstdlib> 
#include <time.h>
#include "lght.h"
#include <thread>

using namespace std;

void foo()
{
	// do stuff...
}

int main(int argc, char *argv[])
{
	router_t rtr;
	srand((unsigned char)time(NULL));
	std::vector<lght_t> tLightStack;
	for (int i = 4; i > 0; i--)
	{
		lght_t tmp; 
		tmp.init(lghtColor::Red, 500, rand() % 100, i, &rtr);
		tLightStack.push_back(tmp);
		std::thread thr(&lght_t::wLoop, &tLightStack.back());
		thr.detach();
	}
	while (true)
	{

	}
	return 0;
}