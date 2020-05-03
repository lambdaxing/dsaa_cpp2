#pragma once

// 18)
// 2n
template <typename T>
T sum(T a[], int n)
{
	T theSum = 0;
	for (int i = 0; i < n; ++I)
		theSum += a[i];
	return theSum;
}

// 19)
// n-1
int factorial(int n)
{
	if (n <= 1) return 1;
	else return  n * factorial(n - 1);
}