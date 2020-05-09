
#ifndef arrayList_
#define arrayList_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

template<class T>
class circularArrayList : public linearList<T>
{
public:
    // constructor, copy constructor and destructor
    circularArrayList(int initialCapacity = 10);
    circularArrayList(const circularArrayList<T>&);
    ~circularArrayList() { delete[] element; }

    // ADT methods
    bool empty() const { return first == -1; }
    int size() const
    {
        if (first == -1)
            return 0;
        else
            return (arrayLength + last - first) % arrayLength + 1;
    }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;

    T& operator[](int theIndex) const;
    // additional method
    int capacity() const { return arrayLength; }
    void reserve(int theCapacity);
    void clear();

    // ex5_33
    void reverse();
    // ex5_34
    void meld(const circularArrayList& a, const circularArrayList& b);
    // ex5_35
    void merge(const circularArrayList& a, const circularArrayList& b);
    // ex5_36
    void split(circularArrayList& a,circularArrayList& b);

    // iterators to start and end of list
    class iterator;
    iterator begin() { return iterator(*this, 0); }
    iterator end() { return iterator(*this, size()); }
    const iterator cbegin() const { return iterator(*this, 0); }
    const iterator cend()  const { return iterator(*this, size()); }

    // iterator for arrayList
    class iterator
    {
    public:
        // typedefs required by C++ for a bidirectional iterator
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        // constructor
        iterator(const circularArrayList& theList, int i) :currentList(theList) 
        { 
            position = &theList.element[(theList.first + i) % theList.arrayLength];
            index = i;
        }

        // dereferencing operators
        T& operator*() const { return *position; }
        T* operator->() const { return &*position; }

        // increment
        iterator& operator++()   // preincrement
        {
            ++index;
            position = currentList.element + (currentList.first + index) % currentList.arrayLength;
            return *this;
        }
        iterator operator++(int) // postincrement
        {
            iterator old = *this;
            operator++();
            return old;
        }

        // decrement
        iterator& operator--()   // predecrement
        {
            --index;
            position = currentList.element + (currentList.first + index) % currentList.arrayLength;
            return *this;
        }
        iterator operator--(int) // postdecrement
        {
            iterator old = *this;
            operator--();
            return old;
        }

        // equality testing
        bool operator!=(const iterator right) const
        {
            return position != right.position;
        }
        bool operator==(const iterator right) const
        {
            return position == right.position;
        }
    protected:
        T* position;
        const circularArrayList& currentList;
        int index;
    };  // end of iterator class
protected:
    void checkIndex(int theIndex) const;
    // throw illegalIndex if theIndex invalid
    T* element;            // 1D array to hold list elements
    int arrayLength;       // capacity of the 1D array
    int first;             // location of first element
    int last;              // location of last element
};

template<class T>
circularArrayList<T>::circularArrayList(int initialCapacity)
{// Constructor.
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    first = -1;   // list is empty
}

template<class T>
circularArrayList<T>::circularArrayList(const circularArrayList<T>& theList)
{// Copy constructor.
    arrayLength = theList.arrayLength;
    element = new T[arrayLength];
    first = theList.first;
    if (first == -1)
        return;   // theList is empty

     // non-empty list
    last = theList.last;
    int current = first;
    while (current != last)
    {
        element[current] = theList.element[current];
        current = (current + 1) % arrayLength;
    }
    element[current] = theList.element[current];
}

template<class T>
void circularArrayList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and size() - 1.
    int listSize = size();
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
T& circularArrayList<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);
    return element[(first + theIndex) % arrayLength];
}

template<class T>
int circularArrayList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

    int listSize = size();
    for (int i = 0; i < listSize; i++)
        if (element[(first + i) % arrayLength] == theElement)
            return i;

    return -1;
}

template<class T>
void circularArrayList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
    checkIndex(theIndex);

    // no exception thrown, valid index, remove element
    if (size() == 1)
    {// list becomes empty
        element[first].~T();   // delete element
        first = -1;
        return;
    }

    // determine which side has fewer elements
    // and shift the smaller number of elements
    int listSize = size();
    if (theIndex <= (listSize - 1) / 2)
    {// shift elements theIndex - 1 ... 0
        for (int i = theIndex - 1; i >= 0; i--)
            element[(first + i + 1) % arrayLength]
            = element[(first + i) % arrayLength];
        element[first].~T();    // delete
        first = (first + 1) % arrayLength;
    }
    else
    {// shift elements theIndex + 1 ... size() - 1
        for (int i = theIndex + 1; i < listSize; i++)
            element[(first + i - 1) % arrayLength]
            = element[(first + i) % arrayLength];
        element[last].~T();   // delete
        last = (arrayLength + last - 1) % arrayLength;
    }
}

template<class T>
void circularArrayList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
    int listSize = size();
    if (theIndex < 0 || theIndex > listSize)
    {// invalid index
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    // valid index, handle empty list as special case
    if (first == -1)
    {// insert into empty list
        first = last = 0;
        element[0] = theElement;
        return;
    }

    // insert into a nonempty list, make sure we have space
    if (listSize == arrayLength)
    {// no space, double capacity
        T* newArray = new T[2 * arrayLength];

        // copy elements into new array beginning at position  0
        int j = 0;   // position in newArray to copy to
        for (int i = first;
            i != last; i = (i + 1) % arrayLength)
            newArray[j++] = element[i];
        newArray[j] = element[last];  // copy last element

        // switch to newArray and set first and last
        delete[] element;
        element = newArray;
        arrayLength *= 2;
        first = 0;
        last = j;
    }

    // create space for new element
    if (theIndex <= listSize / 2)
    {// shift elements 0 through theIndex - 1
        for (int i = 0; i < theIndex; i++)
            element[(arrayLength + first + i - 1) % arrayLength]
            = element[(first + i) % arrayLength];
        first = (arrayLength + first - 1) % arrayLength;
    }
    else
    {// shift elements listSize - 1  ... theIndex
        for (int i = listSize - 1; i >= theIndex; i--)
            element[(first + i + 1) % arrayLength]
            = element[(first + i) % arrayLength];
        last = (last + 1) % arrayLength;
    }

    // insert new element
    element[(first + theIndex) % arrayLength] = theElement;
}

template<class T>
void circularArrayList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
    if (first == -1)
        return;   // list is empty

     // non-empty list
    int current = first;
    while (current != last)
    {
        out << element[current] << "  ";
        current = (current + 1) % arrayLength;
    }
    out << element[current] << "  ";
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const circularArrayList<T>& x)
{
    x.output(out); return out;
}

template<typename T>
T& circularArrayList<T>::operator[] (int theIndex) const
{
    checkIndex(theIndex);
    return element[(first + theIndex) % arrayLength];
}

template<typename T>
void circularArrayList<T>::clear()
{
    delete[] element;
    element = new T[arrayLength];
    first = -1;
}

template<typename T>
void circularArrayList<T>::reserve(int theCapacity)
{
    if (theCapacity <= arrayLength)
        return;
    changeLength1D(element, arrayLength, theCapacity + 1);   // +1 for the end itear
    arrayLength = theCapacity + 1;
}

template<typename T>
void circularArrayList<T>::reverse()
{
    for (int i = 0; i < size() / 2; ++i)
        std::swap(element[(first + i) % arrayLength], element[(first + size() - i - 1) % arrayLength]);
}

template<typename T>
void reverse(circularArrayList<T>& x)
{
    using std::swap;
    for (int i = 0; i < x.size() / 2; ++i)
        swap(x[i], x[x.size() - i - 1]);
}

template<typename T>
void circularArrayList<T>::meld(const circularArrayList& a, const circularArrayList& b)
{
    int size = a.size() + b.size();
    reserve(size);
    auto abegin = a.cbegin(), bbegin = b.cbegin();
    for (int i = 0; i < size; ++i) {
        if (i % 2 && abegin != a.cend() || bbegin == b.cend())
            element[i] = *abegin++;
        else
            element[i] = *bbegin++;
    }
    first = (size == 0 ? -1 : 0);
    last = size - 1;
}

template<typename T>
void circularArrayList<T>::merge(const circularArrayList& a, const circularArrayList& b)
{
    int size = a.size() + b.size();
    reserve(size);
    auto abegin = a.cbegin(), bbegin = b.cbegin();
    for (int i = 0; i < size; ++i) {
        if (abegin != a.cend() && bbegin != b.cend() && *abegin < *bbegin ||
            abegin != a.cend() && bbegin == b.cend())
            element[i] = *abegin++;
        else
            element[i] = *bbegin++;
    }
    first = (size == 0 ? -1 : 0);
    last = size - 1;
}

template<typename T>
void circularArrayList<T>::split(circularArrayList& a,circularArrayList& b)
{
    a.clear();
    b.clear();
    for (int i = 0, j = 0, k = 0; i < size(); ++i)
    {
        if (i % 2) b.insert(j++, element[(i + first) % arrayLength]);	// odd
        else a.insert(k++, element[(i + first) % arrayLength]);		// even
    }
}

using namespace std;

int testIterator()
{
    // create a linear list
    circularArrayList<int> y(2);
    y.insert(0, 2);
    y.insert(1, 6);
    y.insert(0, 1);
    y.insert(2, 4);
    y.insert(3, 5);
    y.insert(2, 3);
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;

    // test iterator
    cout << "Output using forward iterators prefix and post ++" << endl;
    for (auto i = y.begin();
        i != y.end(); ++i)
        cout << *i << "  ";
    cout << endl;
    for (auto i = y.begin();
        i != y.end(); ++i)
        cout << *i << "  ";
    cout << endl;

    cout << "Output using backward iterators prefix and post --" << endl;
    for (circularArrayList<int>::iterator i = y.end();
        i != y.begin(); cout << *(--i) << "  ");
    cout << endl;
    for (circularArrayList<int>::iterator i = y.end();
        i != y.begin();)
    {
        i--; cout << *i << "  "; *i += 1;
    }
    cout << endl;
    cout << "Incremented by 1 list is " << y << endl;

    // try out some STL algorithms
    reverse(y.begin(), y.end());
    cout << "The reversed list is " << y << endl;
    int sum = accumulate(y.begin(), y.end(), 0);
    cout << "The sum of the elements is " << sum << endl;
    return 0;
}

int test()
{
    // test constructor
    linearList<double>* x = new circularArrayList<double>(20);
    circularArrayList<int> y(20), z;

    // test capacity
    cout << "Capacity of x, y and z = "
        << ((circularArrayList<double>*) x)->capacity() << ", "
        << y.capacity() << ", "
        << z.capacity() << endl;


    // test size
    cout << "Initial size of x, y, and z = "
        << x->size() << ", "
        << y.size() << ", "
        << z.size() << endl;

    // test empty
    if (x->empty()) cout << "x is empty" << endl;
    else cout << "x is not empty" << endl;
    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;

    // test insert
    y.insert(0, 2);
    y.insert(1, 6);
    y.insert(0, 1);
    y.insert(2, 4);
    y.insert(3, 5);
    y.insert(2, 3);
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;
    y.output(cout);
    cout << endl << "Testing overloaded <<" << endl;
    cout << y << endl;

    // test indexOf
    int index = y.indexOf(4);
    if (index < 0) cout << "4 not found" << endl;
    else cout << "The index of 4 is " << index << endl;

    index = y.indexOf(7);
    if (index < 0) cout << "7 not found" << endl;
    else cout << "The index of 7 is " << index << endl;

    // test get
    cout << "Element with index 0 is " << y.get(0) << endl;
    cout << "Element with index 3 is " << y.get(3) << endl;

    // test erase
    y.erase(1);
    cout << "Element 1 erased" << endl;
    cout << "The list is " << y << endl;
    cout << "The list capacity is " << y.capacity() << endl;
    y.erase(2);
    cout << "Element 2 erased" << endl;
    cout << "The list is " << y << endl;
    cout << "The list capacity is " << y.capacity() << endl;

    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
    if (y.empty()) cout << "y is empty" << endl;
    else cout << "y is not empty" << endl;

    try { y.insert(-3, 0); }
    catch (illegalIndex e)
    {
        cout << "Illegal index exception" << endl;
        cout << "Insert index must be between 0 and list size" << endl;
        e.outputMessage();
    }

    // test copy constructor
    circularArrayList<int> w(y);
    y.erase(0);
    y.erase(0);
    cout << "w should be old y, new y has first 2 elements removed" << endl;
    cout << "w is " << w << endl;
    cout << "y is " << y << endl;

    // a few more inserts, just for fun
    y.insert(0, 4);
    y.insert(0, 5);
    y.insert(0, 6);
    y.insert(0, 7);
    cout << "y is " << y << endl;

    // test reserve
    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
    y.reserve(10);
    cout << "Size of y = " << y.size() << endl;
    cout << "Capacity of y = " << y.capacity() << endl;
    y[4] = 3; y[5] = 2; y.reverse();
    cout << "y is " << y << endl;
    // test reverse
    y.reverse();
    cout << "y is " << y << endl;
    reverse(y);
    cout << "y is " << y << endl;
    // test meld
    circularArrayList<int> a(y);
    cout << "a is " << a << endl;
    z.meld(y, a);
    cout << "z is " << z << endl;
    // test merge
    z.merge(y, a);
    cout << "a is " << a << endl;
    cout << "z is " << z << endl;
    y.merge(a, z);
    cout << "a merge z is : y is " << y << endl;
    // test split
    y.split(a, z);
    cout << "a split from y:a is " << a << endl;
    cout << "z split from y:z is " << z << endl;
    // test clear
    y.clear();
    cout << "y.clear():     y is " << y << endl;
    return 0;
}
#endif