
#ifndef tridiagonalByColumns_
#define tridiagonalByColumns_

#include "myExceptions.h"
#include "ex7_15_16.h"

template<typename T>
class tridiagonalByColumns
{
    friend std::istream& operator>>(std::istream& in, tridiagonalByColumns<T>& m);
    friend std::ostream& operator<<(std::ostream& out, const tridiagonalByColumns<T>& m);
public:
    tridiagonalByColumns(int theN = 10);
    tridiagonalByColumns(const tridiagonalByColumns<T>& m);
    ~tridiagonalByColumns() { delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);

    tridiagonalByColumns<T> operator+(const tridiagonalByColumns<T>& rhs) const;
    tridiagonalByColumns<T>& operator+=(const tridiagonalByColumns<T>& rhs);
    tridiagonalByColumns<T> operator-(const tridiagonalByColumns<T>& rhs) const;
    tridiagonalByColumns<T>& operator-=(const tridiagonalByColumns<T>& rhs);
    matrix<T> operator*(const tridiagonalByColumns<T>& rhs) const;
    //tridiagonalMatrix<T>& operator*=(const tridiagonalMatrix<T>& rhs);
    tridiagonalByColumns<T> tranpose() const;

    tridiagonalByColumns<T>& operator=(const tridiagonalByColumns<T>& rhs);
private:
	int n;
	T* element;
};


template<class T>
tridiagonalByColumns<T>::tridiagonalByColumns(int theN)
{// Constructor.
   // validate theN
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T[3 * n - 2]{};
}

template<typename T>
tridiagonalByColumns<T>::tridiagonalByColumns(const tridiagonalByColumns<T>& m)
{
    n = m.n;
    element = new T[3 * n - 2];
    std::copy(m.element, m.element + (3 * n - 2), element);
}

template <class T>
T tridiagonalByColumns<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.

   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    if (i - j > 1 || i - j < -1)
        return 0;

    if (j == 1)                 // first column
        return element[i - 1];
    else
        return element[2 + (j - 2) * 2 + i - 1];
}

template<class T>
void tridiagonalByColumns<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element

   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    if ((i - j > 1 || i - j < -1) && newValue != 0)        // |i-j| > 1 , M(i,j) = 0;
        throw illegalParameterValue
        ("non-tridiagonal elements must be zero");
    if (i - j <= 1 && i - j >= -1)
    {
        if (j == 1)                 // first column
            element[i - 1] = newValue;
        else
            element[2 + (j - 2) * 2 + i - 1] = newValue;
    }
}

template<typename T>
std::istream& operator>>(std::istream& in, tridiagonalByColumns<T>& m)
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

std::istream& operator>>(std::istream& in, tridiagonalByColumns<int>& m)
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
std::ostream& operator<<(std::ostream& out, const tridiagonalByColumns<T>& m)
{
    for (int i = 1; i <= m.n; ++i)
    {
        for (int j = 1; j <= m.n; ++j)
            out << m.get(i, j) << " ";
        out << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const tridiagonalByColumns<int>& m)
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
tridiagonalByColumns<T>& tridiagonalByColumns<T>::operator=(const tridiagonalByColumns<T>& rhs)
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
tridiagonalByColumns<T>& tridiagonalByColumns<T>::operator+=(const tridiagonalByColumns<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < 3 * n - 2; ++i)
        element[i] += rhs.element[i];
    return *this;
}

template<typename T>
tridiagonalByColumns<T> tridiagonalByColumns<T>::operator+(const tridiagonalByColumns<T>& rhs) const
{
    tridiagonalByColumns<T> result = *this;
    result += rhs;
    return result;
}

template<typename T>
tridiagonalByColumns<T>& tridiagonalByColumns<T>::operator-=(const tridiagonalByColumns<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < 3 * n - 2; ++i)
        element[i] -= rhs.element[i];
    return *this;
}

template<typename T>
tridiagonalByColumns<T> tridiagonalByColumns<T>::operator-(const tridiagonalByColumns<T>& rhs) const
{
    tridiagonalByColumns<T> result = *this;
    result -= rhs;
    return result;
}

template<typename T>
matrix<T> tridiagonalByColumns<T>::operator*(const tridiagonalByColumns<T>& rhs) const
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
tridiagonalByColumns<T> tridiagonalByColumns<T>::tranpose() const
{
    tridiagonalByColumns<T> tran(*this);
    using std::swap;
    for (int i = 1; i < 3 * n - 2; i += 3)
        swap(tran.element[i], tran.element[i + 1]);
    return tran;
}

void testEx7_22()
{
    tridiagonalByColumns<int> m1, m2;
    std::cin >> m1;
    m2 = m1.tranpose();
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    matrix<int> m = m1 * m2;
    std::cout << m << std::endl;

}
#endif
