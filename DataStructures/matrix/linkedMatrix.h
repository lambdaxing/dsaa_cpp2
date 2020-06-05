// linked representation of a sparse matrix

#ifndef linkedMatrix_
#define linkedMatrix_

#include <iostream>
#include "extendedChain.h"
#include "matrixElements.h"

template<class T>
class linkedMatrix
{
    friend std::ostream& operator<<(std::ostream&, linkedMatrix<T>&);
    friend std::istream& operator>>(std::istream&, linkedMatrix<T>&);
    friend linkedMatrix<T> operator+(const linkedMatrix<T>& lhs, const linkedMatrix<T>& rhs);
    friend linkedMatrix<T> operator-(const linkedMatrix<T>& lhs, const linkedMatrix<T>& rhs);
    friend linkedMatrix<T> operator*(const linkedMatrix<T>& lhs, const linkedMatrix<T>& rhs);
public:
    linkedMatrix() {}
    linkedMatrix(int row, int col) :rows(row), cols(col) {}
    ~linkedMatrix() {}
    linkedMatrix(const linkedMatrix& x) :rows(x.rows), cols(x.cols), headerChain(x.headerChain) {}
    linkedMatrix& operator=(const linkedMatrix& rhs)
    {
        if (this != &rhs)
        {
            rows = rhs.rows;
            cols = rhs.cols;
            headerChain = rhs.headerChain;
        }
        return *this;
    }

    void transpose(linkedMatrix<T>& b);
    T get(int, int) const;
    void set(int, int, const T& newValue);
    void print() const;

private:
    int rows,       // number of rows in matrix
        cols;       // number of columns in matrix
    extendedChain<headerElement<T> > headerChain;
};

template<typename T>
linkedMatrix<T> operator*(const linkedMatrix<T>& lhs, const linkedMatrix<T>& rhs)
{
    if (lhs.cols != rhs.rows)
        throw matrixSizeMismatch();

    linkedMatrix<T> w(lhs.rows, rhs.cols);

    for (int i = 1; i <= lhs.rows; ++i)
        for (int j = 1; j <= rhs.cols; ++j)
        {
            T sum = lhs.get(i, 1) * rhs.get(1, j);
            for (int k = 2; k <= lhs.cols; ++k)
                sum += lhs.get(i, k) * rhs.get(k, j);
            w.set(i, j, sum);
        }
    return w;
}

template<typename T>
linkedMatrix<T> operator-(const linkedMatrix<T>& lhs, const linkedMatrix<T>& rhs)
{
    // verify compatibility
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
        throw matrixSizeMismatch(); // incompatible matrices

      // set characteristics of result c
    linkedMatrix<T> c;
    c.rows = lhs.rows;
    c.cols = lhs.cols;

    // define iterators for lhs and rhs
    auto il = lhs.headerChain.cbegin();
    auto ir = rhs.headerChain.cbegin();
    auto ilEnd = lhs.headerChain.cend();
    auto irEnd = rhs.headerChain.cend();

    while (il != ilEnd && ir != irEnd)
    {
        headerElement<T> header;
        if (il->row < ir->row)
            header = *il++;
        else if (il->row > ir->row)
        {
            header = *ir++;
            for (auto& x : header.rowChain)
                x.value = -x.value;
        }
        else
        {
            header.row = il->row;
            // define iterators for i row of lhs and rhs
            auto jl = il->rowChain.cbegin(), jr = ir->rowChain.cbegin();
            auto jlEnd = il->rowChain.cend(), jrEnd = ir->rowChain.cend();
            while (jl != jlEnd && jr != jrEnd)
            {
                if (jl->col < jr->col)
                    header.rowChain.push_back(*jl++);
                else if (jl->col > jr->col)
                {
                    header.rowChain.push_back({ jr->col,-jr->value });
                    ++jr;
                }
                else
                {
                    header.rowChain.push_back({ jl->col,jl->value - jr->value });
                    ++jl, ++jr;
                }
            }
            // copy over remaining terms in i row
            for (; jl != jlEnd; ++jl)
                header.rowChain.push_back(*jl);
            for (; jr != jrEnd; ++jr)
                header.rowChain.push_back({ jr->col,-jr->value });
            ++il, ++ir;
        }
        c.headerChain.push_back(header);
    }
    // copy over remaining terms in headerChain
    for (; il != ilEnd; il++)
        c.headerChain.push_back(*il);
    for (; ir != irEnd; ir++)
    {
        auto x = *ir;
        for (auto& y : x.rowChain)
            y.value = -y.value;
        c.headerChain.push_back(x);
    }

    return c;
}

template<typename T>
linkedMatrix<T> operator+(const linkedMatrix<T>& lhs, const linkedMatrix<T>& rhs)
{
    // verify compatibility
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
        throw matrixSizeMismatch(); // incompatible matrices

    // set characteristics of result c
    linkedMatrix<T> c;
    c.rows = lhs.rows;
    c.cols = lhs.cols;

    // define iterators for lhs and rhs
    auto il = lhs.headerChain.cbegin();
    auto ir = rhs.headerChain.cbegin();
    auto ilEnd = lhs.headerChain.cend();
    auto irEnd = rhs.headerChain.cend();

    while (il != ilEnd && ir != irEnd)
    {
        headerElement<T> header;
        if (il->row < ir->row)
            header = *il++;
        else if (il->row > ir->row)
            header = *ir++;
        else
        {
            header.row = il->row;
            auto jl = il->rowChain.cbegin(), jr = ir->rowChain.cbegin();
            auto jlEnd = il->rowChain.cend(), jrEnd = ir->rowChain.cend();
            while (jl != jlEnd && jr != jrEnd)
            {
                if (jl->col < jr->col)
                    header.rowChain.push_back(*jl++);
                else if (jl->col > jr->col)
                    header.rowChain.push_back(*jr++);
                else
                {
                    header.rowChain.push_back({ jl->col,jl->value + jr->value });
                    ++jl, ++jr;
                }
            }
            // copy over remaining terms in i row
            for (; jl != jlEnd; ++jl)
                header.rowChain.push_back(*jl);
            for (; jr != jrEnd; ++jr)
                header.rowChain.push_back(*jr);
            ++il, ++ir;
        }
        c.headerChain.push_back(header); 
    }

    // copy over remaining terms in headerChain
    for (; il != ilEnd; il++)
        c.headerChain.push_back(*il);
    for (; ir != irEnd; ir++)
        c.headerChain.push_back(*ir);

    return c;
}

linkedMatrix<int> operator+(const linkedMatrix<int>& lhs, const linkedMatrix<int>& rhs)
{
    // verify compatibility
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
        throw matrixSizeMismatch(); // incompatible matrices

    linkedMatrix<int> c;
    c.rows = lhs.rows;
    c.cols = lhs.cols;

    // define iterators for lhs and rhs
    auto il = lhs.headerChain.cbegin();
    auto ir = rhs.headerChain.cbegin();
    auto ilEnd = lhs.headerChain.cend();
    auto irEnd = rhs.headerChain.cend();

    while (il != ilEnd && ir != irEnd)
    {
        headerElement<int> header;
        if (il->row < ir->row)
            header = *il++;
        else if (il->row > ir->row)
            header = *ir++;
        else
        {
            header.row = il->row;
            auto jl = il->rowChain.cbegin(), jr = ir->rowChain.cbegin();
            auto jlEnd = il->rowChain.cend(), jrEnd = ir->rowChain.cend();
            while (jl != jlEnd && jr != jrEnd)
            {
                if (jl->col < jr->col)
                    header.rowChain.push_back(*jl++);
                else if (jl->col > jr->col)
                    header.rowChain.push_back(*jr++);
                else
                {
                    header.rowChain.push_back({ jl->col,jl->value + jr->value });
                    ++jl, ++jr;
                }
            }
            for (; jl != jlEnd; ++jl)
                header.rowChain.push_back(*jl);
            for (; jr != jrEnd; ++jr)
                header.rowChain.push_back(*jr);
            ++il, ++ir;
        }
        c.headerChain.push_back(header);
    }

    // copy over remaining terms
    for (; il != ilEnd; il++)
        c.headerChain.push_back(*il);
    for (; ir != irEnd; ir++)
        c.headerChain.push_back(*ir);

    return c;
}

linkedMatrix<int> operator-(const linkedMatrix<int>& lhs, const linkedMatrix<int>& rhs)
{
    // verify compatibility
    if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
        throw matrixSizeMismatch(); // incompatible matrices

    // set characteristics of result c
    linkedMatrix<int> c;
    c.rows = lhs.rows;
    c.cols = lhs.cols;

    // define iterators for lhs and rhs
    auto il = lhs.headerChain.cbegin();
    auto ir = rhs.headerChain.cbegin();
    auto ilEnd = lhs.headerChain.cend();
    auto irEnd = rhs.headerChain.cend();

    while (il != ilEnd && ir != irEnd)
    {
        headerElement<int> header;
        if (il->row < ir->row)
            header = *il++;
        else if (il->row > ir->row)
        {
            header = *ir++;
            for (auto& x : header.rowChain)
                x.value = -x.value;
        }
        else
        {
            header.row = il->row;
            auto jl = il->rowChain.cbegin(), jr = ir->rowChain.cbegin();
            auto jlEnd = il->rowChain.cend(), jrEnd = ir->rowChain.cend();
            while (jl != jlEnd && jr != jrEnd)
            {
                if (jl->col < jr->col)
                    header.rowChain.push_back(*jl++);
                else if (jl->col > jr->col)
                {
                    header.rowChain.push_back({ jr->col,-jr->value });
                    ++jr;
                }
                else
                {
                    header.rowChain.push_back({ jl->col,jl->value - jr->value });
                    ++jl, ++jr;
                }
            }
            for (; jl != jlEnd; ++jl)
                header.rowChain.push_back(*jl);
            for (; jr != jrEnd; ++jr)
                header.rowChain.push_back({ jr->col,-jr->value });
            ++il, ++ir;
        }
        c.headerChain.push_back(header);

    }
    // copy over remaining terms
    for (; il != ilEnd; il++)
        c.headerChain.push_back(*il);
    for (; ir != irEnd; ir++)
    {
        auto x = *ir;
        for (auto& y : x.rowChain)
            y.value = -y.value;
        c.headerChain.push_back(x);
    }

    return c;
}

linkedMatrix<int> operator*(const linkedMatrix<int>& lhs, const linkedMatrix<int>& rhs)
{
    if (lhs.cols != rhs.rows)
        throw matrixSizeMismatch();

    linkedMatrix<int> w(lhs.rows, rhs.cols);

    for (int i = 1; i <= lhs.rows; ++i)
        for (int j = 1; j <= rhs.cols; ++j)
        {
            int sum = lhs.get(i, 1) * rhs.get(1, j);
            for (int k = 2; k <= lhs.cols; ++k)
                sum += lhs.get(i, k) * rhs.get(k, j);
            w.set(i, j, sum);
        }
    return w;
}

template<typename T>
void linkedMatrix<T>::print() const
{
    for (int i = 1; i <= rows; ++i)
    {
        for (int j = 1; j <= cols; ++j)
            std::cout << get(i, j) << " ";
        std::cout << std::endl;
    }
}

template<typename T>
T linkedMatrix<T>::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > rows || j > cols)
        throw matrixIndexOutOfBounds();

    // find i row 
    auto b = headerChain.cbegin();
    while (b != headerChain.cend() && b->row < i)
        ++b;

    // not found
    if (b == headerChain.cend())
        return 0;
    if (b->row != i)
        return 0;

    auto iRowBegin = b->rowChain.begin(), iRowEnd = b->rowChain.end();
    while (iRowBegin != iRowEnd)
    {
        if (iRowBegin->col == j)
            return iRowBegin->value;
        if (iRowBegin->col > j)
            return 0;
        ++iRowBegin;
    }
    return 0;
}

template<typename T>
void linkedMatrix<T>::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > rows || j > cols)
        throw matrixIndexOutOfBounds();

    int iInsert = 0, jInsert = 0;
    // find i row 
    auto b = headerChain.begin();
    while (b != headerChain.end() && b->row < i)
        ++b, ++iInsert;

    if (b == headerChain.end()) // not found i row
    {
        if (newValue != 0)
        {
            headerElement<T> m;
            m.row = i;
            m.rowChain.push_back({ j,newValue });
            headerChain.push_back(m);
        }
    }
    else                      
    {
        if (b->row == i)       // found i row
        {
            auto jb = b->rowChain.begin();  // find j col
            while (jb != b->rowChain.end() && jb->col < j)
                ++jb, ++jInsert;
            if (jb == b->rowChain.end())    // not found j col
            {
                if (newValue != 0)
                    b->rowChain.push_back({ j,newValue }); 
            }
            else                            
            {
                if (jb->col == j)           // found j col
                {
                    if (newValue != 0)
                        jb->value = newValue;
                    else
                        b->rowChain.erase(jInsert);
                }
                else                        // not found j col ,but found the index of inserting j
                {
                    if(newValue != 0)
                        b->rowChain.insert(jInsert, { j,newValue });
                }
            }
        }
        else if (b->row > i)    // not found i row, but found the index of inserting i row
        {
            if (newValue != 0)
            {
                headerElement<T> m;
                m.row = i;
                m.rowChain.push_back({ j,newValue });
                headerChain.insert(iInsert, m);
            }
        }
    }
}

template<class T>
std::istream& operator>>(std::istream& in, linkedMatrix<T>& x)
{// Input matrix x from the stream in.
    x.headerChain.clear();
    // delete all nodes from x

    // get matrix characteristics
    int terms;   // number of terms to be input
    std::cout << "Enter number of rows, columns, and terms"
        << std::endl;
    in >> x.rows >> x.cols >> terms;

    // check out
    if (x.rows < 0 || x.cols < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if ((x.rows == 0 || x.cols == 0)
        && (x.rows != 0 || x.cols != 0))
        throw illegalParameterValue
        ("Either both or neither rows and columns should be zero");

    // create fictional row zero
    headerElement<T> header;  // header for current row
    header.row = 0;           // current row number

    int cRow = 0, cCol = 0;
    // get terms of matrix x
    for (int i = 1; i <= terms; i++)
    {
        // input next term
        std::cout << "Enter row, column, and value of term "
            << i << std::endl;
        rowElement<T>* term = new rowElement<T>;
        int row;
        in >> row >> term->col >> term->value;

        // determine if the value is zero 
        if (term->value == 0)
            throw illegalParameterValue("elements in linkedMatrix must not be zero");
        // determine whether rows and columns overflow 
        if (row < 1 || term->col < 1 || row > x.rows || term->col > x.cols)
            throw illegalParameterValue("Rows and columns must be in the legal range");
        // determine if the row and column order is correct
        if (row * x.cols + term->col <= cRow * x.cols + cCol)
            throw illegalParameterValue("the order of row and col is wrong.");
        cRow = row; cCol = term->col;

        // check if new term is part of current row
        if (row > header.row)
        {// start a new row
           // append header of current row to
           // header node chain only if row not zero
            if (header.row != 0)
                x.headerChain.push_back(header);

            // prepare header for new row
            header.row = row;
            header.rowChain.zero();
            // clear without deleting nodes
        }

        // add new term to row chain
        header.rowChain.push_back(*term);
    }

    // take care of last row of matrix
    if (header.row != 0)
        x.headerChain.push_back(header);
    header.rowChain.zero(); // save from chain destructor

    return in;
}

template<class T>
std::ostream& operator<<(std::ostream& out, linkedMatrix<T>& x)
{// Put matrix x into the output stream out.
   // output matrix dimensions
    out << "rows = " << x.rows << " columns = "
        << x.cols << std::endl << "  ";

    if (x.headerChain.empty())
    {
        out << "No non-zero terms" << std::endl;
        return out;
    }

    out << x.headerChain << std::endl;
    return out;
}

/****************************************************************/
// explict code to overload with T = int for test as compiler
// unable to generate

std::istream& operator>>(std::istream& in, linkedMatrix<int>& x)
{// Input matrix x from the stream in.
    x.headerChain.clear();
    // delete all nodes from x

    // get matrix characteristics
    int terms;   // number of terms to be input
    std::cout << "Enter number of rows, columns, and terms"
        << std::endl;
    in >> x.rows >> x.cols >> terms;

    // check out
    if (x.rows < 0 || x.cols < 0)
        throw illegalParameterValue("Rows and columns must be >= 0");
    if ((x.rows == 0 || x.cols == 0)
        && (x.rows != 0 || x.cols != 0))
        throw illegalParameterValue
        ("Either both or neither rows and columns should be zero");

    // create fictional row zero
    headerElement<int> header;  // header for current row
    header.row = 0;           // current row number

    int cRow = 0, cCol = 0;
    // get terms of matrix x
    for (int i = 1; i <= terms; i++)
    {
        // input next term
        std::cout << "Enter row, column, and value of term "
            << i << std::endl;
        rowElement<int>* term = new rowElement<int>;
        int row;
        in >> row >> term->col >> term->value;

        // determine if the value is zero 
        if (term->value == 0)
            throw illegalParameterValue("elements in linkedMatrix must not be zero");
        // determine whether rows and columns overflow 
        if (row < 1 || term->col < 1 || row > x.rows || term->col > x.cols)
            throw illegalParameterValue("Rows and columns must be in the legal range");
        // determine if the row and column order is correct
        if (row * x.cols + term->col <= cRow * x.cols + cCol)
            throw illegalParameterValue("the order of row and col is wrong.");
        cRow = row; cCol = term->col;

        // check if new term is part of current row
        if (row > header.row)
        {// start a new row
           // append header of current row to
           // header node chain only if row not zero
            if (header.row != 0)
                x.headerChain.push_back(header);

            // prepare header for new row
            header.row = row;
            header.rowChain.zero();
            // clear without deleting nodes
        }

        // add new term to row chain
        header.rowChain.push_back(*term);
    }

    // take care of last row of matrix
    if (header.row != 0)
        x.headerChain.push_back(header);
    header.rowChain.zero(); // save from chain destructor

    return in;
}

std::ostream& operator<<(std::ostream& out, linkedMatrix<int>& x)
{// Put matrix x into the output stream out.
   // output matrix dimensions
    out << "rows = " << x.rows << " columns = "
        << x.cols << std::endl << "  ";

    if (x.headerChain.empty())
    {
        out << "No non-zero terms" << std::endl;
        return out;
    }

    out << x.headerChain << std::endl;

    return out;
}
/****************************************************************/

template<class T>
void linkedMatrix<T>::transpose(linkedMatrix<T>& b)
{// Return transpose of *this as matrix b.
    b.headerChain.clear(); // delete all nodes from b

    // create bins to collect rows of b
    extendedChain<rowElement<T> >* bin;
    bin = new extendedChain<rowElement<T> >[cols + 1];

    // head node iterator
   auto ih = headerChain.begin(),ihEnd = headerChain.end();

    // copy terms of *this into bins
    while (ih != ihEnd)
    {// examine all rows
        int r = ih->row; // row number for row chain

        // row chain iterator
        auto ir = ih->rowChain.begin(), irEnd = ih->rowChain.end();

        rowElement<T> x;
        // terms from row r of *this go to column r of b
        x.col = r;

        while (ir != irEnd)
        {// copy a term from the row chain into a bin
            x.value = ir->value;
            // x will eventually be in row ir->col of transpose
            bin[ir->col].push_back(x);
            ir++;  // next term in row
        }

        ih++; // go to next row
    }

    // set dimensions of transpose
    b.rows = cols;
    b.cols = rows;

    // assemble header chain of transpose
    headerElement<T> h;
    // scan bins
    for (int i = 1; i <= cols; i++)
        if (!bin[i].empty())
        {// row i of transpose
            h.row = i;
            h.rowChain = bin[i];
            b.headerChain.push_back(h);
            bin[i].zero(); // save from destructor
        }

    h.rowChain.zero();   // save from destructor
    delete[] bin;
}

#endif
