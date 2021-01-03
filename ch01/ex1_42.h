#pragma once
#include <iostream>
#include <numeric>

template<typename T>
void iota(T* b, T* e,T v)
{
	while (b != e) *b++ = v++;
}

int ex1_42()
{
	int n1[5]{ 1,2,3,4,5 };
	int n2[5]{ 1,2,3,4,5 };
	std::iota(std::begin(n1), std::end(n1), 2);
	for (const auto& i : n1)
		std::cout << i << std::endl;
	iota(std::begin(n2), std::end(n2), 2);
	for (const auto& i : n2)
		std::cout << i << std::endl;

	return 0;
}