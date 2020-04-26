#pragma once
#include <iostream>
#include <numeric>

int ex1_36()
{
	int n[5]{ 0,1,2,3,4 };
	std::iota(std::begin(n),std::end(n), 1);
	for (const auto& i : n)
		std::cout << i << std::endl;

	return 0;
}