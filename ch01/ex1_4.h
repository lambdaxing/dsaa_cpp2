#pragma once
#include <iostream>

template<typename T1, typename T2, size_t N, size_t M>
T1 inner_product(const T1(&t1)[N], const T2(&t2)[M])
{
	auto j = N > M ? M : N;
	T1 temp{};
	for (size_t i = 0; i < j; ++i)
		temp += t1[i] * t2[i];
	return temp;
}

int ex1_4()
{
	int n1[6]{ 0,1,2,3,4,5 };
	int n2[5]{ 6,7,8,9,10 };
	double d1[6]{ 0.0,1.1,2.2,3.3,4.4,5.5 };
	double d2[5]{ 6.6,7.7,8.8,9.9,10.10 };

	std::cout << inner_product(n1, n2) << std::endl;
	std::cout << inner_product(d1, d2) << std::endl;

	return 0;
}