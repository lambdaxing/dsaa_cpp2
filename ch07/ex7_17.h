#ifndef matrixAs2DArray_
#define matrixAs2DArray_

#include "myExceptions.h"

template<typename T>
class matrixAs2DArray
{
    friend std::istream& operator>>(std::istream&, matrixAs2DArray<T>&);
    friend std::ostream& operator<<(std::ostream&, const matrixAs2DArray<T>&);
public:
    matrixAs2DArray(int theRows = 0, int theColumns = 0);
    matrixAs2DArray(const matrixAs2DArray<T>&);
    ~matrixAs2DArray() { for (int i = 0; i < theRows; ++i) delete[] element[i]; delete[] element; }
    int rows() const { return theRows; }
    int columns() const { return theColumns; }
    T& operator()(int i, int j) const;
    matrixAs2DArray<T>& operator=(const matrixAs2DArray<T>&);
    matrixAs2DArray<T> operator+() const; // unary +
    matrixAs2DArray<T> operator+(const matrixAs2DArray<T>&) const;
    matrixAs2DArray<T> operator-() const; // unary minus
    matrixAs2DArray<T> operator-(const matrixAs2DArray<T>&) const;
    matrixAs2DArray<T> operator*(const matrixAs2DArray<T>&) const;
    matrixAs2DArray<T>& operator+=(const T&);

    // ex7_15
    matrixAs2DArray<T>& operator-=(const T&);
    matrixAs2DArray<T>& operator*=(const T&);
    matrixAs2DArray<T>& operator/=(const T&);

    // ex7_16
    matrixAs2DArray<T> tranpose();
private:
    int theRows,    // number of rows in matrix
        theColumns; // number of columns in matrix
    T** element;     // element array
};


template<class T>
matrixAs2DArray<T>::matrixAs2DArray(int theRows, int theColumns)
{// matrix constructor.
   // validate theRows and theColumns
    if (theRows < 0 || theColumns < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if ((theRows == 0 || theColumns == 0)
        && (theRows != 0 || theColumns != 0))
        throw illegalParameterValue
        ("Either both or neither rows and columns should be zero");

    // create the matrix
    this->theRows = theRows;
    this->theColumns = theColumns;
    element = new T * [theRows];
    for (int i = 0; i < theRows; ++i)
        element[i] = new T[theColumns];
}

template<class T>
matrixAs2DArray<T>::matrixAs2DArray(const matrixAs2DArray<T>& m)
{// Copy constructor for matrices.
   // create matrix
    theRows = m.theRows;
    theColumns = m.theColumns;
    element = new T * [theRows];
    for (int i = 0; i < theRows; ++i)
    {
        element[i] = new T[theColumns];
        // copy each element of m
        std::copy(m.element[i],
            m.element[i] + theColumns,
            element[i]);
    }
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator=(const matrixAs2DArray<T>& m)
{// Assignment. (*this) = m.
    if (this != &m)
    {// not copying to self
        for (int i = 0; i < theRows; ++i)
            delete[] element[i];
        delete[] element;
        theRows = m.theRows;
        theColumns = m.theColumns;
        element = new T * [theRows];
        for (int i = 0; i < theRows; ++i)
        {
            element[i] = new T[theColumns];
            // copy each element of m
            std::copy(m.element[i],
                m.element[i] + theColumns,
                element[i]);
        }
    }
    return *this;
}

template<class T>
T& matrixAs2DArray<T>::operator()(int i, int j) const
{// Return a reference to element (i,j).
    if (i < 1 || i > theRows
        || j < 1 || j > theColumns)
        throw matrixIndexOutOfBounds();
    return element[i-1][j-1];
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator+(const matrixAs2DArray<T>& m) const
{// Return w = (*this) + m.
    if (theRows != m.theRows
        || theColumns != m.theColumns)
        throw matrixSizeMismatch();

    // create result matrix w
    matrixAs2DArray<T> w(theRows, theColumns);
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            w.element[i][j] = element[i][j] + m.element[i][j];

    return w;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::
operator-(const matrixAs2DArray<T>& m) const
{// Return (*this) - m.
    if (theRows != m.theRows
        || theColumns != m.theColumns)
        throw matrixSizeMismatch();

    // create result matrix w
    matrixAs2DArray<T> w(theRows, theColumns);
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            w.element[i][j] = element[i][j] - m.element[i][j];


    return w;
}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator-() const
{// Return w = -(*this).

   // create result matrix w
    matrixAs2DArray<T> w(theRows, theColumns);
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            w.element[i][j] = -element[i][j];
    return w;

}

template<class T>
matrixAs2DArray<T> matrixAs2DArray<T>::operator*(const matrixAs2DArray<T>& m) const
{// matrix multiply.  Return w = (*this) * m.
    if (theColumns != m.theRows)
        throw matrixSizeMismatch();

    matrixAs2DArray<T> w(theRows, m.theColumns);  // result matrix

    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < m.theColumns; ++j)
        {
            T sum = 0;
            for (int k = 0; k < theColumns; ++k)
                sum += element[i][k] * m.element[k][j];
            w.element[i][j] = sum;
        }
    return w;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator+=(const T& x)
{// Increment all elements of *this by x.
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            element[i][j] += x;
    return *this;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const matrixAs2DArray<T>& m)
{// Put matrix m into the stream out.
 // One row per line.
    for (int i = 0; i < m.theRows; i++)
    {// do row i
        for (int j = 0; j < m.theColumns; j++)
            out << m.element[i][j] << "  ";

        // row i finished
        out << std::endl;
    }

    return out;
}

// for some reason compiler can't create this on its own
std::ostream& operator<<(std::ostream& out, const matrixAs2DArray<int>& m)
{// Put matrix m into the stream out.
 // One row per line.
    for (int i = 0; i < m.theRows; i++)
    {// do row i
        for (int j = 0; j < m.theColumns; j++)
            out << m.element[i][j] << "  ";

        // row i finished
        out << std::endl;
    }
    return out;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator-=(const T& x)
{// Decrease all elements of *this by x.
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            element[i][j] -= x;
    return *this;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator*=(const T& x)
{// Multip all elements of *this by x.
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            element[i][j] *= x;
    return *this;
}

template<class T>
matrixAs2DArray<T>& matrixAs2DArray<T>::operator/=(const T& x)
{// Division all elements of *this by x.
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            element[i][j] /= x;
    return *this;
}

template<typename T>
std::istream& operator>>(std::istream& in, matrixAs2DArray<T>& m)
{
    int theRows, theColumns;
    in >> theRows >> theColumns;
    matrixAs2DArray<T> t(theRows, theColumns);
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            in >> t.element[i][j];
    m = t;
    return in;
}

std::istream& operator>>(std::istream& in, matrixAs2DArray<int>& m)
{
    int theRows, theColumns;
    in >> theRows >> theColumns;
    matrixAs2DArray<int> t(theRows, theColumns);
    for (int i = 0; i < theRows; ++i)
        for (int j = 0; j < theColumns; ++j)
            in >> t.element[i][j];
    m = t;
    return in;
}

template<typename T>
matrixAs2DArray<T> matrixAs2DArray<T>::tranpose()
{
    matrixAs2DArray<T> tran(theColumns, theRows);
    for (int i = 1; i <= theRows; ++i)
        for (int j = 1; j <= theColumns; ++j)
            tran.element[j-1][i-1] = element[i-1][j-1];

    return tran;
}

void testEx7_17()
{
    matrixAs2DArray<int> m1, m2;
    std::cin >> m1;
    m2 = m1.tranpose();
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
    matrixAs2DArray<int> m = m1 * m2;
    std::cout << m << std::endl;
}
#endif