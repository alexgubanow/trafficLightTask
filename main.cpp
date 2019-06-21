#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "lght.h"
#include <thread>
#include <signal.h>
#include <iterator>
#include "mLog.h"

using namespace std;

constexpr auto frstLght = 1;
constexpr auto maxLght = 4;

void posix_death_signal(int signum)
{
	printf("ooops, signum#%d\n", signum);
	//inLog("ooops, signum");
	//finishLog();
	signal(signum, SIG_DFL);
	exit(3);
}
int main(int argc, char* argv[])
{
	//lets attach method to atleast say bye on sigmentation fault
	signal(SIGSEGV, posix_death_signal);
	initLog("test.txt");
	inLog("sdcsd");
	inLog("tyj");
	inLog(",oki,");
	/*
	//router instance
	safe_ptr<router_t> rtr;
	//init of random machine
	srand((unsigned char)time(NULL));
	//stack of all lights
	std::vector<lght_t> tLightStack;
	//stack of iterators for future queue
	std::vector<std::map<int, int>::iterator> iteratorStack;
	//lets generate some amount of light iterators
	for (int i = frstLght; i < maxLght; i++)
	{
		//just pushing pair of random prior and current idx to stack of light iterators, probably possible to run in parallel
		iteratorStack.push_back(rtr->pushRequest(std::pair<int, int>(rand() % 100, i)));
	}
	//iterate over lights, create, init and run each
	for (size_t i = 0; i < iteratorStack.size(); i++)
	{
		//pushing to stack some blank light
		tLightStack.push_back(lght_t());
		//init of last light by given values
		tLightStack[i].init(lghtColor::Red, 500, iteratorStack[i]);
		//create thread with running wLoop of light, passing instance of safe_ptr<router_t>
		std::thread thr(&lght_t::wLoop, &(tLightStack[i]), rtr);
		//lunch it independent
		thr.detach();
	}
	//set new king
	rtr->setTopIdx(rtr->getFqe());
	while (true)
	{
	}*/
	finishLog();
	return 0;
}