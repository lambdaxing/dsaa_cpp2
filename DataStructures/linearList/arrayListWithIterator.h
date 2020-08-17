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

template<typename T>
class arrayList :public linearList<T>
{
public:
	// constructor, copy constructor and destructor
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element; }

	// ADT methods
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	// additional method
	int capacity() const { return arrayLength; }

	// iterators to start and end of list
	class iterator;
	iterator begin() { return iterator(element); }
	iterator end() { return iterator(element + listSize); }

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
		iterator(T* thePosition = nullptr) { position = thePosition; }

		// dereferencing operator
		T& operator* () const { return *position; }
		T* operator->() const { return &*position; }

		// increment
		iterator& operator++() { ++position; return *this; }	// preincrement
		iterator operator++(int)								// postincrement
		{
			iterator old = *this;
			++position;
			return old;
		}
		// decrement
		iterator& operator--() { --position; return *this; }	// predecrement
		iterator operator--(int)								// postdecrement
		{
			iterator old = *this;
			--position;
			return old;
		}

		// equality testing
		bool operator!=(const iterator& rhs) const { return position != rhs.position; }
		bool operator==(const iterator& rhs) const { return position == rhs.position; }

		// others
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
	};// end of iterator class

protected:	// additional members of arrayList
	void checkIndex(int theIndex) const;
	// throw illegalIndex if theIndex invalid
	T* element;            // 1D array to hold list elements
	int arrayLength;       // capacity of the 1D array
	int listSize;          // number of elements in list
};

template<typename T>
arrayList<T>::arrayList(int initialCapacity /* = 10 */)
{// Constructor.
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<typename T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{// Copy constructor.
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template<typename T>
void arrayList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& arrayList<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);
	return element[theIndex];
}

template<typename T>
int arrayList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search for theElement
	int theIndex = static_cast<int>(std::find(element, element + listSize, theElement) - element);

	// check if theElement was found
	if (theIndex == listSize)
		return -1;		// not found
	else
		return theIndex;
}

template<typename T>
void arrayList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// valid index, shift elements with higher index
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);

	element[--listSize].~T();	// invoke destructor

	// reduce array length
	//if (listSize < arrayLength / 4) {

	//}
}

template<typename T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize) 
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	// valid index, make sure we have space
	if (listSize == arrayLength) 
	{// no space, double capacity
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	// shift elements right one position
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

	element[theIndex] = theElement;

	++listSize;
}

template<typename T>
void arrayList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	std::copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

// overload <<
template<typename T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
	x.output(out);
	return out;
}

#endif