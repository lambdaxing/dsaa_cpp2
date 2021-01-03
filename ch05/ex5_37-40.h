#ifndef vectorList_
#define vectorList_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <memory>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

template<typename T>
class vectorList :public linearList<T>
{
public:

	vectorList(int initialCapacity = 10);
    vectorList(const vectorList<T>& theList) :element(std::make_shared<std::vector<T>>(*theList.element)) {}
	~vectorList() {};

	// ADT
	bool empty() const override { return element->empty(); }
	int size() const override { return static_cast<int>(element->size()); }
    T& get(int theIndex) const override { checkIndex(theIndex); return (*element)[theIndex]; }
	int indexOf(const T& theElement) const override;
	void erase(int theIndex) override;
	void insert(int theIndex, const T& theElement) override;
    void output(std::ostream& out) const override;

	int capacity() const { return static_cast<int>(element->capacity()); }
    void clear() { element->clear(); }
    void push_back(const T& theElement) { element->push_back(theElement); }

	// ex5_37
	void half();
	// ex5_38
	void meld(const vectorList& a, const vectorList& b);
	// ex5_39
	void merge(const vectorList& a, const vectorList& b);
	// ex5_40
	void split(vectorList& a, vectorList& b);

	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }
	const_iterator cbegin() const { return element->cbegin(); }
    const_iterator cend() const { return element->cend(); }

protected:
	void checkIndex(int theIndex) const;
	std::shared_ptr<std::vector<T>> element;
};

template<class T>
void vectorList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
    std::copy(element->begin(), element->end(), std::ostream_iterator<T>(out, "  "));
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const vectorList<T>& x)
{
    x.output(out); return out;
}

template<typename T>
void vectorList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= size()) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw illegalIndex(s.str());
	}
}

template<typename T>
int vectorList<T>::indexOf(const T& theElement) const
{
	auto f = std::find(cbegin(), cend(), theElement);
	if (f == cend()) return -1;
	else return f - cbegin();
}

template<typename T>
vectorList<T>::vectorList(int initialCapacity /* = 10 */)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}

	element = std::make_shared<std::vector<T>>();
	element->reserve(initialCapacity);
}

template<typename T>
void vectorList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}

template<typename T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > size())
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size " << size();
		throw illegalIndex(s.str());
	}
	element->insert(element->begin() + theIndex, theElement);
}

template<typename T>
void vectorList<T>::half()
{
	if (size() == 0)
		return;
	for (int i = 0, j = 0; i < size(); ++i)
		if (!(i % 2))
            (*element)[j++] = (*element)[i];
	int num = size() / 2;
	element->erase(element->end() + num, element->end());
}

template<typename T>
void vectorList<T>::meld(const vectorList& a, const vectorList& b)
{
	int num = a.size() + b.size();
	element->resize(num);
	auto acb = a.cbegin(), bcb = b.cbegin();
    for (int i = 0; i < num; ++i)
    {
		if (i % 2 && acb != a.cend() || bcb == b.cend())
            (*element)[i] = *acb++;
		else
            (*element)[i] = *bcb++;
	}
}

template<typename T>
void vectorList<T>::merge(const vectorList& a, const vectorList& b)
{
	int size = a.size() + b.size();
	element->resize(size);
	auto abegin = a.cbegin(), bbegin = b.cbegin();
	for (int i = 0; i < size; ++i) {
		if (abegin != a.cend() && bbegin != b.cend() && *abegin < *bbegin ||
			abegin != a.cend() && bbegin == b.cend())
            (*element)[i] = *abegin++;
		else
            (*element)[i] = *bbegin++;
	}
}

template<typename T>
void vectorList<T>::split(vectorList& a, vectorList& b)
{
	a.clear();
	b.clear();
	for (int i = 0; i < size(); ++i)
	{
		if (i % 2) b.push_back((*element)[i]);	// odd
		else a.push_back((*element)[i]);		// even
	}
}

using namespace std;

int test()
{
    // test constructor
    linearList<double>* x = new vectorList<double>(20);
    vectorList<int> y(20), z;

    // test capacity
    cout << "Capacity of x, y and z = "
        << ((vectorList<double>*) x)->capacity() << ", "
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
    y.insert(1, 9);
    y.insert(0, 1);
    y.insert(2, 4);
    y.insert(3, 8);
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
    vectorList<int> w(y);
    y.erase(0);
    y.erase(0);
    cout << "w should be old y, new y has first 2 elements removed" << endl;
    cout << "w is " << w << endl;
    cout << "y is " << y << endl;

    // a few more inserts, just for fun
    y.insert(0, 7);
    y.insert(0, 6);
    y.insert(0, 5);
    y.insert(0, 4);
    
    cout << "y is " << y << endl;

    // test meld
    vectorList<int> a(y);
    cout << "a is " << a << endl;
    z.meld(y, a);
    cout << "z is " << z << endl;
    // test merge
    z.merge(y, a);
    cout << "a is " << a << endl;
    cout << "z is " << z << endl;
    y.merge(a, z);
    cout << "a merge z is   y is " << y << endl;
    // test split
    y.split(a, z);
    cout << "a split from y:a is " << a << endl;
    cout << "z split from y:z is " << z << endl;
    return 0;
}
#endif