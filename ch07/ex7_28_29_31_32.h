// lower triangle matrix
#ifndef lowerTriangularMatrix_
#define lowerTriangularMatrix_

#include "myExceptions.h"
#include "ex7_27.h"				// #include upperTriangularMatrix

template<class T>
class lowerTriangularMatrix
{
    friend std::istream& operator>>(std::istream& in, lowerTriangularMatrix<T>& m);
    friend std::ostream& operator<<(std::ostream& out, const lowerTriangularMatrix<T>& m);
public:
    lowerTriangularMatrix(int theN = 10);
	lowerTriangularMatrix(const lowerTriangularMatrix<T>& m);
    ~lowerTriangularMatrix() { delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);

	lowerTriangularMatrix<T> operator+(const lowerTriangularMatrix<T>& rhs) const;
	lowerTriangularMatrix<T>& operator+=(const lowerTriangularMatrix<T>& rhs);
	lowerTriangularMatrix<T> operator-(const lowerTriangularMatrix<T>& rhs) const;
	lowerTriangularMatrix<T>& operator-=(const lowerTriangularMatrix<T>& rhs);

	// ex7_31
	matrix<T> operator*(const lowerTriangularMatrix<T>& rhs) const;
	// ex7_32
	matrix<T> operator*(const upperTriangularMatrix<T>& rhs) const;
	upperTriangularMatrix<T> tranpose() const;

private:
    int n;       // matrix dimension
    T* element;  // 1D array for lower triangle
};

template<class T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int theN)
{// Constructor.
   // validate theN
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T[n * (n + 1) / 2];
}

template<typename T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(const lowerTriangularMatrix<T>& m)
{
	n = m.n;
	element = new T[n * (n + 1) / 2];
	std::copy(m.element, m.element + n * (n + 1) / 2, element);
}

template <class T>
T lowerTriangularMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    // (i,j) in lower triangle iff i >= j
    if (i >= j)
        return element[i * (i - 1) / 2 + j - 1];
    else
        return 0;
}

template<class T>
void lowerTriangularMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();


    // (i,j) in lower triangle iff i >= j
    if (i >= j)
        element[i * (i - 1) / 2 + j - 1] = newValue;
    else
        if (newValue != 0)
            throw illegalParameterValue
            ("elements not in lower triangle must be zero");
}

template<typename T>
std::istream& operator>>(std::istream& in, lowerTriangularMatrix<T>& m)
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

std::istream& operator>>(std::istream& in, lowerTriangularMatrix<int>& m)
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
std::ostream& operator<<(std::ostream& out, const lowerTriangularMatrix<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const lowerTriangularMatrix<int>& m)
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
lowerTriangularMatrix<T>& lowerTriangularMatrix<T>::operator+=(const lowerTriangularMatrix<T>& rhs)
{
	if (n != rhs.n)
		throw matrixSizeMismatch();
	for (int i = 1; i <= n * (n + 1) / 2; ++i)
	{
		element[i - 1] += rhs.element[i - 1];
	}
	return *this;
}

template<typename T>
lowerTriangularMatrix<T> lowerTriangularMatrix<T>::operator+(const lowerTriangularMatrix<T>& rhs) const
{
	lowerTriangularMatrix<T> result = *this;
	result += rhs;
	return result;
}

template<typename T>
lowerTriangularMatrix<T>& lowerTriangularMatrix<T>::operator-=(const lowerTriangularMatrix<T>& rhs)
{
	if (n != rhs.n)
		throw matrixSizeMismatch();
	for (int i = 1; i <= n * (n + 1) / 2; ++i)
	{
		element[i - 1] -= rhs.element[i - 1];
	}
	return *this;
}

template<typename T>
lowerTriangularMatrix<T> lowerTriangularMatrix<T>::operator-(const lowerTriangularMatrix<T>& rhs) const
{
	lowerTriangularMatrix<T> result = *this;
	result -= rhs;
	return result;
}

template<typename T>
upperTriangularMatrix<T> lowerTriangularMatrix<T>::tranpose() const
{
	upperTriangularMatrix<T> tran(n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			tran.set(i, j, get(j, i));

	return tran;
}

template<typename T>
matrix<T> lowerTriangularMatrix<T>::operator*(const lowerTriangularMatrix<T>& rhs) const
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
matrix<T> lowerTriangularMatrix<T>::operator*(const upperTriangularMatrix<T>& rhs) const
{
	if (n != rhs.dimension())
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

void testEx7_28()
{
	lowerTriangularMatrix<int> m1;
	std::cin >> m1;
	upperTriangularMatrix<int> m2 = m1.tranpose();
	std::cout << std::endl;
	matrix<int> mm = m1 * m1;
	matrix<int> m = m1 * m2;
	std::cout << "m1:" << std::endl;
	std::cout << m1 << std::endl;
	std::cout << "m2 = m1.tranpose():" << std::endl;
	std::cout << m2 << std::endl;
	std::cout << "mm = m1*m1:" << std::endl;
	std::cout << mm << std::endl;
	std::cout << "m = m1*m2:" << std::endl;
	std::cout << m << std::endl;
}
#endif