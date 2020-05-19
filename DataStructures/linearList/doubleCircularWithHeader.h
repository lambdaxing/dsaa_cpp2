// dcircular doubly linked list with header

#ifndef DOUBLE_CIRCULAR_WITH_HEADER
#define DOUBLE_CIRCULAR_WITH_HEADER

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "doubleChainNode.h"
#include "myExceptions.h"
#include "extendedLinearList.h"


template<typename T>
class doubleCircularWithHeader : public extendedLinearList<T>
{
public:
	doubleCircularWithHeader(int initialCapacity = 10);
	doubleCircularWithHeader(const doubleCircularWithHeader<T>& theList);
	~doubleCircularWithHeader();

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	void clear();
	void push_back(const T& theElement);

	class iterator;
	iterator begin() { return iterator(header->next); }
	iterator end() { return iterator(header); }
	const iterator cbegin() const { return iterator(header->next); }
	const iterator cend() const { return iterator(header); }

	// iterator for doubleCircularWithHeader
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
		iterator(doubleChainNode<T>* theNode = nullptr) :node(theNode) {}

		// dereferencing operators
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		// increment
		iterator& operator++() { node = node->next; return *this; }
		iterator operator++(int) { iterator old = *this; node = node->next; return old; }

		// decrease
		iterator& operator--() { node = node->previous; return *this; }
		iterator operator--(int) { iterator old = *this; node = node->previous; return old; }

		// equality 
		bool operator!=(const iterator right) const { return node != right.node; }
		bool operator==(const iterator right) const { return node == right.node; }

	protected:
		doubleChainNode<T>* node;
	};	// end of iterator class

protected:
	void checkIndex(int theIndex) const;
	doubleChainNode<T>* header;				//	lastNode == header->previous		firstNode = header->next
	int listSize;
};

template<typename T>
doubleCircularWithHeader<T>::doubleCircularWithHeader(int initialCapacity /* = 10 */)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	header = new doubleChainNode<T>();
	header->previous = header->next = header;
	listSize = 0;
}

template<typename T>
doubleCircularWithHeader<T>::doubleCircularWithHeader(const doubleCircularWithHeader<T>& theList)
{// Copy constructor.
	listSize = theList.listSize;
	header = new doubleChainNode<T>();
	doubleChainNode<T>* sourceNode = theList.header->next;
	doubleChainNode<T>* targetNode = header;
	// current last node in *this
	while (sourceNode != theList.header)
	{// copy remaining elements
		targetNode->next = new doubleChainNode<T>(sourceNode->element, targetNode);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = header;			// end the chain
	header->previous = targetNode;		// begin the chain 
}

template<typename T>
doubleCircularWithHeader<T>::~doubleCircularWithHeader()
{
	if (header == nullptr)
		return;
	doubleChainNode<T>* nextNode;
	doubleChainNode<T>* current = header->next;
	while (current != header)
	{// delete
		nextNode = current->next;
		delete current;
		current = nextNode;
	}
	delete current;
}

template<typename T>
void doubleCircularWithHeader<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& doubleCircularWithHeader<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	doubleChainNode<T>* p;
	if (theIndex < listSize / 2)
	{
		p = header->next;
		for (int i = 0; i < theIndex; ++i)
			p = p->next;
	}
	else
	{
		p = header->previous;
		for (int i = listSize; i > theIndex - 1; --i)
			p = p->previous;
	}
	return p->element;
}

template<typename T>
int doubleCircularWithHeader<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // Put theElement in header node
	header->element = theElement;

	// search the chain for theElement
	doubleChainNode<T>* currentNode = header->next;
	int index = 0;  // index of currentNode
	while (currentNode->element != theElement)
	{
		// move to next node
		currentNode = currentNode->next;
		index++;
	}

	// make sure we found matching element
	if (currentNode == header)
		return -1;
	else
		return index;
}

template<typename T>
void doubleCircularWithHeader<T>::erase(int theIndex)
{
	checkIndex(theIndex);

	// find predecessor of delete node
	doubleChainNode<T>* p = header;
	doubleChainNode<T>* deleteNode;

	for (int i = 0; i < theIndex; ++i)
		p = p->next;

	deleteNode = p->next;
	p->next = p->next->next;
	p->next->previous = p;
	delete deleteNode;
	deleteNode = nullptr;
	--listSize;
}

template<typename T>
void doubleCircularWithHeader<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	// find predecessor of new element
	doubleChainNode<T>* p = header;
	for (int i = 0; i < theIndex; i++)
		p = p->next;

	// insert after p
	p->next = new doubleChainNode<T>(theElement, p, p->next);
	p->next->next->previous = p->next;
	++listSize;
}

template<typename T>
void doubleCircularWithHeader<T>::clear()
{
	doubleChainNode<T>* currentNode = header->next;
	doubleChainNode<T>* temp;
	while (currentNode != header)
	{
		temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	header->previous = header->next = header;
	listSize = 0;
}

template<typename T>
void doubleCircularWithHeader<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	for (doubleChainNode<T>* currentNode = header->next;
		currentNode != header;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}

template<typename T>
void doubleCircularWithHeader<T>::push_back(const T& theElement)
{
	header->previous->next = new doubleChainNode<T>(theElement, header->previous, header);
	header->previous = header->previous->next;
	++listSize;
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const doubleCircularWithHeader<T>& x)
{
	x.output(out); return out;
}

#endif