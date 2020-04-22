#pragma once
#include <iostream>
#include <string>

template<typename T, size_t N>
void fill(T(&t)[N], const T v)
{
	for (auto& i : t)
		i = v;
}

int ex1_3()
{
	int n[9];
	char c[9];
	std::string s[6];

	fill(n, 9);
	fill(c, '9');
	fill(s, std::string("6"));

	for (const auto& i : n)
		std::cout << i;
	std::cout << std::endl;

	for (const auto& i : c)
		std::cout << i;
	std::cout << std::endl;


	for (const auto& i : s)
		std::cout << i;
	std::cout << std::endl;


	return 0;
}