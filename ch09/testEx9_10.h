#pragma once
#include "ex9_10.h"

void testEx9_10()
{
	dequeStack<int> s;
	for (int i = 1; i < 26; ++i)
		s.push(i);
	s.output(std::cout);
	std::cout << std::endl;
	for (int i = 1; i < 25; ++i)
		s.pop();
	s.output(std::cout);
}