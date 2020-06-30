#pragma once
#include "ex9_13_2.h"

void testEx9_13_2()
{
	extendedLinkedQueue<int> q, q1, q2;
	std::cin >> q;
	q.split(q1, q2);
	std::cout << "q : " << q << std::endl << "q1: " << q1 << std::endl << "q2: " << q2 << std::endl;
	q.merge(q1, q2);
	std::cout << "q : " << q << std::endl << "q1: " << q1 << std::endl << "q2: " << q2 << std::endl;
}