#pragma once

#include <iostream>
#include <vector>

template<typename T>
void copy(const T& b, const T& e,T& to)
{
	for (auto i = b; i != e; ++i) *to++ = *i;
}

int ex1_29()
{
	std::vector<int> vec{ 1,2,3,4,5 };
	std::vector<int> to1{ 6,7,8,9,10 };
	int num[5];

	copy(vec.cbegin(), vec.cend(), to1.begin());
	copy(to1.cbegin(), to1.cend(), num);

	for (size_t i = 0; i < 5; ++i) std::cout << to1[i] << " " << num[i] << std::endl;

	return 0;
}