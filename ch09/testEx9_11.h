#pragma once
#include "ex9_11.h"

void testEx9_11()
{
	dequeQueue<int> q;
	q.input(std::cin);
	q.output(std::cout);
	std::cout << std::endl;
	for (int i = 0; i < 10; ++i)
		q.pop();
	for (int i = 1; i < 22; ++i)
		q.push(i);
	q.output(std::cout);
}