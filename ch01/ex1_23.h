#pragma once
#include <iostream>

// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c1/e27.htm

// 1)
// gcd(20,30) = 10;
// gcd(112,42) = 14

// 2)
// basics: gcd(x,y) = x (y=0);
// recursion: gcd(x,y) = gcd(y,x mod y) (y>0);
// x mod y = 0 ( x/y = integer || x < y)

// 3)
unsigned gcd(unsigned x, unsigned y)
{
	if (y == 0) return x;
	else return gcd(y, x % y);
}

int ex1_23()
{
	std::cout << gcd(20, 30) << std::endl;
	std::cout << gcd(112, 42) << std::endl;
	return 0;
}