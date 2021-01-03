#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
size_t count(const T* b, const T* e, const T& v)
{
	size_t result = 0;
	while (b != e) {
		if (*b == v) ++result;
		++b;
	}
	return result;
}

int ex1_39()
{
	int n[5]{ 1,2,3,4,5 };
	std::vector<std::string> vec{ "hello",",","world","!","!" };

	std::cout << count(std::cbegin(n), std::cend(n), 5) << std::endl;
	std::cout << count(vec.cbegin(), vec.cend(), std::string("!")) << std::endl;
	std::cout << std::count(std::cbegin(n), std::cend(n), 5) << std::endl;
	std::cout << std::count(vec.cbegin(), vec.cend(), std::string("!")) << std::endl;
	return  0;
}