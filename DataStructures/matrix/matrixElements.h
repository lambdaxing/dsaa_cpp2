// element types used by class linkedMatrix

#ifndef matrixElements_
#define matrixElements_

#include "extendedChain.h"

template<class T>
struct rowElement
{
    int col;
    T value;

    rowElement() = default;
    rowElement(const rowElement&) = default;
    rowElement& operator=(const rowElement&) = default;

    bool operator !=(const rowElement<T>& y)
    {
        return (value != y.value);
    }
    void output(std::ostream& out) const
    {
        out << "column " << col
            << " value " << value << std::endl;
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

    headerElement() = default;
    headerElement(int r) :row(r) {}
    headerElement(const headerElement&) = default;
    headerElement& operator=(const headerElement&) = default;

    bool operator !=(const headerElement<T>& y)
    {
        return (row != y.row);
    }
    void output(std::ostream& out) const
    {
        out << "row " << row << std::endl << "  " << rowChain << std::endl;
    }
};

template<class T>
std::ostream& operator<<(std::ostream& out,
    const headerElement<T>& x)
{
    x.output(out); return out;
}

#endif
