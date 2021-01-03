#pragma once
#include <iostream>
#include <algorithm>

int ex1_38()
{
	int n[5]{ 1,2,3,4,5 };
	double d[5]{ 1.0,2.0,3.0,4.0,5.5 };

	auto p = std::mismatch(std::cbegin(n), std::cend(n), std::cbegin(d));
	if (p.first != std::cend(n))
		std::cout << *p.first << " " << *p.second << std::endl;
	else
		std::cout << *p.second << std::endl;

	return 0;
}