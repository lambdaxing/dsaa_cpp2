// element types used by class linkedMatrix

#ifndef matrixElements_
#define matrixElements_

#include "extendedChain.h"

template<class T>
struct rowElement
{
    int col;
    T value;

    bool operator !=(const rowElement<T>& y)
    {
        return (value != y.value);
    }
    void output(std::ostream& out) const
    {
        out << "column " << col
            << " value " << value << endl;
    }
};

template<class T>
std::ostream& operator<<(std::ostream& out, const rowElement<T>& x)
{
    x.output(out); return out;
}

template<class T>
struct headerElement
{
    int row;
    extendedChain<rowElement<T> > rowChain;

    bool operator !=(const headerElement<T>& y)
    {
        return (row != y.row);
    }
    void output(std::ostream& out) const
    {
        out << "row " << row << endl << "  " << rowChain << endl;
    }
};

template<class T>
std::ostream& operator<<(std::ostream& out,
    const headerElement<T>& x)
{
    x.output(out); return out;
}

#endif
