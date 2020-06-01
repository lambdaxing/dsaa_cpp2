// tridiagonal matrix

#ifndef tridiagonal_
#define tridiagonal_

#include "myExceptions.h"
#include "ex7_15_16.h"      // #include "matrix.h"

template<class T>
class tridiagonalMatrix
{
    friend std::istream& operator>>(std::istream& in, tridiagonalMatrix<T>& m);
    friend std::ostream& operator<<(std::ostream& out, const tridiagonalMatrix<T>& m);
public:
    tridiagonalMatrix(int theN = 10);
    tridiagonalMatrix(const tridiagonalMatrix<T>& m);
    ~tridiagonalMatrix() { delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);

    tridiagonalMatrix<T> operator+(const tridiagonalMatrix<T>& rhs) const;
    tridiagonalMatrix<T>& operator+=(const tridiagonalMatrix<T>& rhs);
    tridiagonalMatrix<T> operator-(const tridiagonalMatrix<T>& rhs) const;
    tridiagonalMatrix<T>& operator-=(const tridiagonalMatrix<T>& rhs);
    matrix<T> operator*(const tridiagonalMatrix<T>& rhs) const;
    //tridiagonalMatrix<T>& operator*=(const tridiagonalMatrix<T>& rhs);
    tridiagonalMatrix<T> tranpose() const;

    tridiagonalMatrix<T>& operator=(const tridiagonalMatrix<T>& rhs);

private:
    int n;       // matrix dimension
    T* element;  // 1D array for tridiagonal
};

template<class T>
tridiagonalMatrix<T>::tridiagonalMatrix(int theN)
{// Constructor.
   // validate theN
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T[3 * n - 2]{};
}

template<typename T>
tridiagonalMatrix<T>::tridiagonalMatrix(const tridiagonalMatrix<T>& m)
{
    n = m.n;
    element = new T[3 * n - 2];
    std::copy(m.element, m.element + (3 * n - 2), element);
}

template <class T>
T tridiagonalMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.

   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    // determine lement to return
    switch (i - j)
    {
    case 1: // lower diagonal
        return element[i - 2];
    case 0: // main diagonal
        return element[n + i - 2];
    case -1: // upper diagonal
        return element[2 * n + i - 2];
    default: return 0;
    }
}

template<class T>
void tridiagonalMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element

   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    switch (i - j)
    {
    case 1: // lower diagonal
        element[i - 2] = newValue; break;
    case 0: // main diagonal
        element[n + i - 2] = newValue; break;
    case -1: // upper diagonal
        element[2 * n + i - 2] = newValue; break;
    default: if (newValue != 0)
        throw illegalParameterValue
        ("non-tridiagonal elements must be zero");
    }
}

template<typename T>
tridiagonalMatrix<T>& tridiagonalMatrix<T>::operator+=(const tridiagonalMatrix<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < 3 * n - 2; ++i)
        element[i] += rhs.element[i];
    return *this;
}

template<typename T>
tridiagonalMatrix<T> tridiagonalMatrix<T>::operator+(const tridiagonalMatrix<T>& rhs) const
{
    tridiagonalMatrix<T> result = *this;
    result += rhs;
    return result;
}

template<typename T>
tridiagonalMatrix<T>& tridiagonalMatrix<T>::operator-=(const tridiagonalMatrix<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < 3 * n - 2; ++i)
        element[i] -= rhs.element[i];
    return *this;
}

template<typename T>
tridiagonalMatrix<T> tridiagonalMatrix<T>::operator-(const tridiagonalMatrix<T>& rhs) const
{
    tridiagonalMatrix<T> result = *this;
    result -= rhs;
    return result;
}

template<typename T>
matrix<T> tridiagonalMatrix<T>::operator*(const tridiagonalMatrix<T>& rhs) const
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
tridiagonalMatrix<T> tridiagonalMatrix<T>::tranpose() const
{
    tridiagonalMatrix<T> tran(*this);
    using std::swap;
    for (int i = 0; i < n - 1; ++i)
        swap(tran.element[i], tran.element[i + 2 * n - 1]);
    return tran;
}

template<typename T>
tridiagonalMatrix<T>& tridiagonalMatrix<T>::operator=(const tridiagonalMatrix<T>& rhs)
{
    if (this != &rhs)
    {// not copying to self
        delete[] element;
        n = rhs.n;
        element = new T[3 * n - 2];
        // copy each element
        std::copy(rhs.element, rhs.element + (3 * n - 2), element);
    }
    return *this;
}

template<typename T>
std::istream& operator>>(std::istream& in, tridiagonalMatrix<T>& m)
{
    int theN;
    in >> theN;
    delete[] m.element;
    m.n = theN;
    m.element = new T[3 * theN - 2];
    T t{};
    for (int i = 1; i <= theN; ++i)
        for (int j = 1; j <= theN; ++j)
        {
            in >> t;
            m.set(i, j, t);
        }
    return in;
}

std::istream& operator>>(std::istream& in, tridiagonalMatrix<int>& m)
{
    int theN;
    in >> theN;
    delete[] m.element;
    m.n = theN;
    m.element = new int[3 * theN - 2];
    int t{};
    for (int i = 1; i <= theN; ++i)
        for (int j = 1; j <= theN; ++j)
        {
            in >> t;
            m.set(i, j, t);
        }
    return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const tridiagonalMatrix<T>& m)
{
    for (int i = 1; i <= m.n; ++i)
    {
        for (int j = 1; j <= m.n; ++j)
            out << m.get(i, j) << " ";
        out << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const tridiagonalMatrix<int>& m)
{
    for (int i = 1; i <= m.n; ++i)
    {
        for (int j = 1; j <= m.n; ++j)
            out << m.get(i, j) << " ";
        out << std::endl;
    }
    return out;
}

void testEx7_21()
{
    tridiagonalMatrix<int> m1, m2;
    std::cin >> m1;
    m2 = m1.tranpose();
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    matrix<int> m = m1 * m2;
    std::cout << m << std::endl;
}


//input:
//4
//2 1 0 0
//3 1 3 0
//0 5 2 7
//0 0 9 0
//
//output:
//2 1 0 0
//3 1 3 0
//0 5 2 7
//0 0 9 0
//
//2 3 0 0
//1 1 5 0
//0 3 2 9
//0 0 7 0
//
//5 7 5 0
//7 19 11 27
//5 11 78 18
//0 27 18 81

#endif