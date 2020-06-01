
#ifndef lowerTriangleAsIrregularArray_
#define lowerTriangleAsIrregularArray_

#include "myExceptions.h"
#include "ex7_15_16.h"

template<typename T>
class lowerTriangleAsIrregularArray
{
	friend std::istream& operator>>(std::istream& in, lowerTriangleAsIrregularArray<T>& m);
	friend std::ostream& operator<<(std::ostream& out, const lowerTriangleAsIrregularArray<T>& m);
public:
	lowerTriangleAsIrregularArray(int theN = 10);
	lowerTriangleAsIrregularArray(const lowerTriangleAsIrregularArray<T>& m);
	~lowerTriangleAsIrregularArray()
	{
		for (int i = 0; i < n; ++i) delete[] element[i]; delete[] element;
	}
	T get(int, int) const;
	void set(int, int, const T&);
	void clear();

	lowerTriangleAsIrregularArray<T> operator+(const lowerTriangleAsIrregularArray<T>& rhs) const;
	lowerTriangleAsIrregularArray<T>& operator+=(const lowerTriangleAsIrregularArray<T>& rhs);
	lowerTriangleAsIrregularArray<T> operator-(const lowerTriangleAsIrregularArray<T>& rhs) const;
	lowerTriangleAsIrregularArray<T>& operator-=(const lowerTriangleAsIrregularArray<T>& rhs);
	matrix<T> operator*(const lowerTriangleAsIrregularArray<T>& rhs) const;

	matrix<T> tranpose() const;

	lowerTriangleAsIrregularArray<T>& operator=(const lowerTriangleAsIrregularArray<T>& rhs);
private:
	int n;
	T** element;
};


template<typename T>
lowerTriangleAsIrregularArray<T>::lowerTriangleAsIrregularArray(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		throw illegalParameterValue("Matrix size must be > 0");

	n = theN;
	element = new T * [n];
	for (int i = 0; i < n; ++i)
		element[i] = new T[i + 1];
}

template<typename T>
lowerTriangleAsIrregularArray<T>::lowerTriangleAsIrregularArray(const lowerTriangleAsIrregularArray<T>& m)
{
	n = m.n;
	element = new T * [n];
	for (int i = 0; i < n; ++i)
	{
		element[i] = new T[i + 1];
		std::copy(m.element[i], m.element[i] + i + 1, element[i]);
	}
}

template <class T>
T lowerTriangleAsIrregularArray<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.

   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i < j)
		return 0;
	return element[i - 1][j - 1];
}

template<class T>
void lowerTriangleAsIrregularArray<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element

   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i < j && newValue != 0)        // |i-j| > 1 , M(i,j) = 0;
		throw illegalParameterValue
		("non-tridiagonal elements must be zero");
	if (i >= j)
		element[i - 1][j - 1] = newValue;
}

template<typename T>
void lowerTriangleAsIrregularArray<T>::clear()
{
	for (int i = 0; i < n; ++i)
		delete[] element[i];
	delete[] element;
	element = nullptr;
	n = 0;
}

template<typename T>
std::istream& operator>>(std::istream& in, lowerTriangleAsIrregularArray<T>& m)
{
	int theN;
	in >> theN;
	m.clear();
	m.n = theN;
	m.element = new T * [theN];
	T t{};
	for (int i = 1; i <= theN; ++i)
	{
		m.element[i - 1] = new T[i];
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			if (i < j) continue;
			m.set(i, j, t);
		}
	}
	return in;
}

std::istream& operator>>(std::istream& in, lowerTriangleAsIrregularArray<int>& m)
{
	int theN;
	in >> theN;
	m.clear();
	m.n = theN;
	m.element = new int * [theN];
	int t{};
	for (int i = 1; i <= theN; ++i)
	{
		m.element[i - 1] = new int[i];
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
std::ostream& operator<<(std::ostream& out, const lowerTriangleAsIrregularArray<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const lowerTriangleAsIrregularArray<int>& m)
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
lowerTriangleAsIrregularArray<T>& lowerTriangleAsIrregularArray<T>::operator=(const lowerTriangleAsIrregularArray<T>& rhs)
{
	if (this != &rhs)
	{// not copying to self
		clear();
		n = rhs.n;
		element = new T * [n];
		for (int i = 0; i < n; ++i)
		{
			element[i] = new T[i + 1];
			std::copy(rhs.element[i], rhs.element[i] + i + 1, element[i]);
		}
	}
	return *this;
}


template<typename T>
lowerTriangleAsIrregularArray<T>& lowerTriangleAsIrregularArray<T>::operator+=(const lowerTriangleAsIrregularArray<T>& rhs)
{
	if (n != rhs.n)
		throw matrixSizeMismatch();
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			if (i >= j)
				element[i - 1][j - 1] += rhs.element[i - 1][j - 1];
	}
	return *this;
}

template<typename T>
lowerTriangleAsIrregularArray<T> lowerTriangleAsIrregularArray<T>::operator+(const lowerTriangleAsIrregularArray<T>& rhs) const
{
	lowerTriangleAsIrregularArray<T> result = *this;
	result += rhs;
	return result;
}

template<typename T>
lowerTriangleAsIrregularArray<T>& lowerTriangleAsIrregularArray<T>::operator-=(const lowerTriangleAsIrregularArray<T>& rhs)
{
	if (n != rhs.n)
		throw matrixSizeMismatch();
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
			if (i >= j)
				element[i - 1][j - 1] -= rhs.element[i - 1][j - 1];
	}
	return *this;
}

template<typename T>
lowerTriangleAsIrregularArray<T> lowerTriangleAsIrregularArray<T>::operator-(const lowerTriangleAsIrregularArray<T>& rhs) const
{
	lowerTriangleAsIrregularArray<T> result = *this;
	result -= rhs;
	return result;
}

template<typename T>
matrix<T> lowerTriangleAsIrregularArray<T>::operator*(const lowerTriangleAsIrregularArray<T>& rhs) const
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

template<typename T>
matrix<T> lowerTriangleAsIrregularArray<T>::tranpose() const
{
	matrix<T> tran(n, n);
	using std::swap;
	for (int i = 1; i <=n ; ++i)
	{
		for (int j = 1; j <= n; ++j)
			tran(i, j) = get(j, i);
	}
	return tran;
}

void testEx7_26()
{
	lowerTriangleAsIrregularArray<int> m1;
	std::cin >> m1;
	matrix<int> m2 = m1.tranpose();
	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;
	matrix<int> m = m1 * m1;
	std::cout << m << std::endl;

}
#endif