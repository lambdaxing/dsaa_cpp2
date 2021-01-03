#ifndef cMatrix_
#define cMatrix_

#include "myExceptions.h"

template<typename T>
class cMatrix
{
	friend std::istream& operator>>(std::istream& in, cMatrix<T>& m);
	friend std::ostream& operator<<(std::ostream& out, const cMatrix<T>& m);
public:
	cMatrix(int theN = 10);
	cMatrix(const cMatrix<T>& m);
	~cMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);

	void printReally() const;
private:
	int n;
	T* element;
};

template<typename T>
cMatrix<T>::cMatrix(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		throw illegalParameterValue("Matrix size must be > 0");

	n = theN;
	element = new T[3 * n - 2];
}

template<typename T>
cMatrix<T>::cMatrix(const cMatrix<T>& m)
{
	n = m.n;
	element = new T[3 * n - 2];
	std::copy(m.element, m.element + 3 * n - 2, element);
}


template<typename T>
T cMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();
	
	if (i == 1)
		return element[j - 1];
	if (i == n)
		return element[2 * n - 2 + j - 1];
	if (j == 1)
		return element[n + i - 2];
	return 0;
}

template<typename T>
void cMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i == 1)
		element[j - 1] = newValue;
	else if (i == n)
		element[2 * n - 2 + j - 1] = newValue;
	else if (j == 1)
		element[n + i - 2] = newValue;
	else
		if (newValue != 0)
			throw illegalParameterValue
			("elements not in lower triangle must be zero");
}

template<typename T>
std::istream& operator>>(std::istream& in, cMatrix<T>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	delete[] m.element;
	m.element = new T[3 * theN - 2];
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

std::istream& operator>>(std::istream& in, cMatrix<int>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	delete[] m.element;
	m.element = new int[3 * theN - 2];
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
std::ostream& operator<<(std::ostream& out, const cMatrix<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const cMatrix<int>& m)
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
void cMatrix<T>::printReally() const
{
	for (int i = 0; i < 3 * n - 2; ++i)
		std::cout << element[i] << " ";
}

void testEx7_34()
{
	cMatrix<int> m1;
	std::cin >> m1;
	std::cout << std::endl;
	std::cout << "m1:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << "m1.printReally():";
	m1.printReally();
}
#endif