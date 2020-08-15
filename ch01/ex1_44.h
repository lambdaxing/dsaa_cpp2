#pragma once
#include <iostream>
#include <algorithm>

template<typename T1,typename T2>
auto mismatch(const T1* b, const T1* e, const T2* b2)
-> std::pair<const T1*,const T2*>
{
	while (b != e) {
		if (*b != *b2) break;
		++b, ++b2;
	}
	return { b,b2 };
}
 
int ex1_44()
{
	int n[5]{ 1,2,3,4,5 };
	double d[5]{ 1.0,2.0,3.0,4.0,5.5 };

	auto p1 = std::mismatch(std::cbegin(n), std::cend(n), std::cbegin(d));
	if (p1.first != std::cend(n))
		std::cout << *p1.first << " " << *p1.second << std::endl;
	else
		std::cout << *p1.second << std::endl;

	auto p2 = mismatch(std::cbegin(n), std::cend(n), std::cbegin(d));
	if (p2.first != std::cend(n))
		std::cout << *p2.first << " " << *p2.second << std::endl;
	else
		std::cout << *p2.second << std::endl;

	return 0;
}