
#ifndef newSparseMatrix_
#define newSparseMatrix_

#include "newMatrixTerm.h"
#include "extendedArrayList.h"
#include "myExceptions.h"

template<typename T>
class newSparseMatrix
{
    friend std::ostream& operator<<(std::ostream&, newSparseMatrix<T>&);
    friend std::istream& operator>>(std::istream&, newSparseMatrix<T>&);
public:
    newSparseMatrix() = default;
    newSparseMatrix(int row, int col) :rows(row), cols(col), rowStart(new int[row + 1]) 
    {
        for (int i = 1; i <= rows; ++i)
            rowStart[i] = -1;
    }
    newSparseMatrix(const newSparseMatrix<T>&);
    ~newSparseMatrix() { delete[] rowStart; };

    newSparseMatrix<T>& operator=(const newSparseMatrix<T>& rhs);

    T get(int, int) const;
    void set(int, int, const T & newValue);
    void print() const;
    void transpose(newSparseMatrix<T> & b);
    void add(newSparseMatrix<T> & b, newSparseMatrix<T> & c);
    newSparseMatrix<T> operator*(const newSparseMatrix<T> & rhs) const;

private:
    int getLastIndexOfRow(int i) const;
	int* rowStart;
	int rows,    // number of rows in matrix
		cols;    // number of columns in matrix
	arrayList<newMatrixTerm<T> > terms;
	// list of nonzero terms
};

template<typename T>
newSparseMatrix<T>& newSparseMatrix<T>::operator=(const newSparseMatrix<T>& rhs)
{
    if (this != &rhs)
    {
        rows = rhs.rows;
        cols = rhs.cols;
        rowStart = new int[rows + 1];
        std::copy(rhs.rowStart, rhs.rowStart + rows + 1, rowStart);
        terms = rhs.terms;
    }
    return *this;
}

template<typename T>
newSparseMatrix<T> newSparseMatrix<T>::operator*(const newSparseMatrix<T>& rhs) const
{
    if (cols != rhs.rows)
        throw matrixSizeMismatch();

    newSparseMatrix<T> w(rows, rhs.cols);

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
int newSparseMatrix<T>::getLastIndexOfRow(int i) const
{
    if (i == rows)
        return terms.size();
    else
    {
        int k;
        for (k = i + 1; k < rows && rowStart[k] == -1; ++k);
        if (k == rows && rowStart[k] == -1) return terms.size();
        else return rowStart[k];
    }
}

template<typename T>
T newSparseMatrix<T>::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > rows || j > cols)
        throw matrixIndexOutOfBounds();

    int index = rowStart[i];
    if (index != -1)
    {
        int endIndex = getLastIndexOfRow(i);
        for (int k = index; k < endIndex; ++k)       // on i row
            if (terms[k].col == j)
                return terms[k].value;
    }
    // not found in the terms , it is 0
    return 0;
}

template<typename T>
void newSparseMatrix<T>::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > rows || j > cols)
        throw matrixIndexOutOfBounds();

    int index = rowStart[i];
    
    if (index == -1)
    {
        if (newValue != 0)
        {
            int insertI = getLastIndexOfRow(i);
            terms.insert(insertI, { j,newValue });
            rowStart[i] = insertI;
            for (int k = i + 1; k <= rows && rowStart[k] != -1; ++k) ++rowStart[k];
            return;
        }
    }
    else
    {
        int iRowEnd = getLastIndexOfRow(i);
        for (int k = index; k < iRowEnd; ++k)
        {
            if (j == terms[k].col)
            {
                if (newValue != 0)
                    terms[k].value = newValue;
                else
                {
                    terms.erase(k);
                    if (index == iRowEnd - 1)
                        rowStart[i] = -1;
                    else
                        ++rowStart[i];
                    for (int z = i + 1; z <= rows && rowStart[z] != -1; ++z) --rowStart[z];
                }
                return;
            }
            else if (j < terms[k].col)
            {
                terms.insert(k, { j,newValue });
                for (int z = i + 1; z <= rows && rowStart[z] != -1; ++z) ++rowStart[z];
                return;
            }
            else
                continue;
        }

        if (j > terms[iRowEnd - 1].col)
        {
            terms.insert(iRowEnd, { j,newValue });
            for (int z = i + 1; z <= rows && rowStart[z] != -1; ++z) ++rowStart[z];
            return;
        }
    }
    
}

template<typename T>
newSparseMatrix<T>::newSparseMatrix(const newSparseMatrix<T>& x)
{
    rows = x.rows;
    cols = x.cols;
    rowStart = new int[rows + 1];
    std::copy(x.rowStart, x.rowStart + rows + 1, rowStart);
    terms = x.terms;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, newSparseMatrix<T>& x)
{
    // put matrix characteristics
    out << "rows = " << x.rows << " columns = "
        << x.cols << std::endl;
    out << "nonzero terms = " << x.terms.size() << std::endl;

    // put terms, one per line
    for (int i = 1; i <= x.rows; ++i)
    {
        if (x.rowStart[i] != -1)
        {
            int iRowEnd = x.getLastIndexOfRow(i);
            for (int j = x.rowStart[i]; j < iRowEnd; ++j)
                out << "a(" << i << ',' << x.terms[j].col
                << ") = " << x.terms[j].value << std::endl;
        }
    }
    return out;
}

// overload >>
template<class T>
std::istream& operator>>(std::istream& in, newSparseMatrix<T>& x)
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
    delete[] x.rowStart;
    x.rowStart = new int[x.rows + 1];
    for (int i = 1; i <= x.rows; ++i)
        x.rowStart[i] = -1;

    // input terms
    newMatrixTerm<T> mTerm;
    int row;
    int cRow = 0, cCol = 0;
    for (int i = 0; i < numberOfTerms; i++)
    {
        std::cout << "Enter row, column, and value of term "
            << (i + 1) << std::endl;
        in >> row >> mTerm.col >> mTerm.value;

        // determine if the value is zero 
        if (mTerm.value == 0)
            throw illegalParameterValue("elements in sparseMatrix must not be zero");
        // determine whether rows and columns overflow 
        if (row < 1 || mTerm.col < 1 || row > x.rows || mTerm.col > x.cols)
            throw illegalParameterValue("Rows and columns must be in the legal range");
        // determine if the row and column order is correct
        if (row * x.cols + mTerm.col <= cRow * x.cols + cCol)
            throw illegalParameterValue("the order of row and col is wrong.");
        cRow = row; cCol = mTerm.col;

        if (x.rowStart[row] == -1)
            x.rowStart[row] = i;
        x.terms.set(i, mTerm);
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, newSparseMatrix<int>& x)
{
    // put matrix characteristics
    out << "rows = " << x.rows << " columns = "
        << x.cols << std::endl;
    out << "nonzero terms = " << x.terms.size() << std::endl;

    // put terms, one per line
    for (int i = 1; i <= x.rows; ++i)
    {
        if (x.rowStart[i] != -1)
        {
            int iRowEnd = x.getLastIndexOfRow(i);
            for (int j = x.rowStart[i]; j < iRowEnd; ++j)
                out << "a(" << i << ',' << x.terms[j].col
                << ") = " << x.terms[j].value << std::endl;
        }
    }
    return out;
}

std::istream& operator>>(std::istream& in, newSparseMatrix<int>& x)
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
    delete[] x.rowStart;
    x.rowStart = new int[x.rows + 1];
    for (int i = 1; i <= x.rows; ++i)
        x.rowStart[i] = -1;

    // input terms
    newMatrixTerm<int> mTerm;
    int row;
    int cRow = 0, cCol = 0;
    for (int i = 0; i < numberOfTerms; i++)
    {
        std::cout << "Enter row, column, and value of term "
            << (i + 1) << std::endl;
        in >> row >> mTerm.col >> mTerm.value;

        // determine if the value is zero 
        if (mTerm.value == 0)
            throw illegalParameterValue("elements in sparseMatrix must not be zero");
        // determine whether rows and columns overflow 
        if (row < 1 || mTerm.col < 1 || row > x.rows || mTerm.col > x.cols)
            throw illegalParameterValue("Rows and columns must be in the legal range");
        // determine if the row and column order is correct
        if (row * x.cols + mTerm.col <= cRow * x.cols + cCol)
            throw illegalParameterValue("the order of row and col is wrong.");
        cRow = row; cCol = mTerm.col;

        if (x.rowStart[row] == -1)
            x.rowStart[row] = i;
        x.terms.set(i, mTerm);
    }

    return in;
}

template <typename T>
void newSparseMatrix<T>::transpose(newSparseMatrix<T>& b)
{
    b.rows = cols;
    b.cols = rows;
    delete[] b.rowStart;
    b.rowStart = new int[cols + 1];
    for (int i = 1; i <= cols; ++i) b.rowStart[i] = -1;
    b.terms.reSet(terms.size());

    // initialize to compute transpose
    int* colSize = new int[cols + 1];
    int* rowNext = new int[cols + 1];

    // find number of entries in each column of *this
    for (int i = 1; i <= cols; i++) // initialize
        colSize[i] = 0;
    for (auto i = terms.begin();
        i != terms.end(); i++)
        colSize[(*i).col]++;

    // find the starting point of each row of b
    rowNext[1] = 0;
    for (int i = 2; i <= cols; i++)
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];

    newMatrixTerm<T> m;
    for (int i = 1; i <= rows; ++i)
    {
        if (rowStart[i] != -1)
        {
            int iRowEnd = getLastIndexOfRow(i);
            for (int index = rowStart[i]; index < iRowEnd; ++index)
            {
                int row = terms[index].col;
                int j = rowNext[row]++; // position in b
                if (b.rowStart[row] == -1 || b.rowStart[row] > j)
                    b.rowStart[row] = j;
                m.col = i;
                m.value = terms[index].value;
                b.terms.set(j, m);
            }
        }
    }
}

template<typename T>
void newSparseMatrix<T>::add(newSparseMatrix<T>& b, newSparseMatrix<T>& c)
{
    // verify compatibility
    if (rows != b.rows || cols != b.cols)
        throw matrixSizeMismatch(); // incompatible matrices

    // set characteristics of result c
    c.rows = rows;
    c.cols = cols;
    c.terms.clear();
    delete[] c.rowStart;
    c.rowStart = new int[rows + 1];
    for (int k = 0; k <= rows; ++k) c.rowStart[k] = -1;

    int cSize = 0;

    for (int i = 1; i <= rows; ++i)
    {
        int tIndex = rowStart[i], bIndex = b.rowStart[i];
        int tEnd = getLastIndexOfRow(i), bEnd = b.getLastIndexOfRow(i);

        if (tIndex != -1 || bIndex != -1)
            c.rowStart[i] = cSize;
        else
            continue;

        if (tIndex == -1 && bIndex != -1) // i row in b
        {
            for (int index = bIndex; index < bEnd; ++index)
                c.terms.insert(cSize++, { b.terms[index].col,b.terms[index].value });
        }
        else if (tIndex != -1 && bIndex == -1) // i row in this
        {
            for (int index = tIndex; index < tEnd; ++index)
                c.terms.insert(cSize++, { terms[index].col,terms[index].value });
        }
        else if (tIndex != -1 && bIndex != -1) // i row in b and this
        {
            int ti, bi;
            for (ti = tIndex, bi = bIndex; ti < tEnd && bi < bEnd;)
            {
                if (terms[ti].col < b.terms[bi].col)
                {
                    c.terms.insert(cSize++, { terms[ti].col,terms[ti].value });
                    ++ti;
                }
                else if (terms[ti].col == b.terms[bi].col)
                {
                    c.terms.insert(cSize++, { terms[ti].col,b.terms[bi].value + terms[ti].value });
                    ++bi; ++ti;
                }
                else
                {
                    c.terms.insert(cSize++, { b.terms[bi].col,b.terms[bi].value });
                    ++bi;
                }
            }
            while (ti < tEnd)
            {
                c.terms.insert(cSize++, { terms[ti].col,terms[ti].value });
                ++ti;
            }
            while (bi < bEnd)
            {
                c.terms.insert(cSize++, { b.terms[bi].col,b.terms[bi].value });
                ++bi;
            }
        }
    }
}

template<typename T>
void newSparseMatrix<T>::print() const
{
    for (int i = 1; i <= rows; ++i)
    {
        for (int j = 1; j <= cols; ++j)
            std::cout << get(i, j) << " ";
        std::cout << std::endl;
    }
}

void testEx7_47()
{
    newSparseMatrix<int> m1;
    std::cin >> m1;
    std::cout << m1 << std::endl;
    newSparseMatrix<int> m2(m1);
    std::cout << "print m1:" << std::endl;
    std::cout << m1 << std::endl;
    for (int i = 1; i <= 4; ++i)
    {
        for (int j = 1; j <= 4; ++j)
        {
            std::cout << m1.get(i, j) << " ";
            m2.set(i, j, i * 10 + j);
        }
        std::cout << std::endl;
    }
    std::cout << "print m2:" << std::endl;
    std::cout << m2 << std::endl;
    m2.print();
    std::cout << std::endl;
    newSparseMatrix<int> m;
    m1.transpose(m);
    std::cout << m << std::endl;
    std::cout << "print m:" << std::endl;
    m.print();
    m1.add(m2, m);
    std::cout << m << std::endl;
    std::cout << "print m = m1 + m2:" << std::endl;
    m.print();
    m = m1 * m2;
    std::cout << m << std::endl;
    std::cout << "print m = m1 * m2:" << std::endl;
    m.print();
}

#endif