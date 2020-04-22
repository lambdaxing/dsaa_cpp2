#include <iostream>

template<typename T,size_t N>
void iota(T(&t)[N], const T& v)
{
	size_t curr = 0;
	for (auto& i : t)
		t[i] = v + curr++;
}

int ex1_5() 
{
	int n[5]{ 0,1,2,3,4 };
	iota(n, 1);
	for (const auto& i : n)
		std::cout << i << std::endl;

	return 0;
}