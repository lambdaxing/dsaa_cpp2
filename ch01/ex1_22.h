#pragma once
#include <math.h>
#include <stdexcept>
#include <iostream>

// 1)
// A(1,2) = 2^2 = 4;
// A(2,1) = A(1,2) = 4;
// A(2,2) = A(1,A(2,1)) = A(1,4) = 2^4 = 16;

// 2)
// basics: (i = 1 && j >= 1) => 2^j;
// recursion: The other two conditions

// 3)
int A(int i, int j)
{
	if (i == 1 && j >= 1)return pow(2, j);
	else if (i >= 2 && j == 1) return A(i - 1, 2);
	else if (i >= 2 && j >= 2) return A(i - 1, A(i, j - 1));
	else throw std::runtime_error("A(i,j),i and j must >= 1");
}

int ex1_22()
{
	std::cout << A(1, 2) << std::endl;
	std::cout << A(2, 1) << std::endl;
	std::cout << A(2, 2) << std::endl;
	return 0;
}