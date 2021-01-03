#pragma once
#include <iostream>
#include <string>
#include <algorithm>

int ex1_34()
{
	int n[9];
	char c[9];
	std::string s[6];

	std::fill(std::begin(n), std::end(n), 9);
	std::fill(std::begin(c), std::end(c), '9');
	std::fill(std::begin(s), std::end(s), std::string("6"));

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