// some algorithms about polynomial

#ifndef ALGORITHMS_POLY_
#define ALGORITHMS_POLY_

#include <iostream>
#include <algorithm>
#include <iterator>

// calculate the value of the n-order polynomial at point x, and the coefficient is coeff[0:n]
// example: 5 * x^3 - 4 * x^2 + x + 7;  notice: the order is ^ ,coeff = [7,1,-4,5]
template<typename T>
T polyEval(T coeff[], int n, const T& x)
{
	T y = 1, value = coeff[0];
	for (int i = 1; i <= n; ++i)
	{
		y *= x;
		value += y * coeff[i];
	}
	return value;
}

// coeff = [7 1 -4 5]
template<typename T>
T horner(T coeff[], int n, const T& x)
{
	T value = coeff[n];
	for (int i = 1; i <= n; ++i)
		value = value * x + coeff[n - i];
	return value;
}


// test
int testPolyEval()
{
	int a[6] = { 1, 2, 3, 4, 5, 6 };

	// output the coefficients
	std::cout << "The coefficients a[0:5] are ";
	std::copy(a, a + 6, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "The value at 2 is " << polyEval(a, 5, 2) << std::endl;
	std::cout << "The value at 1 is " << polyEval(a, 5, 1) << std::endl;
	std::cout << "The value at 0 is " << polyEval(a, 5, 0) << std::endl;
	return 0;
}

int testHorner()
{
	int a[6] = { 1, 2, 3, 4, 5, 6 };

	// output the coefficients
	std::cout << "The coefficients a[0:5] are ";
	std::copy(a, a + 6, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << "The value at 2 is " << horner(a, 5, 2) << std::endl;
	std::cout << "The value at 1 is " << horner(a, 5, 1) << std::endl;
	std::cout << "The value at 0 is " << horner(a, 5, 0) << std::endl;
	return 0;
}

#endif // !ALGORITHMS_POLY_
