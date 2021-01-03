#pragma once
#include "ex9_12.h"

void testEx9_12()
{
	linkedQueueFromExtendedChain<int> q;
	for (int i = 1; i < 25; ++i)
		q.push(i);
	q.output(std::cout);
	std::cout << std::endl;
	for (int i = 1; i < 24; ++i)
		q.pop();
	q.output(std::cout);
}