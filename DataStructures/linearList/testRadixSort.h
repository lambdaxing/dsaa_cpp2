#pragma once
#include "chain.h"

void testRadixSort()
{
	chain<int> c;
	for(int i = 1 ; i <= 100 ; i++)
		c.insert(0, i);
	std::cout << c << std::endl;
	c.radixSort();
	std::cout << c << std::endl;
	for (int i = 1; i <= 100; i++)
		c.insert(61, i / 2);
	std::cout << c << std::endl;
	c.radixSort();
	std::cout << c << std::endl;
}