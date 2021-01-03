// diagonal matrix
#ifndef diagonalMatrix_
#define diagonalMatrix_

#include "myExceptions.h"

template<class T>
class diagonalMatrix
{
    friend std::istream& operator>>(std::istream& in, diagonalMatrix<T>& m);
    friend std::ostream& operator<<(std::ostream& out, const diagonalMatrix<T>& m);
public:
    diagonalMatrix(int theN = 10);
    diagonalMatrix(const diagonalMatrix<T>& m);
    ~diagonalMatrix() { delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);
    int dimension() const { return n; }

    diagonalMatrix<T> operator+(const diagonalMatrix<T>& rhs) const;
    diagonalMatrix<T>& operator+=(const diagonalMatrix<T>& rhs);
    diagonalMatrix<T> operator-(const diagonalMatrix<T>& rhs) const;
    diagonalMatrix<T>& operator-=(const diagonalMatrix<T>& rhs);
    diagonalMatrix<T> operator*(const diagonalMatrix<T>& rhs) const;
    diagonalMatrix<T>& operator*=(const diagonalMatrix<T>& rhs);
    diagonalMatrix<T> tranpose() const;

    diagonalMatrix<T>& operator=(const diagonalMatrix<T>& rhs);

private:
    int n;       // matrix dimension ¾ØÕóÎ¬Êý
    T* element;  // 1D array for diagonal elements
};

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{// Constructor.
   // validate theN
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T[n]{};
}

template<typename T>
diagonalMatrix<T>::diagonalMatrix(const diagonalMatrix<T>& m)
{
    n = m.n;
    element = new T[n];
    // copy each element of m
    std::copy(m.element,
        m.element + n,
        element);
}

template <class T>
T diagonalMatrix<T>::get(int i, int j) const
{// Return (i,j)th element of matrix.
   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    if (i == j)
        return element[i - 1];   // diagonal element
    else
        return 0;              // nondiagonal element
}

template<class T>
void diagonalMatrix<T>::set(int i, int j, const T& newValue)
{// Store newValue as (i,j)th element.
   // validate i and j
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();

    if (i == j)
        // save the diagonal value
        element[i - 1] = newValue;
    else
        // nondiagonal value, newValue must be zero
        if (newValue != 0)
            throw illegalParameterValue
            ("nondiagonal elements must be zero");
}

template<typename T>
diagonalMatrix<T>& diagonalMatrix<T>::operator+=(const diagonalMatrix<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < n; ++i)
        element[i] += rhs.element[i];
    return *this;
}

template<typename T>
diagonalMatrix<T> diagonalMatrix<T>::operator+(const diagonalMatrix<T>& rhs) const
{
    diagonalMatrix<T> result = *this;
    result += rhs;
    return result;
}

template<typename T>
diagonalMatrix<T>& diagonalMatrix<T>::operator-=(const diagonalMatrix<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < n; ++i)
        element[i] -= rhs.element[i];
    return *this;
}

template<typename T>
diagonalMatrix<T> diagonalMatrix<T>::operator-(const diagonalMatrix<T>& rhs) const
{
    diagonalMatrix<T> result = *this;
    result -= rhs;
    return result;
}

template<typename T>
diagonalMatrix<T>& diagonalMatrix<T>::operator*=(const diagonalMatrix<T>& rhs)
{
    if (n != rhs.n)
        throw matrixSizeMismatch();
    for (int i = 0; i < n; ++i)
        element[i] *= rhs.element[i];
    return *this;
}

template<typename T>
diagonalMatrix<T> diagonalMatrix<T>::operator*(const diagonalMatrix<T>& rhs) const
{
    diagonalMatrix<T> result = *this;
    result *= rhs;
    return result;
}

template<typename T>
diagonalMatrix<T> diagonalMatrix<T>::tranpose() const
{
    return *this;
}

template<typename T>
diagonalMatrix<T>& diagonalMatrix<T>::operator=(const diagonalMatrix<T>& rhs)
{
    if (this != &rhs)
    {// not copying to self
        delete[] element;
        n = rhs.n;
        element = new T[n];
        // copy each element
        std::copy(rhs.element,
            rhs.element + n,
            element);
    }
    return *this;
}

template<typename T>
std::istream& operator>>(std::istream& in, diagonalMatrix<T>& m)
{
    int theN;
    in >> theN;
    delete[] m.element;
    m.n = theN;
    m.element = new T[theN];
    for (int i = 0; i < theN; ++i)
        in >> m.element[i];
    return in;
}

std::istream& operator>>(std::istream& in, diagonalMatrix<int>& m)
{
    int theN;
    in >> theN;
    delete[] m.element;
    m.n = theN;
    m.element = new int[theN];
    for (int i = 0; i < theN; ++i)
        in >> m.element[i];
    return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const diagonalMatrix<T>& m)
{
    for (int i = 1; i <= m.n; ++i)
    {
        for (int j = 1; j <= m.n; ++j)
        {
            if (i == j) out << m.element[i - 1];
            else out << 0;
            out << " ";
        }
        out << std::endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const diagonalMatrix<int>& m)
{
    for (int i = 1; i <= m.n; ++i)
    {
        for (int j = 1; j <= m.n; ++j)
        {
            if (i == j) out << m.element[i - 1];
            else out << 0;
            out << " ";
        }
        out << std::endl;
    }
    return out;
}

void testEx7_20()
{
    diagonalMatrix<int> m1, m2;
    std::cin >> m1;
    m2 = m1.tranpose();
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    diagonalMatrix<int> m = m1 * m2;
    std::cout << m << std::endl;
}

#endif