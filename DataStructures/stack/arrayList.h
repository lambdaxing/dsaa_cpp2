// array implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// USES STL ALGORITHMS TO SIMPLIFY CODE

#ifndef arrayList_
#define arrayList_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

template<typename T>
class arrayList :
	public linearList<T>
{
public:
	arrayList(int initialCapacity = 10);
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

	// other
	int capacity() const { return arrayLength; }

protected:
	void checkIndex(int theIndex) const;
	T* element;
	int arrayLength;
	int listSize;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x);

template<typename T>
arrayList<T>::arrayList(int initialCapacity /* = 10 */)
{
	if (initialCapacity < 1) {
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

// copy constructor
template<typename T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template<typename T>
void arrayList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
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
	//if (listSize < arrayLength / 4) {

	//}
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
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
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

#endif