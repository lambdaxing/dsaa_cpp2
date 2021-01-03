#pragma once
#include <iostream>
#include <algorithm>
#include <functional>

template<typename T>
bool is_sorted(const T* b, const T* e, std::function<bool(const T, const T)> f = std::less_equal<T>())
{
	auto i = b++;
	while (b != e) {
		if (!f(*i, *b))return false;
		++b, ++i;
	}
	return true;
}

int ex1_43()
{
	int sort1[5]{ 1,1,1,4,5 };
	int sort2[5]{ 5,4,4,2,1 };
	int nsort[5]{ 5,3,2,1,4 };

	std::cout << "sort1 is " << (std::is_sorted(std::cbegin(sort1), std::cend(sort1)) ? "sorted" : "not sorted.") << std::endl;
	std::cout << "sort2 is " << (std::is_sorted(std::cbegin(sort2), std::cend(sort2)) ? "sorted" : "not sorted.") << std::endl;
	std::cout << "nsort is " << (std::is_sorted(std::cbegin(nsort), std::cend(nsort)) ? "sorted" : "not sorted.") << std::endl;
	std::cout << std::endl;
	std::cout << "sort1 is " << (is_sorted(std::cbegin(sort1), std::cend(sort1)) ? "sorted" : "not sorted.") << std::endl;
	std::cout << "sort2 is " << (is_sorted(std::cbegin(sort2), std::cend(sort2)) ? "sorted" : "not sorted.") << std::endl;
	std::cout << "nsort is " << (is_sorted(std::cbegin(nsort), std::cend(nsort)) ? "sorted" : "not sorted.") << std::endl;

	return 0;
}