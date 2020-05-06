// array implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// USES STL ALGORITHMS TO SIMPLIFY CODE
// iterator class for arrayList included

#ifndef arrayList_
#define arrayList_

#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<iterator>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

template<typename T> class arrayList;
template<typename T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x);
template<typename T>
bool operator ==(const arrayList<T>& lhs, const arrayList<T>& rhs);
template<typename T>
bool operator !=(const arrayList<T>& lhs, const arrayList<T>& rhs);
template<typename T>
bool operator  <(const arrayList<T>& lhs, const arrayList<T>& rhs);

template<typename T>
class arrayList :
	public linearList<T>
{
	// ex5_8_9_10
	friend bool operator ==<T>(const arrayList<T>& lhs, const arrayList<T>& rhs);
	friend bool operator !=<T>(const arrayList<T>& lhs, const arrayList<T>& rhs);
	friend bool operator < <T>(const arrayList<T>& lhs, const arrayList<T>& rhs);
public:
	// ex5_4
	arrayList(int initialCapacity = 10, int multiple = 2);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element; }

	// ADT
	bool empty() const override { return listSize == 0; }
	int size() const override { return listSize; }
	T& get(int theIndex) const override;
	int indexOf(const T& theElement) const override;
	void erase(int theIndex) override;
	void insert(int theIndex, const T& theElement) override;
	void output(std::ostream& out) const override;

	// others
	int capacity() const { return arrayLength; }
	// ex5_5 The complexity of this function is the same as that of changeLength1D, i.e., O(listSize).
	void trimToSize();										
	// ex5_6 The complexity of this function is O(listSize).
	void setSize(int newSize);
	// ex5_7
	T& operator[](int theIndex) const;
	// ex5_11 The complexity of this function is O(n).
	void push_back(const T& theElement);
	// ex5_12 The complexity of this function is O(1).
	void pop_back();
	// ex5_13 The complexity of this function is O(n).
	void swap(arrayList& theList);
	// ex5_14
	void reserve(int theCapacity);
	// ex5_15
	T set(int theIndex, const T& theElement);
	// ex5_16 The complexity of this function is O(1).
	void clear();
	// ex5_17
	void removeRange(int b, int e);
	// ex5_18
	int lastIndexOf(const T& theElement) const;
	// ex5_22
	void reverse();
	// ex5_23
	void leftShift(int i);
	// ex5_24
	void circularShift(int i);
	// ex5_25
	void half();
	// ex5_28
	void meld(const arrayList& a, const arrayList& b);
	// ex5_29
	void merge(const arrayList& a, const arrayList& b);
	// ex5_30
	void split(arrayList& a, arrayList& b);

	// iterators to start and end of list
	class iterator;
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }
	const iterator cbegin() const { return iterator(element); }
	const iterator cend() const { return iterator(element + listSize); }
	// iterator for arrayList
	class iterator
	{
	public:
		// typedefs required by C++ for a bidirectional iterator
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		// constructor
		iterator(T* thePosition = 0) { position = thePosition; }

		// dereferencing operator
		T& operator* () const { return *position; }
		T* operator->() const { return &*position; }

		iterator& operator++() { ++position; return *this; }
		iterator operator++(int)
		{
			iterator old = *this;
			++position;
			return old;
		}
		iterator& operator--() { --position; return *this; }
		iterator operator--(int)
		{
			iterator old = *this;
			--position;
			return old;
		}

		bool operator!=(const iterator& rhs) const { return position != rhs.position; }
		bool operator==(const iterator& rhs) const { return position == rhs.position; }

		iterator& operator+=(std::size_t rhs) { position += rhs; return *this; }
		iterator& operator-=(std::size_t rhs) { position -= rhs; return *this; }
		T& operator[](std::size_t i) { return position[i]; }
		const T& operator[](std::size_t i) const { return position[i]; }

		bool operator <(const iterator& rhs) const { return position < rhs.position; }
		bool operator<=(const iterator& rhs) const { return position <= rhs.position; }
		bool operator> (const iterator& rhs) const { return position > rhs.position; }
		bool operator>=(const iterator& rhs) const { return position >= rhs.position; }
		iterator operator+ (std::size_t rhs) const
		{
			iterator t = *this;
			t += rhs;
			return t;
		}
		iterator operator- (std::size_t rhs) const
		{
			iterator t = *this;
			t -= rhs;
			return t;
		}
		difference_type operator- (const iterator& rhs) const { return position - rhs.position; }
	protected:
		T* position;
	};
	
protected:
	void checkIndex(int theIndex) const;
	T* element;
	int arrayLength = 10;
	int listSize = 0;
	int arrayMultiple = 2;	// multiple of increase
};

// ex5_8
template<typename T>
bool operator ==(const arrayList<T>& lhs, const arrayList<T>& rhs)
{
	if (lhs.listSize != rhs.listSize) return false;

	for (int i = 0; i < lhs.listSize; ++i)
		if (lhs[i] != rhs[i]) return false;
	return true;
}

// ex5_9
template<typename T>
bool operator !=(const arrayList<T>& lhs, const arrayList<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool operator <(const arrayList<T>& lhs, const arrayList<T>& rhs)
{
	int minSize = std::min(rhs.listSize, lhs.listSize);

	// one by one to compare
	for (int i = 0; i < minSize; ++i)
		if (lhs[i] > rhs[i]) return false;
	// redundant elements
	if (lhs.listSize > rhs.listSize) return false;

	return true;
}

// ex5_10
template<typename T>
arrayList<T>::arrayList(int initialCapacity /* = 10 */,int multiple /* = 2*/)
{
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	if (multiple <= 1) {
		std::ostringstream s;
		s << "Multiple = " << multiple << " Must be > 1";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
	arrayMultiple = multiple;
}

// ex5_11
template<typename T>
void arrayList<T>::push_back(const T& theElement)
{
	// increase array length
	if (listSize == arrayLength) {
		changeLength1D(element, arrayLength, arrayMultiple * arrayLength);
		arrayLength *= arrayMultiple;
	}
	element[listSize++] = theElement;		// push
}

// ex5_12
template<typename T>
void arrayList<T>::pop_back()
{
	element[--listSize].~T();
}

// ex5_13
template<class T>
void arrayList<T>::swap(arrayList<T>& theList)
{// Swap the two lists.
	using std::swap;
	swap(arrayLength, theList.arrayLength);
	swap(listSize, theList.listSize);
	swap(element, theList.element);
}

// ex5_14
template<typename T>
void arrayList<T>::reserve(int theCapacity)
{
	if (theCapacity <= arrayLength)
		return;
	changeLength1D(element, arrayLength, theCapacity);
	arrayLength = theCapacity;
}

// ex5_15
template<typename T>
T arrayList<T>::set(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	T temp = element[theIndex];
	element[theIndex] = theElement;
	return temp;
}

// ex5_16
template<typename T>
void arrayList<T>::clear()
{
	delete[] element;
	element = new T[arrayLength];
	listSize = 0;
}

// ex5_17
template<typename T>
void arrayList<T>::removeRange(int b, int e)
{
	if (b < 0 || e > listSize)
		throw illegalIndex();

	if (b >= e)
		// nothing to remove
		return;

	std::copy(element + e, element + listSize, element + b);	
	int size = e - b;
	while (size--)
		pop_back();
}

// ex5_18
template<typename T>
int arrayList<T>::lastIndexOf(const T& theElement) const
{
	for (int i = listSize - 1; i >= 0; --i)
		if (element[i] == theElement) return i;
	return -1;
}

// ex5_22
template<typename T>
void arrayList<T>::reverse()
{
	for (int i = 0; i < listSize / 2; ++i)
		std::swap(element[i], element[listSize - i - 1]);
}

// ex5_22
template<typename T>
void reverse(arrayList<T>& theList)
{
	using std::swap;
	for (int i = 0; i < theList.size() / 2; ++i)
		swap(theList[i], theList[theList.size() - i - 1]);
}

// ex5_23
template<typename T>
void arrayList<T>::leftShift(int i)
{
	if (i <= 0)
		return;

	if (i >= listSize)
		clear();
	else {
		std::copy(element + i, element + listSize, element);
		while (i--)
			pop_back();
	}
}

// ex5_24
template<typename T>
void arrayList<T>::circularShift(int i)
{
	using std::swap;
	int moveSize = i % listSize;
	int mid1 = moveSize / 2;
	int mid2 = moveSize + (listSize - moveSize) / 2;
	for (int j = 0; j < mid1; ++j)
		swap(element[j], element[moveSize - j - 1]);
	for (int j = moveSize, k = 0; j < mid2; ++j, ++k)
		swap(element[moveSize], element[listSize - k - 1]);
	reverse();
}

// ex2_25
template<typename T>
void arrayList<T>::half()
{
	if (listSize == 0)
		return;
	for (int i = 0, j = 0; i < listSize; ++i)
		if (!(i%2)) 
			element[j++] = element[i];
	int num = listSize / 2;
	while (num--)
		element[--listSize].~T();

}

// ex2_26
template<typename T>
void half(arrayList<T>& theList)
{// Remove all odd indexed elements.

   // move even indexed elements to new spots
	for (int i = 2; i < theList.size(); i += 2)
		theList[i / 2] = theList[i];

	// destroy uneeded elements
	int num = theList.size() / 2;
	while (num--)
		theList.pop_back();
}

// ex2_28
template<typename T>
void arrayList<T>::meld(const arrayList& a, const arrayList& b)
{
	int size = a.listSize + b.listSize;
	reserve(size);
	auto abegin = a.cbegin(), bbegin = b.cbegin();
	for (int i = 0; i < size; ++i) {
		if (i % 2 && abegin != a.cend() || bbegin == b.cend())
			element[i] = *abegin++;
		else 
			element[i] = *bbegin++;
	}
	listSize = size;		
}

// ex2_29
template<typename T>
void arrayList<T>::merge(const arrayList& a, const arrayList& b)
{
	int size = a.listSize + b.listSize;
	reserve(size);
	auto abegin = a.cbegin(), bbegin = b.cbegin();
	for (int i = 0; i < size; ++i) {
		if (abegin != a.cend() && bbegin != b.cend() && *abegin < *bbegin ||
			abegin != a.cend() && bbegin == b.cend())
			element[i] = *abegin++;
		else
			element[i] = *bbegin++;
	}
	listSize = size;
}

// ex5_30
template<typename T>
void arrayList<T>::split(arrayList& a, arrayList& b)
{
	a.clear();
	b.clear();
	for (int i = 0, j = 0, k = 0; i < listSize; ++i)
	{
		if (i % 2) b.push_back(element[i]);	// odd
		else a.push_back(element[i]);		// even
	}
}

// copy constructor
template<typename T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
	arrayLength = theList.arrayLength;
	arrayMultiple = theList.arrayMultiple;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template<typename T>
void arrayList<T>::checkIndex(int theIndex) const
{
	//std::cout << theIndex << std::endl;
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& arrayList<T>::operator[] (int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}

template<typename T>
T& arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex];
}

template<typename T>
int arrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = static_cast<int>(std::find(element, element + listSize, theElement) - element);

	if (theIndex == listSize)	// not found
		return -1;
	else
		return theIndex;
}

template<typename T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	std::copy(element + theIndex + 1, element + listSize, element + theIndex);

	element[--listSize].~T();	// invoke destructor

	// reduce array length
	if (listSize < arrayLength / 4) {
		changeLength1D(element, arrayLength, arrayLength / 2);
		arrayLength /= 2;
	}
}

template<typename T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	// increase array length
	if (listSize == arrayLength) {
		if (arrayLength <= 0) arrayLength = 10;
		changeLength1D(element, arrayLength, arrayMultiple * arrayLength);
		arrayLength *= arrayMultiple;
	}

	// move the elements on the right of theIndex one place to the right as a whole
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

	element[theIndex] = theElement;		// insert
	++listSize;
}

template<typename T>
void arrayList<T>::output(std::ostream& out) const
{
	std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
	x.output(out);
	return out;
}

template<typename T>
void arrayList<T>::trimToSize()
{// Make array length equal to max{listSize, 1}

	if (arrayLength == listSize)
		return;

	if (listSize == 0)
	{// replace with array of length 1
		delete[] element;
		element = new T[1];
		arrayLength = 1;
		return;
	}

	// need to change array length and copy eleements into new array
	changeLength1D(element, listSize, listSize);
	arrayLength = listSize;
}

template <typename T>
void arrayList<T>::setSize(int newSize)
{
	if (listSize <= newSize)
		return;
	else if (listSize > newSize)		// erase redundant elements
		while(listSize > newSize)
			element[--listSize].~T();	// invoke destructor
}

using namespace std;
int ex5_4()
{
	// test constructor
	linearList<double>* x = new arrayList<double>(20);
	arrayList<int> y(20), z;

	// test capacity
	cout << "Capacity of x, y and z = "
		<< ((arrayList<double>*) x)->capacity() << ", "
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
	arrayList<int> w(y);
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

	// test trimToSize
	y.trimToSize();
	cout << "y.trimToSize():" << endl << "y is " << y << endl;

	// test setSize
	y.setSize(6);
	y.setSize(20);
	y.setSize(2);
	cout << "y.setSize(2):" << endl << "y is " << y << endl;

	// test ==, !=, <, push_back,pop_back,swap
	z.push_back(7);
	cout << "z is " << z << endl;
	cout << "y == z is " << (y == z ? "true" : "false") << endl;
	cout << "y != z is " << (y != z ? "true" : "false") << endl;
	cout << "y <  z is " << (y < z ? "true" : "false") << endl;
	z.push_back(6);
	cout << "z is " << z << endl;
	cout << "y == z is " << (y == z ? "true" : "false") << endl;
	cout << "y != z is " << (y != z ? "true" : "false") << endl;
	cout << "y <  z is " << (y < z ? "true" : "false") << endl;
	z.push_back(0);
	cout << "z is " << z << endl;
	cout << "y == z is " << (y == z ? "true" : "false") << endl;
	cout << "y != z is " << (y != z ? "true" : "false") << endl;
	cout << "y <  z is " << (y <  z ? "true" : "false") << endl;
	z.pop_back();
	cout << "z is " << z << endl;

	// test swap
	y.push_back(1); y.push_back(2); y.push_back(3);
	cout << "y is " << y << endl;
	z.swap(y);
	cout << "z is " << z << endl;
	cout << "y is " << y << endl;
	// test reserve
	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	y.reserve(10);
	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	cout << "y is " << y << endl;
	// test set
	y.set(1, 10);
	cout << "y is " << y << endl;
	// test clear
	y.clear();
	cout << "y is " << y << endl;
	// test removeRange
	z.removeRange(2, 2);
	cout << "z is " << z << endl;
	z.removeRange(2, 4);
	cout << "z is " << z << endl;
	// test lastIndexOf
	cout << z.lastIndexOf(7) << endl;
	cout << z.lastIndexOf(11) << endl;
	// test reverse
	z.reverse();
	cout << "z is " << z << endl;
	reverse(z);
	cout << "z is " << z << endl;
	// test leftshift
	z.leftShift(1);
	cout << "z is " << z << endl;
	z.leftShift(2);
	cout << "z is " << z << endl;
	// test circularShift
	z.push_back(0); z.push_back(1); z.push_back(2); z.push_back(3); z.push_back(4);
	arrayList<int> a(z);
	cout << "z is " << z << endl;
	cout << "a is " << a << endl;
	z.circularShift(2);
	a.circularShift(7);
	cout << "z is " << z << endl;
	cout << "a is " << a << endl;
	// test half
	a.push_back(5);
	a.half();
	half(z);
	cout << "z is " << z << endl;
	cout << "a is " << a << endl;
	// test sort
	std::sort(z.begin(), z.end());
	std::sort(a.begin(), a.end());
	cout << "z is " << z << endl;
	cout << "a is " << a << endl;
	// test meld
	y.meld(z, a);
	cout << "y is " << y << endl;
	// test merge
	y.merge(z, a);
	cout << "y is " << y << endl;
	z.merge(a, y);
	cout << "z is " << z << endl;
	// test split
	z.split(a, y);
	cout << "a is " << a << endl;
	cout << "y is " << y << endl;
	return 0;
}

#endif
