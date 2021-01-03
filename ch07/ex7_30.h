#ifndef twoLowerTriangularMatrix_
#define twoLowerTriangularMatrix_

#include "myExceptions.h"

template<typename T>
class twoLowerTriangularMatrix
{
	friend std::istream& operator>>(std::istream& in, twoLowerTriangularMatrix<T>& m);
	friend std::ostream& operator<<(std::ostream& out, const twoLowerTriangularMatrix<T>& m);
public:
	twoLowerTriangularMatrix(int theN = 10);
	twoLowerTriangularMatrix(const twoLowerTriangularMatrix<T>& m);
	~twoLowerTriangularMatrix() { for (int i = 0; i < n; ++i) delete[] element[i]; delete[] element; }
	T get(int, int, int) const;
	void set(int, int, int, const T&);

	void printReally() const;
private:
	int n;
	T** element;
};

template<typename T>
twoLowerTriangularMatrix<T>::twoLowerTriangularMatrix(int theN)
{
	n = theN;
	element = new T * [n + 1];
	for (int i = 0; i < n + 1; ++i)
		element[i] = new T[n];
}

template<typename T>
twoLowerTriangularMatrix<T>::twoLowerTriangularMatrix(const twoLowerTriangularMatrix<T>& m)
{
	n = m.n;
	element = new T * [n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		element[i] = new T[n];
		std::copy(m.element[i], m.element[i] + n, element[i]);
	}
}

template<typename T>
T twoLowerTriangularMatrix<T>::get(int p, int i, int j) const
{

	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();
	if (i < j)
		return 0;

	if (p == 1)
		return element[j - 1][i - 1];
	else if (p == 2)
		return element[i][j - 1];
	else
		throw illegalParameterValue("the first parameter of twoLowerTriangularMatrix::get() must be 1 or 2.");
}

template<typename T>
void twoLowerTriangularMatrix<T>::set(int p, int i, int j, const T& newValue)
{
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	// (i,j) in lower triangle iff i >= j
	if (i >= j)
	{
		if (p == 1)
			element[j - 1][i - 1] = newValue;
		else if (p == 2)
			element[i][j - 1] = newValue;
		else
			throw illegalParameterValue("the first parameter of twoLowerTriangularMatrix::get() must be 1 or 2.");
	}
	else
		if (newValue != 0)
			throw illegalParameterValue
			("elements not in lower triangle must be zero");
}

template<typename T>
std::istream& operator>>(std::istream& in, twoLowerTriangularMatrix<T>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	m.element = new T * [theN + 1];
	for (int i = 0; i < theN + 1; ++i)
		m.element[i] = new T[theN];
	T t{};
	for (int i = 1; i <= theN; ++i)
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			m.set(1, i, j, t);
		}
	for (int i = 1; i <= theN; ++i)
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			m.set(2, i, j, t);
		}

	return in;
}

std::istream& operator>>(std::istream& in, twoLowerTriangularMatrix<int>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	m.element = new int * [theN + 1];
	for (int i = 0; i < theN + 1; ++i)
		m.element[i] = new int[theN];
	int t{};
	for (int i = 1; i <= theN; ++i)
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			m.set(1, i, j, t);
		}
	for (int i = 1; i <= theN; ++i)
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			m.set(2, i, j, t);
		}

	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const twoLowerTriangularMatrix<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(1,i, j) << " ";
		out << std::endl;
	}
	out << std::endl;
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(2, i, j) << " ";
		out << std::endl;
	}
	out << std::endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, const twoLowerTriangularMatrix<int>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(1, i, j) << " ";
		out << std::endl;
	}
	out << std::endl;
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(2, i, j) << " ";
		out << std::endl;
	}
	out << std::endl;
	return out;
}

template<typename T>
void twoLowerTriangularMatrix<T>::printReally() const
{
	for (int i = 0; i < n + 1; ++i)
	{
		for (int j = 0; j < n; ++j)
			std::cout << element[i][j] << " ";
		std::cout << std::endl;
	}
}

void testEx7_30()
{
	twoLowerTriangularMatrix<int> m1;
	std::cin >> m1;
	std::cout << std::endl;
	std::cout << m1 << std::endl;
	m1.printReally();
}

#endif
