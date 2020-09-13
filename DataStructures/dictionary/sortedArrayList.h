// sorted array, implements dictionary
// There is a question: std::pair<const K,E>::operator=(...,...) is be deleted. 
// see: https://en.cppreference.com/w/cpp/utility/pair/operator%3D
#ifndef sortedArrayList_
#define sortedArrayList_

#include "dictionary.h"
#include "myExceptions.h"
#include "changeLength1D.h"
#include <sstream>

template<typename K,typename E>
class sortedArrayList :public dictionary<K, E>
{
public:
	sortedArrayList(int initialCapacity = 10);
	~sortedArrayList() { delete[] element; }

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	std::pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const std::pair<const K, E>&);
	void output(std::ostream& out) const;

protected:
	std::pair<const K, E>* element;		// array of the dictionary
	int arrayLength;
	int dSize;							// number of elemetns in dictionary
};

template<typename K,typename E>
sortedArrayList<K,E>::sortedArrayList(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new std::pair<const K, E>[arrayLength];
	dSize = 0;
}

template<typename K, typename E>
std::pair<const K, E>* sortedArrayList<K, E>::find(const K& theKey) const
{
	int left = 0;                       // left end of segment
	int right = dSize - 1;              // right end of segment
	while (left <= right) {
		int middle = (left + right) / 2;   // middle of segment
		if (theKey == element[middle].first) return element + middle;
		if (theKey > element[middle].first) left = middle + 1;
		else right = middle - 1;
	}

	// no match
	return nullptr;
}

template<typename K, typename E>
void sortedArrayList<K, E>::insert(const std::pair<const K, E>& thePair)
{
	// increase array capacity
	if (dSize == arrayLength)
	{
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	// find the position of insert
	int f = 0;
	while (f < dSize && element[f].first < thePair.first) ++f;

	// has same key
	if (f < dSize&& element[f].first == thePair.first)
	{
		element[f].second = thePair.second;
		return;
	}

	// not the last position of arrayList
	if (f != dSize)
		for (int i = dSize; i > f; --i) element[i] = element[i - 1];	// move element[f:dSize-1] to element[f+1:dSize]
	// insert the position
	element[f] = thePair;
	++dSize;
}

template<typename K, typename E>
void sortedArrayList<K, E>::erase(const K& theKey)
{
	// find the position of erase
	int f = 0;
	while (f < dSize && element[f].first < theKey) ++f;

	// found 
	if (f < dSize && element[f].first == theKey)
	{
		if (f != dSize - 1)
			for (int i = f; i < dSize; ++i) element[i] = element[i + 1];	// move element[f+1:dSize-1] to element[f:dSize-2]
		--dSize;		// nothing to do, just --dSize.
	}
}

template<typename K, typename E>
void sortedArrayList<K, E>::output(std::ostream& out) const
{
	for (int i = 0; i < dSize; ++i)
		out << element[i].first << " " << element[i].second << " ";
}

template<typename K, typename E>
std::ostream& operator<<(std::ostream& out, const sortedArrayList<K, E>& x)
{
	x.output(out);
	return out;
}
#endif // !sortedArrayList_
