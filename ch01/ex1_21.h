#pragma once
#include <iostream>

// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c1/e21.html  

// 1)
// f(5) = 8; f(7) = 11.

// 2)
// basics: n(even)/2; recursion: f(3n(odd)+1) 
// odd * 3 = odd => 3n = odd => 3n + 1 = odd + 1 = even => f(even) = even / 2;

// 3)
int accu(unsigned n)
{
	if (n % 2) return accu(3 * n + 1);
	else return n / 2;
}

// 4)
int accu2(unsigned n)
{
	if (n % 2) return (3 * n + 1) / 2;
	else  return n / 2;
}

int ex1_21()
{
	for (unsigned i = 0; i < 10; ++i)
	{
		std::cout << "f(" << i << "):\n";
		std::cout << accu(i) << std::endl;
		std::cout << accu(i) << std::endl;
	}
	return 0;
}