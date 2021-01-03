#ifndef upperTriangularMatrix_
#define upperTriangularMatrix_

#include "myExceptions.h"
#include "ex7_15_16.h"

template<typename T>
class upperTriangularMatrix
{
	friend std::istream& operator>>(std::istream& in, upperTriangularMatrix<T>& m);
	friend std::ostream& operator<<(std::ostream& out, const upperTriangularMatrix<T>& m);
public:
    upperTriangularMatrix(int theN = 10);
	upperTriangularMatrix(const upperTriangularMatrix<T>& m);
    ~upperTriangularMatrix() { delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);
	int dimension()const { return n; }
private:
    int n;       // matrix dimension
    T* element;  // 1D array for lower triangle
};

template<class T>
upperTriangularMatrix<T>::upperTriangularMatrix(int theN)
{// Constructor.
   // validate theN
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T[n * (n + 1) / 2];
}

template<typename T>
upperTriangularMatrix<T>::upperTriangularMatrix(const upperTriangularMatrix<T>& m)
{
	n = m.n;
	element = new T[n * (n + 1) / 2];
	std::copy(m.element, m.element + n * (n + 1) / 2, element);
}

template <class T>
T upperTriangularMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    // (i,j) in lower triangle iff i >= j
    if (i <= j)
    {
        int index = 0;
		for (int a = 0; a < i - 1; ++a)
            index += n - a;
        index += j - i;
        return element[index];
    }
    else
        return 0;
}

template<class T>
void upperTriangularMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();


    // (i,j) in lower triangle iff i >= j
    if (i <= j)
    {
        int index = 0;
		for (int a = 0; a < i - 1; ++a)
            index += n - a;
        index += j - i;
        element[index] = newValue;
    }
    else
        if (newValue != 0)
            throw illegalParameterValue
            ("elements not in lower triangle must be zero");
}

template<typename T>
std::istream& operator>>(std::istream& in, upperTriangularMatrix<T>& m)
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
			if (i > j) continue;
			m.set(i, j, t);
		}
	}
	return in;
}

std::istream& operator>>(std::istream& in, upperTriangularMatrix<int>& m)
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
			if (i > j) continue;
			m.set(i, j, t);
		}
	}
	return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const upperTriangularMatrix<T>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const upperTriangularMatrix<int>& m)
{
	for (int i = 1; i <= m.n; ++i)
	{
		for (int j = 1; j <= m.n; ++j)
			out << m.get(i, j) << " ";
		out << std::endl;
	}
	return out;
}

void testEx7_27()
{
    upperTriangularMatrix<int> m1;
    std::cin >> m1;
    std::cout << m1 << std::endl;
}
#endif