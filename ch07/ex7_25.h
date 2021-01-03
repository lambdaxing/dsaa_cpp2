
#ifndef tridiagonalAsIrregularArray_
#define tridiagonalAsIrregularArray_

#include "myExceptions.h"
#include "ex7_15_16.h"

template<typename T>
class tridiagonalAsIrregularArray
{
	friend std::istream& operator>>(std::istream& in, tridiagonalAsIrregularArray<T>& m);
	friend std::ostream& operator<<(std::ostream& out, const tridiagonalAsIrregularArray<T>& m);
public:
	tridiagonalAsIrregularArray(int theN = 10);
	tridiagonalAsIrregularArray(const tridiagonalAsIrregularArray<T>& m);
	~tridiagonalAsIrregularArray()
	{
		for (int i = 0; i < n; ++i) delete[] element[i]; delete[] element;
	}
	T get(int, int) const;
	void set(int, int, const T&);
	void clear();

	tridiagonalAsIrregularArray<T> operator+(const tridiagonalAsIrregularArray<T>& rhs) const;
	tridiagonalAsIrregularArray<T>& operator+=(const tridiagonalAsIrregularArray<T>& rhs);
	tridiagonalAsIrregularArray<T> operator-(const tridiagonalAsIrregularArray<T>& rhs) const;
	tridiagonalAsIrregularArray<T>& operator-=(const tridiagonalAsIrregularArray<T>& rhs);
	matrix<T> operator*(const tridiagonalAsIrregularArray<T>& rhs) const;
	//tridiagonalMatrix<T>& operator*=(const tridiagonalMatrix<T>& rhs);
	tridiagonalAsIrregularArray<T> tranpose() const;

	tridiagonalAsIrregularArray<T>& operator=(const tridiagonalAsIrregularArray<T>& rhs);
private:
	int n;
	T** element;
};

template<typename T>
tridiagonalAsIrregularArray<T>::tridiagonalAsIrregularArray(int theN)
{// Constructor.
   // validate theN
	if (theN < 1)
		throw illegalParameterValue("Matrix size must be > 0");

	n = theN;
	element = new T* [n];
	for (int i = 0; i < n; ++i)
	{
		if (i == 0 || i == n - 1)
			element[i] = new T[2];
		else
			element[i] = new T[3];
	}
}

template<typename T>
tridiagonalAsIrregularArray<T>::tridiagonalAsIrregularArray(const tridiagonalAsIrregularArray<T>& m)
{
	n = m.n;
	element = new T * [n];
	for (int i = 0; i < n; ++i)
	{
		if (i == 0 || i == n - 1)
		{
			element[i] = new T[2];
			std::copy(m.element[i], m.element[i] + 2, element[i]);
		}
		else
		{
			element[i] = new T[3];
			std::copy(m.element[i], m.element[i] + 3, element[i]);
		}
	}
}

template <class T>
T tridiagonalAsIrregularArray<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.

   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if (i - j > 1 || i - j < -1)
		return 0;


	if (i == 1 || i == 2)
		return element[i - 1][j - 1];		// first row and second row
	else
		return element[i - 1][j - i + 1];
}

template<class T>
void tridiagonalAsIrregularArray<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element

   // validate i and j
	if (i < 1 || j < 1 || i > n || j > n)
		throw matrixIndexOutOfBounds();

	if ((i - j > 1 || i - j < -1) && newValue != 0)        // |i-j| > 1 , M(i,j) = 0;
		throw illegalParameterValue
		("non-tridiagonal elements must be zero");
	if (i - j <= 1 && i - j >= -1)
		if (i == 1 || i == 2)
			element[i - 1][j - 1] = newValue;		// first row and second row
		else
			element[i - 1][j - i + 1] = newValue;
}

template<typename T>
void tridiagonalAsIrregularArray<T>::clear()
{
	for (int i = 0; i < n; ++i)
		delete[] element[i];
	delete[] element;
	element = nullptr;
	n = 0;
}

template<typename T>
std::istream& operator>>(std::istream& in, tridiagonalAsIrregularArray<T>& m)
{
	int theN;
	in >> theN;
	m.clear();
	m.n = theN;
	m.element = new T * [theN];
	T t{};
	for (int i = 1; i <= theN; ++i)
	{
		if (i == 1 || i == theN)
			m.element[i - 1] = new T[2];
		else
			m.element[i - 1] = new T[3];
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			m.set(i, j, t);
		}
	}
	return in;
}

std::istream& operator>>(std::istream& in, tridiagonalAsIrregularArray<int>& m)
{
	int theN;
	in >> theN;
	m.clear();
	m.n = theN;
	m.element = new int* [theN];
	int t{};
	for (int i = 1; i <= theN; ++i)
	{
		if (i == 1 || i == theN)
			m.element[i - 1] = new int[2];
		else
			m.element[i - 1] = new int[3];
		for (int j = 1; j <= theN; ++j)
		{
			in >> t;
			m.set(i, j, t);
		}
	}
	return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const tridiagonalAsIrregularArray<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const tridiagonalAsIrregularArray<int>& m)
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
tridiagonalAsIrregularArray<T>& tridiagonalAsIrregularArray<T>::operator=(const tridiagonalAsIrregularArray<T>& rhs)
{
	if (this != &rhs)
	{// not copying to self
		clear();
		n = rhs.n;
		element = new T * [n];
		for (int i = 0; i < n; ++i)
		{
			if (i == 0 || i == n - 1)
			{
				element[i] = new T[2];
				std::copy(rhs.element[i], rhs.element[i] + 2, element[i]);
			}
			else
			{
				element[i] = new T[3];
				std::copy(rhs.element[i], rhs.element[i] + 3, element[i]);
			}
		}
	}
	return *this;
}


template<typename T>
tridiagonalAsIrregularArray<T>& tridiagonalAsIrregularArray<T>::operator+=(const tridiagonalAsIrregularArray<T>& rhs)
{
	if (n != rhs.n)
		throw matrixSizeMismatch();
	for (int i = 0; i < n; ++i)
	{
		if (i == 0 || i == n - 1)
		{
			for (int j = 0; j < 2; ++j)
				element[i][j] += rhs.element[i][j];
		}
		else
		{
			for (int j = 0; j < 3; ++j)
				element[i][j] += rhs.element[i][j];
		}
	}
	return *this;
}

template<typename T>
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::operator+(const tridiagonalAsIrregularArray<T>& rhs) const
{
	tridiagonalAsIrregularArray<T> result = *this;
	result += rhs;
	return result;
}

template<typename T>
tridiagonalAsIrregularArray<T>& tridiagonalAsIrregularArray<T>::operator-=(const tridiagonalAsIrregularArray<T>& rhs)
{
	if (n != rhs.n)
		throw matrixSizeMismatch();
	for (int i = 0; i < n; ++i)
	{
		if (i == 0 || i == n - 1)
		{
			for (int j = 0; j < 2; ++j)
				element[i][j] -= rhs.element[i][j];
		}
		else
		{
			for (int j = 0; j < 3; ++j)
				element[i][j] -= rhs.element[i][j];
		}
	}
	return *this;
}

template<typename T>
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::operator-(const tridiagonalAsIrregularArray<T>& rhs) const
{
	tridiagonalAsIrregularArray<T> result = *this;
	result -= rhs;
	return result;
}

template<typename T>
matrix<T> tridiagonalAsIrregularArray<T>::operator*(const tridiagonalAsIrregularArray<T>& rhs) const
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
tridiagonalAsIrregularArray<T> tridiagonalAsIrregularArray<T>::tranpose() const
{
	tridiagonalAsIrregularArray<T> tran(*this);
	using std::swap;
	for (int i = 1; i < n; ++i)
	{
		if (i > 1)
			swap(tran.element[i][0], tran.element[i - 1][2]);
		else
			swap(tran.element[i][0], tran.element[i - 1][1]);
	}
	return tran;
}

void testEx7_25()
{
	tridiagonalAsIrregularArray<int> m1, m2;
	std::cin >> m1;
	m2 = m1.tranpose();
	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;
	matrix<int> m = m1 * m2;
	std::cout << m << std::endl;

}

#endif
