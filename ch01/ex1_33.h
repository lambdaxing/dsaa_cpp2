#pragma once
#include <iostream>
#include <string>

//	I really didn't understand the exercise.

template<typename T, size_t N>
size_t count(const T(&)[N])
{
	return N;
}

int ex1_33()
{
	int i[9];
	char c[9];
	std::string s[6];

	std::cout << "i: " << count(i) << std::endl;
	std::cout << "c: " << count(c) << std::endl;
	std::cout << "s: " << count(s) << std::endl;

	return 0;
}