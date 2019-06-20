#include "router.h"

router_t::router_t()
{
}

int router_t::getCurrIdx()
{
	return queue->begin()->first;
}

void router_t::clearQueuePlace(int targetIdx)
{
	//possible low perfomance, has to be replaced
	for (auto it = queue->begin(); it != queue->end(); it++) {
		if (it->first == targetIdx)
		{
			queue->erase(it);
		}
	}
}
int router_t::pushRequest(int targetIdx, int targetPrior)
{
	std::lock_guard<decltype(queue)>lock(queue);
	printf("incoming rq  idx#%d\n", targetIdx);
	if (queue->size() == 0)
	{
		printf("queue is zero\n");
		queue->insert(std::pair<int, int>(targetIdx, targetPrior));
	}
	else
	{
		//possible low perfomance, has to be replaced
		auto bestPlace = queue->begin();
		for (auto it = std::prev(queue->begin(), 1); it != queue->end(); it++)
		{
			if (it->second > targetPrior)
			{
				break;
			}
			else
			{
				bestPlace = std::prev(it, 1);
			}
		}
		queue->insert(bestPlace, std::pair<int, int>(targetIdx, targetPrior));
	}
	printf("queue now is: ");
	for (auto itr = queue->begin(); itr != queue->end(); itr++)
	{
		printf("idx#%d, ", itr->first);
	}
	printf("\n");
	//in future can return time to wait until
	return 0;
}