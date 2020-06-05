// sparse matrix using an extended array list

#ifndef sparseMatrixByCols_
#define sparseMatrixByCols_

#include <iostream>
#include "matrixTerm.h"
#include "extendedArrayList.h"
#include "myExceptions.h"

template<class T>
class sparseMatrixByCols
{
    friend std::ostream& operator<<(std::ostream&, sparseMatrixByCols<T>&);
    friend std::istream& operator>>(std::istream&, sparseMatrixByCols<T>&);
public:
    sparseMatrixByCols() = default;
    sparseMatrixByCols(int row, int col) :rows(row), cols(col) {}
    sparseMatrixByCols(const sparseMatrixByCols<T>&);
    ~sparseMatrixByCols() {};
    T get(int, int) const;
    void set(int, int, const T& newValue);

    void transpose(sparseMatrixByCols<T>& b);
    void add(sparseMatrixByCols<T>& b, sparseMatrixByCols<T>& c);

    sparseMatrixByCols<T> operator*(const sparseMatrixByCols<T>& rhs) const;
private:
    int rows,    // number of rows in matrix
        cols;    // number of columns in matrix
    arrayList<matrixTerm<T> > terms;
    // list of nonzero terms
};

template<typename T>
sparseMatrixByCols<T> sparseMatrixByCols<T>::operator*(const sparseMatrixByCols<T>& rhs) const
{
    if (cols != rhs.rows)
        throw matrixSizeMismatch();

    sparseMatrixByCols<T> w(rows, rhs.cols);

    for (int i = 1; i <= rows; ++i)
        for (int j = 1; j <= rhs.cols; ++j)
        {
            T sum = get(i, 1) * rhs.get(1, j);
            for (int k = 2; k <= cols; ++k)
                sum += get(i, k) * rhs.get(k, j);
            w.set(i, j, sum);
        }
    return w;
}

template<typename T>
sparseMatrixByCols<T>::sparseMatrixByCols(const sparseMatrixByCols<T>& m)
{
    rows = m.rows;
    cols = m.cols;
    terms = m.terms;
}

template<typename T>
T sparseMatrixByCols<T>::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > rows || j > cols)
        throw matrixIndexOutOfBounds();

    // binarySearch
    int index = j * rows + i;
    int begin = 0, end = terms.size() - 1;
    while (begin <= end)
    {
        int middle = (begin + end) / 2;
        int fIndex = terms[middle].col * rows + terms[middle].row;
        if (index > fIndex)
            begin = middle + 1;
        else if (index < fIndex)
            end = middle - 1;
        else
            return terms[middle].value;
    }

    // not found in the terms , it is 0
    return 0;
}

template <typename T>
void sparseMatrixByCols<T>::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > rows || j > cols)
        throw matrixIndexOutOfBounds();

    int index = j * rows + i, Iindex = 0, b;
    for (b = 0; b < terms.size(); ++b)
    {
        Iindex = terms[b].col * rows + terms[b].row;

        if (Iindex == index)            // cover primary element
        {
            if (newValue == 0)          // newValue is 0 , delete primary element
                terms.erase(b);
            else
                terms[b].value = newValue;
            return;
        }

        if (Iindex > index)
        {
            if (newValue != 0)
                terms.insert(b, { i,j,newValue });
            // a new element in terms(i,j) is 0
            // nothing to do
            return;
        }
    }

    if (index > Iindex && newValue != 0)        // the index of setting element is largest than the index of last element in the terms 
        terms.insert(b, { i,j,newValue });
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, sparseMatrixByCols<T>& x)
{// Put x in output stream.

   // put matrix characteristics
    out << "rows = " << x.rows << " columns = "
        << x.cols << std::endl;
    out << "nonzero terms = " << x.terms.size() << std::endl;

    // put terms, one per line
    for (auto i = x.terms.begin();
        i != x.terms.end(); i++)
        out << "a(" << (*i).row << ',' << (*i).col
        << ") = " << (*i).value << std::endl;

    return out;
}

// overload >>
template<class T>
std::istream& operator>>(std::istream& in, sparseMatrixByCols<T>& x)
{// Input a sparse matrix.

   // input matrix characteristics
    int numberOfTerms;
    std::cout << "Enter number of rows, columns, and #terms"
        << std::endl;
    in >> x.rows >> x.cols >> numberOfTerms;

    // check out
    if (x.rows < 0 || x.cols < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if ((x.rows == 0 || x.cols == 0)
        && (x.rows != 0 || x.cols != 0))
        throw illegalParameterValue
        ("Either both or neither rows and columns should be zero");

    // set size of x.terms and ensure enough capacity
    x.terms.reSet(numberOfTerms);

    // input terms
    matrixTerm<T> mTerm;
    int cRow = 0, cCol = 0;
    for (int i = 0; i < numberOfTerms; i++)
    {
        std::cout << "Enter row, column, and value of term "
            << (i + 1) << std::endl;
        in >> mTerm.row >> mTerm.col >> mTerm.value;

        // determine if the value is zero 
        if (mTerm.value == 0)
            throw illegalParameterValue("elements in sparseMatrix must not be zero");
        // determine whether rows and columns overflow 
        if (mTerm.row < 1 || mTerm.col < 1 || mTerm.row > x.rows || mTerm.col > x.cols)
            throw illegalParameterValue("Rows and columns must be in the legal range");
        // determine if the row and column order is correct
        if (mTerm.col * x.rows + mTerm.row <= cCol * x.rows + cRow)
            throw illegalParameterValue("the order of row and col is wrong.");
        cRow = mTerm.row; cCol = mTerm.col;

        x.terms.set(i, mTerm);
    }

    return in;
}


/****************************************************************/
// explict code tooverload with T = int for test as compiler
// unable to generate

// overload <<
std::ostream& operator<<(std::ostream& out, sparseMatrixByCols<int>& x)
{// Put x in output stream.

   // put matrix characteristics
    out << "rows = " << x.rows << " columns = "
        << x.cols << std::endl;
    out << "nonzero terms = " << x.terms.size() << std::endl;

    // put terms, one per line
    for (arrayList<matrixTerm<int> >::iterator i = x.terms.begin();
        i != x.terms.end(); i++)
        out << "a(" << (*i).row << ',' << (*i).col
        << ") = " << (*i).value << std::endl;

    return out;
}

// overload >>
std::istream& operator>>(std::istream& in, sparseMatrixByCols<int>& x)
{// Input a sparse matrix.

   // input matrix characteristics
    int numberOfTerms;
    std::cout << "Enter number of rows, columns, and #terms"
        << std::endl;
    in >> x.rows >> x.cols >> numberOfTerms;

    // check out
    if (x.rows < 0 || x.cols < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if ((x.rows == 0 || x.cols == 0)
        && (x.rows != 0 || x.cols != 0))
        throw illegalParameterValue
        ("Either both or neither rows and columns should be zero");

    // set size of x.terms and ensure enough capacity
    x.terms.reSet(numberOfTerms);

    // input terms
    matrixTerm<int> mTerm;
    int cRow = 0, cCol = 0;
    for (int i = 0; i < numberOfTerms; i++)
    {
        std::cout << "Enter row, column, and value of term "
            << (i + 1) << std::endl;
        in >> mTerm.row >> mTerm.col >> mTerm.value;

        // determine if the value is zero 
        if (mTerm.value == 0)
            throw illegalParameterValue("elements in sparseMatrix must not be zero");
        // determine whether rows and columns overflow 
        if (mTerm.row < 1 || mTerm.col < 1 || mTerm.row > x.rows || mTerm.col > x.cols)
            throw illegalParameterValue("Rows and columns must be in the legal range");
        // determine if the row and column order is correct
        if (mTerm.col * x.rows + mTerm.row <= cCol * x.rows + cRow)
            throw illegalParameterValue("the order of row and col is wrong.");
        cRow = mTerm.row; cCol = mTerm.col;

        x.terms.set(i, mTerm);
    }
    return in;
}

/****************************************************************/
template<class T>
void sparseMatrixByCols<T>::transpose(sparseMatrixByCols<T>& b)
{// Return transpose of *this in b.

   // set transpose characteristics
    b.cols = rows;
    b.rows = cols;
    b.terms.reSet(terms.size());

    // initialize to compute transpose
    int* rowSize = new int[rows + 1];
    int* colNext = new int[rows + 1];

    // find number of entries in each column of *this
    for (int i = 1; i <= rows; i++) // initialize
        rowSize[i] = 0;
    for (auto i = terms.begin();
        i != terms.end(); i++)
        rowSize[(*i).row]++;

    // find the starting point of each row of b
    colNext[1] = 0;
    for (int i = 2; i <= rows; i++)
        colNext[i] = colNext[i - 1] + rowSize[i - 1];

    // perform the transpose copying from *this to b
    matrixTerm<T> mTerm;
    for (auto i = terms.begin();
        i != terms.end(); i++)
    {
        int j = colNext[(*i).row]++; // position in b
        mTerm.row = (*i).col;
        mTerm.col = (*i).row;
        mTerm.value = (*i).value;
        b.terms.set(j, mTerm);
    }
}

template<class T>
void sparseMatrixByCols<T>::add(sparseMatrixByCols<T>& b, sparseMatrixByCols<T>& c)
{// Compute c = (*this) + b.

   // verify compatibility
    if (rows != b.rows || cols != b.cols)
        throw matrixSizeMismatch(); // incompatible matrices

      // set characteristics of result c
    c.rows = rows;
    c.cols = cols;
    c.terms.clear();
    int cSize = 0;

    // define iterators for *this and b
    auto it = terms.begin();
    auto ib = b.terms.begin();
    auto itEnd = terms.end();
    auto ibEnd = b.terms.end();

    // move through *this and b adding like terms
    while (it != itEnd && ib != ibEnd)
    {
        // row-major index plus cols of each term
        int tIndex = (*it).col * rows + (*it).row;
        int bIndex = (*ib).col * rows + (*ib).row;

        if (tIndex < bIndex)
        {// b term comes later
            c.terms.insert(cSize++, *it);
            it++;
        }
        else {
            if (tIndex == bIndex)
            {// both in same position

               // append to c only if sum not zero
                if ((*it).value + (*ib).value != 0)
                {
                    matrixTerm<T> mTerm;
                    mTerm.row = (*it).row;
                    mTerm.col = (*it).col;
                    mTerm.value = (*it).value + (*ib).value;
                    c.terms.insert(cSize++, mTerm);
                }

                it++;
                ib++;
            }
            else
            {// a term comes later
                c.terms.insert(cSize++, *ib);
                ib++;
            }
        }
    }

    // copy over remaining terms
    for (; it != itEnd; it++)
        c.terms.insert(cSize++, *it);
    for (; ib != ibEnd; ib++)
        c.terms.insert(cSize++, *ib);
}

void testEx7_44()
{
    sparseMatrixByCols<int> m1;
    std::cin >> m1;
    std::cout << std::endl << "<<m1:" << std::endl;
    std::cout << m1 << std::endl;
    sparseMatrixByCols<int> m2(m1);
    std::cout << std::endl << "<<m2:" << std::endl;
    std::cout << m2 << std::endl;

    std::cout << std::endl << "print m1:" << std::endl;
    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 1; j <= 4; ++j)
        {
            std::cout << m1.get(i, j) << " ";
            m2.set(i, j, i * 10 + j);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << "print m2:" << std::endl;
    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 1; j <= 4; ++j)
            std::cout << m2.get(i, j) << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    sparseMatrixByCols<int> m;
    std::cout << std::endl << "m1.tanspose(m):" << std::endl;
    m1.transpose(m);
    std::cout << m << std::endl;
    std::cout << std::endl << "print m:" << std::endl;
    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 1; j <= 4; ++j)
            std::cout << m.get(i, j) << " ";
        std::cout << std::endl;
    }
  
    std::cout << std::endl << "m1.add(m2,m)" << std::endl;
    m1.add(m2, m);
    std::cout << m << std::endl;
    std::cout << "print m:" << std::endl;
    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 1; j <= 4; ++j)
            std::cout << m.get(i, j) << " ";
        std::cout << std::endl;
    }
    
    m = m1 * m2;
    std::cout << std::endl << m << std::endl;
    std::cout << "print m(m1*m2):" << std::endl;
    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 1; j <= 4; ++j)
            std::cout << m.get(i, j) << " ";
        std::cout << std::endl;
    }
}

#endif