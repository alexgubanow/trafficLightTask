#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "lght.h"
#include <thread>
#include <signal.h>
#include <iterator>

using namespace std;

constexpr auto frstLght = 1;
constexpr auto maxLght = 5;

void posix_death_signal(int signum)
{
	printf("ooops, signum#%d\n", signum);
	signal(signum, SIG_DFL);
	exit(3);
}
int main(int argc, char* argv[])
{
	signal(SIGSEGV, posix_death_signal);
	//router_t rtr;
	srand((unsigned char)time(NULL));
	std::vector<lght_t> tLightStack;
	std::vector<std::map<int, int>::iterator> iteratorStack;
	//idx has to be > 0
	for (int i = frstLght; i < maxLght; i++)
	{
		iteratorStack.push_back(pushRequest(std::pair<int, int>(rand() % 100, i)));
	}
	for (size_t i = 0; i < iteratorStack.size(); i++)
	{
		//printf("creating idx#%d\n", iteratorStack[i]->second);
		tLightStack.push_back(lght_t());
		tLightStack[i].init(lghtColor::Red, 500, iteratorStack[i]);
		std::thread thr(&lght_t::wLoop, &(tLightStack[i]));
		thr.detach();
	}
	setTopIdx(getFqe());
	while (true)
	{
		//printf("idx#%d become green\n", getTopIdx()->second);
	}
	return 0;
}