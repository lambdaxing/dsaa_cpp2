#pragma once

// calculate the value of the n-order polynomial at point x, and the coefficient is coeff[0:n]
// example: 5 * x^3 - 4 * x^2 + x + 7;  notice: the order is n -> 0 ,coeff = [7,1,-4,5]
// coeff is the coefficient, n is the highest order, x is the x in the polynomial
template<typename T>
T polyEval(T coeff[], int n, const T& x)
{	T y = 1, value = coeff[0];
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