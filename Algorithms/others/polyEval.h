#pragma once

#include <iostream>
#include <algorithm> // has copy
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

using namespace std;
int testPolyEval()
{
	int a[6] = { 1, 2, 3, 4, 5, 6 };

	// output the coefficients
	cout << "The coefficients a[0:5] are ";
	copy(a, a + 6, ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << "The value at 2 is " << polyEval(a, 5, 2) << endl;
	cout << "The value at 1 is " << polyEval(a, 5, 1) << endl;
	cout << "The value at 0 is " << polyEval(a, 5, 0) << endl;
	return 0;
}