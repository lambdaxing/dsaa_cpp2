#pragma once
#include <iostream>

int factorial(int n)
{
	int result = 1;
	while (n > 1) result *= n--;
	return result;
}

int ex1_19()
{
	std::cout << factorial(5) << std::endl;
	return 0;
}