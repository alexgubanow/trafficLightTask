#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "lght.h"
#include <thread>
#include <signal.h>
#include <iterator>

using namespace std;
safe_ptr<std::map<int, int>> queueG;
std::map<int, int>::iterator currTopIdx;

constexpr auto frstLght = 1;
constexpr auto maxLght = 5;

void posix_death_signal(int signum)
{
	printf("ooops, signum#%d\n", signum);
	signal(signum, SIG_DFL);
	exit(3);
}
void nextPls(safe_ptr<std::map<int, int>> queue)
{
	if (currTopIdx != std::prev(queueG->end()))
	{
		currTopIdx++;
	}
	else
	{
		currTopIdx = queue->begin();
	}
}

std::map<int, int>::iterator pushRequest(safe_ptr<std::map<int, int>> queue, int targetIdx, int targetPrior)
{
	std::map<int, int>::iterator itr = queue->insert(queue->lower_bound(targetPrior), std::pair<int, int>(targetPrior, targetIdx));	
	printf("queue now is: ");
	for (auto itr = queue->begin(); itr != queue->end(); itr++)
	{
		printf("idx#%d+%d, ", itr->second, itr->first);
	}
	printf("\n");
	return itr;
}
void wLoop(safe_ptr<std::map<int, int>> queue, std::map<int, int>::iterator ownItr)
{
	while (true)
	{
		//can be replaced by listening some port or other external interface
		while (currTopIdx != ownItr) {
		}
		//sw to green
		printf("idx#%d become green\n", ownItr->second);
		//swLight(lghtColor::Grn);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		//sw to red
		printf("idx#%d become red\n", ownItr->second);
		nextPls(queue);
		//swLight(lghtColor::Red);
		//wait for setted delay
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

}
int main(int argc, char* argv[])
{
	signal(SIGSEGV, posix_death_signal);
	//router_t rtr;
	srand((unsigned char)time(NULL));
	//std::vector<lght_t> tLightStack;
	std::vector<std::map<int, int>::iterator> tLightStack;
	//idx has to be > 0
	for (int i = frstLght; i < maxLght; i++)
	{
		tLightStack.push_back(pushRequest(queueG, i, (rand() % 100)));
	}
	currTopIdx = queueG->begin();
	for (size_t i = 0; i != tLightStack.size(); i++)
	{
		/*lght_t tmp;
		tmp.init(lghtColor::Red, 500, rand() % 100, i, &rtr);
		tLightStack.push_back(tmp);*/
		std::thread thr(&wLoop, queueG, tLightStack[i]);
		thr.detach();
	}
	while (true)
	{
	}
	return 0;
}