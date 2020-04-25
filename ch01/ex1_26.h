#pragma once
#include <string>
#include <iostream>

// 1)
// g(4) = g(3),4,g(3) = g(2),3,g(2),4,g(2),3,g(2) = g(1),2,g(1),3,g(1),2,g(1),4,g(1),2,g(1),3,g(1),2,g(1)
// = 1,2,1,3,1,2,1,4,1,2,1,3,1,2,1 ;

// 2)
// basics: g(1) = 1;
// recursion: g(n) = g(n-1),n,g(n-1); 
// n-1, ... , 1 => g(1) = 1;

// 3)
std::string g(unsigned n)
{
	if (n == 1) return std::to_string(1);
	else return g(n - 1) + std::to_string(n) + g(n - 1);
}

int ex1_26()
{
	std::cout << g(4) << std::endl;
	return 0;
}