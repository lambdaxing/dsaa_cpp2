#pragma once
#include <iostream>

template<typename T1, typename T2, size_t M, size_t N>
size_t mismatch(const T1(&t1)[N], const T2(&t2)[M])
{
	auto m = N > M ? M : N;
	for (size_t i = 0; i < m; ++i)
		if (t1[i] != t2[i]) return i;
	return m;
}

int ex1_7()
{
	int n[5]{ 1,2,3,4,5 };
	double d[5]{ 1.0,2.0,3.0,4.0,5.5 };

	std::cout << mismatch(n, d) << std::endl;

	return 0;
}