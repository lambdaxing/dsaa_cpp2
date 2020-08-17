// vector implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// USES STL ALGORITHMS TO SIMPLIFY CODE
// iterator class for vectorList included

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
	// constructor, copy constructor and destructor
	vectorList(int initialCapacity = 10);
	vectorList(const vectorList<T>& theList) :element(theList.element);
	~vectorList() {};

	// ADT methods
	bool empty() const override { return element->empty(); }
	int size() const override { return static_cast<int>(element->size()); }
	T& get(int theIndex) const override;
	int indexOf(const T& theElement) const override;
	void erase(int theIndex) override;
	void insert(int theIndex, const T& theElement) override;
	void output(std::ostream& out) const override;

	// additional method
	int capacity() const { return static_cast<int>(element->capacity()); }

	// iterators to start and end of list
	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }
	const_iterator cbegin() { return element->cbegin(); }
	const_iterator cend() { return element->cend(): }

protected:		// additional members of vectorList
	void checkIndex(int theIndex) const;
	std::shared_ptr<std::vector<T>> element;	// vector to hold list elements
};

template<typename T>
vectorList<T>::vectorList(int initialCapacity /* = 10 */)
{// Constructor.
	if (initialCapaticy < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapaticy << " Must be > 0";
		throw illegalParameterValue(s.str());
	}

	element = std::make_shared<std::vector<T>>();
	// create an empty vector with capacity 0
	element->reserve(initialCapaticy);
	// increase vector capacity from 0 to initialCapacity
}

template<typename T>
void vectorList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and size() - 1.
	if (theIndex < 0 || theIndex >= size()) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& vectorList<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);
	return (*element)[theIndex];
}

template<typename T>
int vectorList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

	 // search for theElement
	auto f = std::find(cbegin(), cend(), theElement);

	// check if theElement was found
	if (f == cend()) return -1;	     // not found
	else return f - cbegin();
}

template<typename T>
void vectorList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}

template<typename T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > size())
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size " << size();
		throw illegalIndex(s.str());
	}

	element->insert(element->begin() + theIndex, theElement);
	// may throw an uncaught exception if insufficient
		  // memory to resize vector
}

template<typename T>
void vectorList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	std::copy(element->cbegin(), element->cend(), std::ostream_iterator<T>(std::cout, "  "));
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const vectorList<T>& x)
{
	x.output(out); return out;
}

#endif