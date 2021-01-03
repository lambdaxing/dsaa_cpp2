#pragma once
#include <iostream>

template<typename T, size_t N>
bool is_sorted(const T(&t)[N])
{
	bool less = false, greater = false;
	for (size_t i = 1; i < N; ++i)
	{
		if (t[i] < t[i - 1]) {
			if (greater) return false;
			if (!less) less = true;
		}
		else if (t[i] > t[i - 1]) {
			if (less) return false;
			if (!greater) greater = true;
		}
	}
	return true;
}

int ex1_6()
{
	int sort1[5]{ 1,1,1,4,5 };
	int sort2[5]{ 5,4,4,2,1 };
	int nsort[5]{ 5,3,2,1,4 };

	std::cout << "sort1 is " << (is_sorted(sort1) ? "sorted" : "not sorted.") << std::endl;
	std::cout << "sort2 is " << (is_sorted(sort2) ? "sorted" : "not sorted.") << std::endl;
	std::cout << "nsort is " << (is_sorted(nsort) ? "sorted" : "not sorted.") << std::endl;

	return 0;
}