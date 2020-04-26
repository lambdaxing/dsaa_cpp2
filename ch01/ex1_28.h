#pragma once
#include <vector>
#include <iostream>
#include <functional>

template<typename T1, typename T2>
T2 accumulate(const T1 b, const T1 e, const T2& initialValue,std::function<T2(T2,T2)> f = std::plus<T2>() )
{
	T2 result = initialValue;
	for (auto i = b; i != e; ++i) result = f(result, *i);
	return result;
}

int ex1_28()
{
	std::vector<int> vec{ 1,2,3,4,5 };
	int num[5]{ 1,2,3,4,5 };
	std::cout << accumulate(vec.cbegin(), vec.cend(), 1, std::function<int(int, int)>(std::multiplies<int>())) << std::endl;
	std::cout << accumulate(std::begin(num), std::end(num), 0) << std::endl;
	std::cout << accumulate(num, num + 5, 1,std::function<int(int,int)>(std::multiplies<int>())) << std::endl;
	return 0;
}