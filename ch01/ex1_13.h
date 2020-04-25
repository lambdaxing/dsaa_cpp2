#pragma once
#include <iostream>

template<typename T>
void changeLength1D(T*& x, size_t num, size_t n)
{
	auto p = new T[n];
	for (size_t i = 0; i < n; ++i)
	{
		if (i < num) p[i] = x[i];
		else p[i] = {};
	}
	delete[] x;
	x = p;
}

int ex1_13()
{
	auto  d = new double[5]{ 1.1,2.2,3.3,4.4,5.5 };

	changeLength1D(d, 5, 4);
	for (size_t i = 0; i != 4; ++i)
		std::cout << d[i] << " ";

	std::cout << std::endl;

	changeLength1D(d, 4, 6);
	for (size_t i = 0; i != 6; ++i)
		std::cout << d[i] << " ";

	std::cout << std::endl;

	delete[] d;
	return 0;
}