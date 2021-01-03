#ifndef antidiagonalMatrix_
#define antidiagonalMatrix_

#include "myExceptions.h"
template<typename T>
class antidiagonalMatrix
{
	friend std::istream& operator>>(std::istream& in, antidiagonalMatrix<T>& m);
	friend std::ostream& operator<<(std::ostream& out, const antidiagonalMatrix<T>& m);
public:
	antidiagonalMatrix(int theN = 10);
	antidiagonalMatrix(const antidiagonalMatrix<T>& m);
	~antidiagonalMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);

	void printReally() const;
private:
	int n;
	T* element;
};


template<typename T>
antidiagonalMatrix<T>::antidiagonalMatrix(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		throw illegalParameterValue("Matrix size must be > 0");

	n = theN;
	element = new T[n];
}

template<typename T>
antidiagonalMatrix<T>::antidiagonalMatrix(const antidiagonalMatrix<T>& m)
{
	n = m.n;
	element = new T[n];
	std::copy(m.element, m.element + n, element);
}

template<typename T>
T antidiagonalMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i + j != n + 1)
		return 0;
	else
		return element[i - 1];
}

template<typename T>
void antidiagonalMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i + j == n + 1)
		element[i - 1] = newValue;
	else
		if (newValue != 0)
			throw illegalParameterValue
			("elements not in lower triangle must be zero");
}

template<typename T>
std::istream& operator>>(std::istream& in, antidiagonalMatrix<T>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	delete[] m.element;
	m.element = new T[theN];
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

std::istream& operator>>(std::istream& in, antidiagonalMatrix<int>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	delete[] m.element;
	m.element = new int[theN];
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
std::ostream& operator<<(std::ostream& out, const antidiagonalMatrix<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const antidiagonalMatrix<int>& m)
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
void antidiagonalMatrix<T>::printReally() const
{
	for (int i = 0; i < n; ++i)
		std::cout << element[i] << " ";
}

void testEx7_35()
{
	antidiagonalMatrix<int> m1;
	std::cin >> m1;
	std::cout << std::endl;
	std::cout << "m1:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << "m1.printReally():";
	m1.printReally();
}
#endif