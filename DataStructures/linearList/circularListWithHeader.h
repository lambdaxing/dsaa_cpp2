// singal circular linked list with header node

#ifndef circularListWithHeader_
#define circularListWithHeader_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "chainNode.h"
#include "myExceptions.h"
#include "extendedLinearList.h"

template<class T>
class circularListWithHeader : public extendedLinearList<T>
{
public:
	// constructor
	circularListWithHeader();
	circularListWithHeader(const circularListWithHeader<T>& theList);
	~circularListWithHeader();

	// ADT
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	void clear();
	void push_back(const T& theElement);

	// iterators to start and end of list
	class iterator;
	iterator begin() { return iterator(headerNode->next); }
	iterator end() { return iterator(headerNode); }

	// iterator for chain
	class iterator
	{
	public:
		// typedefs required by C++ for a forward iterator
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		// constructor
		iterator(chainNode<T>* theNode = headerNode)
		{
			node = theNode;
		}

		// dereferencing operators
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		// increment
		iterator& operator++()   // preincrement
		{
			node = node->next; return *this;
		}
		iterator operator++(int) // postincrement
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		// equality testing
		bool operator!=(const iterator right) const
		{
			return node != right.node;
		}
		bool operator==(const iterator right) const
		{
			return node == right.node;
		}
	protected:
		chainNode<T>* node;
	};  // end of iterator class
protected:
	void checkIndex(int theIndex) const;
	// throw illegalIndex if theIndex invalid
	chainNode<T>* lastNode;
	chainNode<T>* headerNode;  // pointer to header node
	int listSize;              // number of elements in list	
};

template<class T>
circularListWithHeader<T>::circularListWithHeader()
{// Constructor.
	headerNode = new chainNode<T>();
	lastNode = headerNode;
	lastNode->next = headerNode;
	listSize = 0;
}

template<typename T>
circularListWithHeader<T>::circularListWithHeader(const circularListWithHeader<T>& theList)
{
	headerNode = new chainNode<T>();
	lastNode = headerNode;
	chainNode<T>* theListNode = theList.headerNode->next;
	while (theList != theList.headerNode)
	{
		lastNode->next = new chainNode<T>(theListNode->element);
		lastNode = lastNode->next;
		theListNode = theListNode->next;
	}
	lastNode->next = headerNode;					// circular
	listSize = theList.listSize;
}


template<typename T>
circularListWithHeader<T>::~circularListWithHeader()
{
	if (headerNode == nullptr)
		return;
	chainNode<T>* nextNode;
	while (headerNode != lastNode)
	{// delete
		nextNode = headerNode->next;
		delete headerNode;
		headerNode = nextNode;
	}
	delete headerNode;
	headerNode = nullptr;
}

template<class T>
void circularListWithHeader<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& circularListWithHeader<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	chainNode<T>* currentNode = headerNode->next;
	for (int i = 0; i < theIndex; ++i) currentNode = currentNode->next;
	return currentNode->element;
}

template<class T>
int circularListWithHeader<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // Put theElement in header node
	headerNode->element = theElement;

	// search the chain for theElement
	chainNode<T>* currentNode = headerNode->next;
	int index = 0;  // index of currentNode
	while (currentNode->element != theElement)
	{
		// move to next node
		currentNode = currentNode->next;
		index++;
	}

	// make sure we found matching element
	if (currentNode == headerNode)
		return -1;
	else
		return index;
}

template<typename T>
void circularListWithHeader<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	// find predecessor of delete node
	chainNode<T>* p = headerNode;
	chainNode<T>* deleteNode;

	for (int i = 0; i < theIndex; ++i)
		p = p->next;

	deleteNode = p->next;
	p->next = p->next->next;
	delete deleteNode;
	deleteNode = nullptr;

	if (theIndex == listSize - 1) lastNode = p;
	--listSize;
}

template<class T>
void circularListWithHeader<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	// find predecessor of new element
	chainNode<T>* p = headerNode;
	for (int i = 0; i < theIndex; i++)
		p = p->next;

	// insert after p
	p->next = new chainNode<T>(theElement, p->next);

	if (theIndex == listSize) lastNode = p->next;
	++listSize;
}

template<typename T>
void circularListWithHeader<T>::clear()
{
	chainNode<T>* currentNode = headerNode->next;
	chainNode<T>* temp;
	while (currentNode != headerNode)
	{
		temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	lastNode = currentNode;
	listSize = 0;
}

template<class T>
void circularListWithHeader<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	for (chainNode<T>* currentNode = headerNode->next;
		currentNode != headerNode;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}

template<typename T>
void circularListWithHeader<T>::push_back(const T& theElement)
{
	lastNode->next = new chainNode<T>(theElement, headerNode);
	lastNode = lastNode->next;
	++listSize;
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const circularListWithHeader<T>& x)
{
	x.output(out); return out;
}

#endif