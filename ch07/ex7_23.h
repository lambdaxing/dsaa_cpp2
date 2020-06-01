
#ifndef tridiagonalByRows_
#define tridiagonalByRows_

#include "myExceptions.h"
#include "ex7_15_16.h"

template<typename T>
class tridiagonalByRows
{
    friend std::istream& operator>>(std::istream& in, tridiagonalByRows<T>& m);
    friend std::ostream& operator<<(std::ostream& out, const tridiagonalByRows<T>& m);
public:
    tridiagonalByRows(int theN = 10);
    tridiagonalByRows(const tridiagonalByRows<T>& m);
    ~tridiagonalByRows() { delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);

    tridiagonalByRows<T> operator+(const tridiagonalByRows<T>& rhs) const;
    tridiagonalByRows<T>& operator+=(const tridiagonalByRows<T>& rhs);
    tridiagonalByRows<T> operator-(const tridiagonalByRows<T>& rhs) const;
    tridiagonalByRows<T>& operator-=(const tridiagonalByRows<T>& rhs);
    matrix<T> operator*(const tridiagonalByRows<T>& rhs) const;
    //tridiagonalMatrix<T>& operator*=(const tridiagonalMatrix<T>& rhs);
    tridiagonalByRows<T> tranpose() const;

    tridiagonalByRows<T>& operator=(const tridiagonalByRows<T>& rhs);
private:
    int n;
    T* element;
};


template<class T>
tridiagonalByRows<T>::tridiagonalByRows(int theN)
{// Constructor.
   // validate theN
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T[3 * n - 2]{};
}

template<typename T>
tridiagonalByRows<T>::tridiagonalByRows(const tridiagonalByRows<T>& m)
{
    n = m.n;
    element = new T[3 * n - 2];
    std::copy(m.element, m.element + (3 * n - 2), element);
}

template <class T>
T tridiagonalByRows<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.

   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    if (i - j > 1 || i - j < -1)
        return 0;

    if (i == 1)                 // first column
        return element[j - 1];
    else
        return element[2 + (i - 2) * 2 + j - 1];
}

template<class T>
void tridiagonalByRows<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element

   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    if ((i - j > 1 || i - j < -1) && newValue != 0)        // |i-j| > 1 , M(i,j) = 0;
        throw illegalParameterValue
        ("non-tridiagonal elements must be zero");
    if (i - j <= 1 && i - j >= -1)
    {
        if (i == 1)                 // first column
            element[j - 1] = newValue;
        else
            element[2 + (i - 2) * 2 + j - 1] = newValue;
    }
}

template<typename T>
std::istream& operator>>(std::istream& in, tridiagonalByRows<T>& m)
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

std::istream& operator>>(std::istream& in, tridiagonalByRows<int>& m)
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
std::ostream& operator<<(std::ostream& out, const tridiagonalByRows<T>& m)
{
    for (int i = 1; i <= m.n; ++i)
    {
        for (int j = 1; j <= m.n; ++j)
            out << m.get(i, j) << " ";
        out << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const tridiagonalByRows<int>& m)
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
tridiagonalByRows<T>& tridiagonalByRows<T>::operator=(const tridiagonalByRows<T>& rhs)
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
tridiagonalByRows<T>& tridiagonalByRows<T>::operator+=(const tridiagonalByRows<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < 3 * n - 2; ++i)
        element[i] += rhs.element[i];
    return *this;
}

template<typename T>
tridiagonalByRows<T> tridiagonalByRows<T>::operator+(const tridiagonalByRows<T>& rhs) const
{
    tridiagonalByRows<T> result = *this;
    result += rhs;
    return result;
}

template<typename T>
tridiagonalByRows<T>& tridiagonalByRows<T>::operator-=(const tridiagonalByRows<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < 3 * n - 2; ++i)
        element[i] -= rhs.element[i];
    return *this;
}

template<typename T>
tridiagonalByRows<T> tridiagonalByRows<T>::operator-(const tridiagonalByRows<T>& rhs) const
{
    tridiagonalByRows<T> result = *this;
    result -= rhs;
    return result;
}

template<typename T>
matrix<T> tridiagonalByRows<T>::operator*(const tridiagonalByRows<T>& rhs) const
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
tridiagonalByRows<T> tridiagonalByRows<T>::tranpose() const
{
    tridiagonalByRows<T> tran(*this);
    using std::swap;
    for (int i = 1; i < 3 * n - 2; i += 3)
        swap(tran.element[i], tran.element[i + 1]);
    return tran;
}

void testEx7_23()
{
    tridiagonalByRows<int> m1, m2;
    std::cin >> m1;
    m2 = m1.tranpose();
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    matrix<int> m = m1 * m2;
    std::cout << m << std::endl;

}
#endif
