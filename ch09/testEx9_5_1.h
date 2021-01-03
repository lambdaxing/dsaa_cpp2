#pragma once
#include "ex9_5_1.h"

void testEx9_5_1()
{
	arrayQueue<int> q, q1, q2;
	std::cin >> q;
	q.split(q1, q2);
	std::cout << "q : " << q << std::endl << "q1: " << q1 << std::endl << "q2: " << q2 << std::endl;
	q.merge(q1, q2);
	std::cout << "q : " << q << std::endl << "q1: " << q1 << std::endl << "q2: " << q2 << std::endl;
}