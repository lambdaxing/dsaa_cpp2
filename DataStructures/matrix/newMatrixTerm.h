// a term in sparseMatrix

#ifndef newMatrixTerm_
#define newMatrixTerm_

template <class T>
struct newMatrixTerm
{
    int col;
    T value;

    operator T() const { return value; }
    // type conversion from matrixTerm to T
};

#endif
