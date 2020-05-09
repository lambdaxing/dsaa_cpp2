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

	vectorList(int initialCapacity = 10);
	vectorList(const vectorList<T>& theList) :element(theList.element);
	~vectorList() {};

	// ADT
	bool empty() const override { return element->empty(); }
	int size() const override { return static_cast<int>(element->size()); }
	T& get(int theIndex) const override { return *element[theIndex] };
	int indexOf(const T& theElement) const override;
	void erase(int theIndex) override;
	void insert(int theIndex, const T& theElement) override;
	void output(std::ostream& out) const override 
	{
		for (const auto& i : *element) out << i << " ";
	}

	int capacity() const { return static_cast<int>(element->capacity()); }

	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }
	const_iterator cbegin() { return element->cbegin(); }
	const_iterator cend() { return element->cend(): }

protected:
	void checkIndex(int theIndex) const;
	std::shared_ptr<std::vector<T>> element;
};

template<typename T>
void vectorList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= size()) {
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
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
	if (initialCapaticy < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapaticy << " Must be > 0";
		throw illegalParameterValue(s.str());
	}

	element = std::make_shared<std::vector<T>>();
	element->reserve(initialCapaticy);
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

#endif