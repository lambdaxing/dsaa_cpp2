#pragma once
#include "ex9_8.h"

void testEx9_8()
{
	arrayQueue<int> q, q1, q2;
	std::cin >> q;
	q.split(q1, q2);
	std::cout << "q : " << q << std::endl << "q1: " << q1 << std::endl << "q2: " << q2 << std::endl;
	q.merge(q1, q2);
	std::cout << "q : " << q << std::endl << "q1: " << q1 << std::endl << "q2: " << q2 << std::endl;
}