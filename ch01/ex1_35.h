#pragma once
#include <iostream>
#include <numeric>
#include <functional>

int ex1_35()
{
	int n1[6]{ 0,1,2,3,4,5 };
	int n2[5]{ 6,7,8,9,10 };
	double d1[6]{ 0.0,1.1,2.2,3.3,4.4,5.5 };
	double d2[5]{ 6.6,7.7,8.8,9.9,10.10 };

	std::cout << std::inner_product(std::cbegin(n2),std::cend(n2),std::cbegin(n1),0) << std::endl;
	std::cout << std::inner_product(std::cbegin(d2), std::cend(d2), std::cbegin(d1), 0.0) << std::endl;

	return 0;
}