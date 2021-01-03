#ifndef toeplitzMatrix_
#define toeplitzMatrix_

#include "myExceptions.h"
#include "ex7_15_16.h"

template<typename T>
class toeplitzMatrix
{
	friend std::istream& operator>>(std::istream& in, toeplitzMatrix<T>& m);
	friend std::ostream& operator<<(std::ostream& out, const toeplitzMatrix<T>& m);
public:
	toeplitzMatrix(int theN = 10);
	toeplitzMatrix(const toeplitzMatrix<T>& m);
	~toeplitzMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);

	// 4)
	matrix<T> operator*(const toeplitzMatrix<T>& rhs) const;
	void printReally() const;
private:
	int n;
	T* element;
};

template<typename T>
toeplitzMatrix<T>::toeplitzMatrix(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		throw illegalParameterValue("Matrix size must be > 0");

	n = theN;
	element = new T[2 * n - 1];
}

template<typename T>
toeplitzMatrix<T>::toeplitzMatrix(const toeplitzMatrix<T>& m)
{
	n = m.n;
	element = new T[2 * n - 1];
	std::copy(m.element, m.element + 2 * n - 1, element);
}

template<typename T>
T toeplitzMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i == 1)
		return element[j - 1];
	else if (j == 1)
		return element[n + i - 2];
	else
		if (i > j)
			return element[n + (i - (j - 1)) - 2];
		else if (i < j)
			return element[j - (i - 1) - 1];
		else // =
			return element[0];
}

template<typename T>
void toeplitzMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i == 1)
		element[j - 1] = newValue;
	else if (j == 1)
		element[n + i - 2] = newValue;
	else
		if (i > j)
			element[n + (i - (j - 1)) - 2] = newValue;
		else if (i < j)
			element[j - (i - 1) - 1] = newValue;
		else // =
			element[0] = newValue;
}


template<typename T>
std::istream& operator>>(std::istream& in, toeplitzMatrix<T>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	delete[] m.element;
	m.element = new T[2 * theN - 1];
	T t{};
	for (int i = 1; i <= theN; ++i)
	{
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			m.set(i, j, t);
		}
	}
	return in;
}

std::istream& operator>>(std::istream& in, toeplitzMatrix<int>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	delete[] m.element;
	m.element = new int[2 * theN - 1];
	int t{};
	for (int i = 1; i <= theN; ++i)
	{
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			m.set(i, j, t);
		}
	}
	return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const toeplitzMatrix<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const toeplitzMatrix<int>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

template<typename T>
void toeplitzMatrix<T>::printReally() const
{
	for (int i = 0; i < 2 * n - 1; ++i)
		std::cout << element[i] << " ";
}

template<typename T>
matrix<T> toeplitzMatrix<T>::operator*(const toeplitzMatrix<T>& rhs) const
{
	if (n != rhs.n)
		throw matrixSizeMismatch();

	matrix<T> w(n, n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			T sum = 0;
			for (int k = 1; k <= n; ++k)
				sum += get(i, k) * rhs.get(k, j);
			w(i, j) = sum;
		}
	return w;
} 

void testEx7_36()
{
	toeplitzMatrix<int> m1;
	std::cin >> m1;
	std::cout << std::endl;
	std::cout << "m1:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << "m1.printReally():";
	m1.printReally();
	std::cout << std::endl;
	std::cout << "m = m1*m1:" << std::endl;
	matrix<int> m = m1 * m1;
	std::cout << m << std::endl;
}
#endif