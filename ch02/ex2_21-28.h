#pragma once

// 21)
// numberOfRows * numberOfColumns
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c2/e21.htm
template <typename T>
void matrixAdd(T** a, T** b, T** c, int numberOfRows, int numberOfColumns)
{
	for (int i = 0; i < numberOfRows; ++i)
		for (int j = 0; j < numberOfColumns; ++j)
			c[i][j] = a[i][j] + b[i][j];
}

// 22)
// rows(rows-1)/2

// 23)
// n^3
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c2/e23.htm
template <typename T>
void squareMatrixMultiply(T** a, T** b, T** c, int n)
{
	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j)
		{
			T sum = 0;
			for (int k = 0; k < n; ++k)
				sum += a[i][k] * b[k][j];
			c[i][j] = sum;
		}
}

// 24)
// m * p * n
template<typename T>
void matrixMultiply(T** a, T** b, T** c, int m, int n, int p)
{
	for (int i = 0; i < m; ++i) 
		for (int j = 0; j < p; ++j)
		{
			T sum = 0;
			for (int k = 0; k < n; ++k)
				sum += a[i][k] * b[k][j];
			c[i][j] = sum;
		}
}

// 25)
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c2/e25.htm

// 26)
// 2-24
// 2(n-1)
// best:1; worst:n + 2(n-1) = 3n-2;
template<typename T>
bool minmax(T a[], int n, int& indexOfMin, int& indexOfMax)
{
	if (n < 1) return false;
	indexOfMin = indexOfMax = 0;
	for (int i = 1; i < n; ++i)
	{
		if (a[indexOfMin] > a[i]) indexOfMin = i;
		if (a[indexOfMax] < a[i]) indexOfMax = i;
	}
	return true;
}
// 2-25
// n - 1
// best:1; worst: n + n-1 = 2n -1
template<typename T>
bool minmax(T a[], int n, int& indexOfMin, int& indexOfMax)
{
	if (n < 1) return false;
	indexOfMin = indexOfMax = 0;
	for (int i = 1; i < n; ++i)
		if (a[indexOfMin] > a[i]) indexOfMin = i;
		else if (a[indexOfMax] < a[i]) indexOfMax = i;
	return true;
}

// 27)
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c2/e27.htm

// 28)
// worst:n+1; best:1
// faster: 2-26,because the times of comparing is less; 
template <typename T>
int sequentialSearch(T a[], int n, const T& x)
{
	a[n] = x;
	int i;
	for (i = 0; a[i] != x; ++i);
	if (i == n) return -1;
	return i;
}