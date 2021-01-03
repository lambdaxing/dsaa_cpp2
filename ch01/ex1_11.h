#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

template<typename T, size_t N>
size_t count(const T(&)[N])
{
	if (N < 1) throw std::runtime_error("the size of array is less than 1");
	return N;
}

int ex1_11()
{
	std::string s[1];
	try { std::cout << "s: " << count(s) << std::endl; }
	catch (std::runtime_error e) { std::cout << e.what(); return 1; }
	return 0;
}