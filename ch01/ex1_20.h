#pragma once
#include <iostream>

// 1)
int Fibonacci(unsigned n)
{
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else return Fibonacci(n - 1) + Fibonacci(n - 2);
}

// 2) 
// example:
// Fibonacci(3) => Fibonacci(2) + Fibonacci(1) ,
// Fibonacci(2) => Fibonacci(1) + Fibonacci(0),
// Fibonacci(1) accumulate 2 times

// 3)
int Fibonacci2(unsigned n)
{
	int result = 0, fisrt = 1, second = 0;
	if (n == 1) result = 1;
	while (n-- > 1) {
		result = fisrt + second;
		second = fisrt;
		fisrt = result;
	}
	return result;
}

int ex1_20()
{
	for (unsigned i = 0; i < 10; ++i) 
	{
		std::cout << Fibonacci(i) << std::endl;
		std::cout << Fibonacci2(i) << std::endl;
	}
	return 0;
}