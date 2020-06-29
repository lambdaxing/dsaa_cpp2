#pragma once
#include "ex9_7.h"

void testEx9_7()
{
	arrayQueue<int> q;
	std::cin >> q;
	std::cout << q << std::endl;
	for (int i = 0; i < 10; ++i)
		q.pop();
	for (int i = 1; i < 22; ++i)
		q.push(i);
	std::cout << q << std::endl;
}