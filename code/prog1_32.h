#pragma once
#include <iostream>
#include <algorithm>
#include <iterator>

template<typename T>
void permutations(T list[], int k, int m)
{
	using std::swap;
	if (k == m) {
		std::copy(list, list + m + 1, std::ostream_iterator<T>(cout, ""));
		std::cout << std::endl;
	}
	else {
		for (int i = k; i <= m; ++i)
		{
			swap(list[k], list[i]);
			permutations(list, k + 1, m);
			swap(list[k], list[i]);
		}
	}
}