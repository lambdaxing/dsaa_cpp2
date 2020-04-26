#pragma once
#include <iostream>
#include <algorithm>

int ex1_37()
{
	int sort1[5]{ 1,1,1,4,5 };
	int sort2[5]{ 5,4,4,2,1 };
	int nsort[5]{ 5,3,2,1,4 };

	std::cout << "sort1 is " << (std::is_sorted(std::cbegin(sort1), std::cend(sort1)) ? "sorted" : "not sorted.") << std::endl;
	std::cout << "sort2 is " << (std::is_sorted(std::cbegin(sort2), std::cend(sort2)) ? "sorted" : "not sorted.") << std::endl;
	std::cout << "nsort is " << (std::is_sorted(std::cbegin(nsort), std::cend(nsort)) ? "sorted" : "not sorted.") << std::endl;

	return 0;
}