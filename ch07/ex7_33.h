#ifndef lowerSymmetricMatrix_
#define lowerSymmetricMatrix_

#include "myExceptions.h"

template<typename T>
class lowerSymmetricMatrix
{
	friend std::istream& operator>>(std::istream& in, lowerSymmetricMatrix<T>& m);
	friend std::ostream& operator<<(std::ostream& out, const lowerSymmetricMatrix<T>& m);
public:
	lowerSymmetricMatrix(int theN = 10);
	lowerSymmetricMatrix(const lowerSymmetricMatrix<T>& m);
	~lowerSymmetricMatrix() { delete[] element; }
	T get(int, int) const;
	void set(int, int, const T&);

	void printReally() const;
private:
	int n;
	T* element;
};

template<typename T>
lowerSymmetricMatrix<T>::lowerSymmetricMatrix(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		throw illegalParameterValue("Matrix size must be > 0");

	n = theN;
	element = new T[n * (n + 1) / 2];
}

template<typename T>
lowerSymmetricMatrix<T>::lowerSymmetricMatrix(const lowerSymmetricMatrix<T>& m)
{
	n = m.n;
	element = new T[n * (n + 1) / 2];
	std::copy(m.element, m.element + n * (n + 1) / 2, element);
}

template<typename T>
T lowerSymmetricMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i < j)
		return element[j * (j - 1) / 2 + i - 1];
	else
		return element[i * (i - 1) / 2 + j - 1];
}

template<typename T>
void lowerSymmetricMatrix<T>::set(int i, int j,const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i < j)
		element[j * (j - 1) / 2 + i - 1] = newValue;
	else
		element[i * (i - 1) / 2 + j - 1] = newValue;
}


template<typename T>
std::istream& operator>>(std::istream& in, lowerSymmetricMatrix<T>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	delete[] m.element;
	m.element = new T[theN * (theN + 1) / 2];;
	T t{};
	for (int i = 1; i <= theN; ++i)
	{
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			if (i < j) continue;
			m.set(i, j, t);
		}
	}
	return in;
}

std::istream& operator>>(std::istream& in, lowerSymmetricMatrix<int>& m)
{
	int theN;
	in >> theN;
	m.n = theN;
	delete[] m.element;
	m.element = new int[theN * (theN + 1) / 2];;
	int t{};
	for (int i = 1; i <= theN; ++i)
	{
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			if (i < j) continue;
			m.set(i, j, t);
		}
	}
	return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const lowerSymmetricMatrix<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const lowerSymmetricMatrix<int>& m)
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
void lowerSymmetricMatrix<T>::printReally() const
{
	for (int i = 0; i < n * (n + 1) / 2; ++i)
		std::cout << element[i] << " ";
}

void testEx7_33()
{
	lowerSymmetricMatrix<int> m1;
	std::cin >> m1;
	std::cout << std::endl;
	std::cout << "m1:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << "m1.printReally():";
	m1.printReally();
}
#endif