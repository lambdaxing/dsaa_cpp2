#pragma once
#include <iostream>

template <typename T>
void rank(T a[], int n, int r[])
{
	for (int i = 0; i < n; ++i)
		r[i] = 0;			// init

	for (int i = 1; i < n; ++i)
		for (int j = 0; j < i; ++j)
			if (a[j] <= a[i]) ++r[i];
			else ++r[j];
}

int ex2_9()
{
	int a[9]{ 3,2,6,5,9,4,7,1,8 };
	int r[9];
	rank(a, 9, r);
	for (const auto& i : r)
		std::cout << i << " ";
	std::cout << std::endl;
	return 0;
}