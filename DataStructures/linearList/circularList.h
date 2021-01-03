// singly linked circular list

#ifndef CIRCULAR_LIST
#define CIRCULAR_LIST

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "extendedChain.h"

template<typename T>
class circularList : public extendedChain<T>
{
public:
	// constructor, copy constructor and destructor
	circularList(int initialCapacity = 10) : extendedChain<T>(initialCapacity) {}
	circularList(const circularList<T>& theList);
	~circularList();

	// ADT methods
	bool empty() const { return this->listSize == 0; }
	int size() const { return this->listSize; }
	T& get(int theIndex) const { return extendedChain<T>::get(theIndex); }
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void clear()
	{// Delete all nodes in chain.
		while (this->firstNode != this->lastNode)
		{// delete firstNode
			chainNode<T>* nextNode = this->firstNode->next;
			delete this->firstNode;
			this->firstNode = nextNode;
		}
		delete this->firstNode;
		this->firstNode = this->lastNode = nullptr;
		this->listSize = 0;
	}
	void push_back(const T& theElement);
	void output(std::ostream& out) const;

	// iterators to start and end of list
	class iterator;
	iterator begin() { return iterator(this->firstNode); }
	const iterator cbegin() const { return iterator(this->firstNode); }
	iterator end() { return iterator(this->lastNode); }
	const iterator cend() const { return iterator(this->lastNode); }

	bool operator==(const circularList& rhs) const;
	bool operator!=(const circularList& rhs) const;
	bool operator <(const circularList& rhs) const;
	bool operator>=(const circularList& rhs) const;
	bool operator >(const circularList& rhs) const;
	bool operator<=(const circularList& rhs) const;

	// iterator for circularList , there is a question: the lastNode is the end iterator. 
	class iterator
	{
	public:
		// typedefs required by C++ for a forward iterator
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		typedef const iterator const_iterator;

		// constructor
		iterator(chainNode<T>* theNode = nullptr)
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
};

template<typename T>
circularList<T>::circularList(const circularList<T>& theList)
{
	// Copy constructor.
	this->listSize = theList.listSize;

	if (this->listSize == 0)
	{// theList is empty
		this->firstNode = this->lastNode = nullptr;
		return;
	}

	// non-empty list
	chainNode<T>* sourceNode = theList.firstNode;
	// node in theList to copy from
	this->firstNode = new chainNode<T>(sourceNode->element);
	// copy first element of theList
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = this->firstNode;
	// current last node in *this
	while (sourceNode != theList.firstNode)
	{// copy remaining elements
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	this->lastNode = targetNode;
	this->lastNode->next = this->firstNode; // end the chain
}

template<typename T>
circularList<T>::~circularList()
{
	if (this->firstNode == nullptr)
		return;
	chainNode<T>* nextNode;
	while (this->firstNode != this->lastNode)
	{// delete firstNode
		nextNode = this->firstNode->next;
		delete this->firstNode;
		this->firstNode = nextNode;
	}
	delete this->firstNode;
	this->firstNode = nullptr;
}

template<typename T>
int circularList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search the chain for theElement
	chainNode<T>* currentNode = this->firstNode;
	if (currentNode == nullptr)
		return -1;
	if (currentNode != nullptr && currentNode->element == theElement)
		return 0;
	currentNode = currentNode->next;
	int index = 1;  // index of currentNode
	while (currentNode != this->firstNode &&
		currentNode->element != theElement)
	{
		// move to next node
		currentNode = currentNode->next;
		++index;
	}

	// make sure we found matching element
	if (currentNode == this->firstNode)
		return -1;
	else
		return index;
}

template<typename T>
void circularList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	this->checkIndex(theIndex);

	// valid index, locate node with element to delete
	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = this->firstNode;
		if (this->firstNode == this->lastNode)
			this->firstNode = this->lastNode = nullptr;
		else
		{
			this->firstNode = this->firstNode->next;
			this->lastNode->next = this->firstNode;
		}
	}
	else
	{  // use p to get to predecessor of desired node
		chainNode<T>* p = this->firstNode;
		for (int i = 0; i < theIndex - 1; ++i)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next; // remove deleteNode from chain
		if (deleteNode == this->lastNode)
			this->lastNode = p;
	}
	--this->listSize;
	delete deleteNode;
}

template<typename T>
void circularList<T>::insert(int theIndex, const T& theElement)
{
	// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > this->listSize)
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << this->listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)
	{// insert at front
		this->firstNode = new chainNode<T>(theElement, this->firstNode);
		if (this->listSize == 0)
			this->lastNode = this->firstNode;
		this->lastNode->next = this->firstNode;
	}
	else
	{  // find predecessor of new element
		chainNode<T>* p = this->firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		// insert after p
		p->next = new chainNode<T>(theElement, p->next);
		if (this->listSize == theIndex)
			this->lastNode = p->next;
	}
	++this->listSize;
}

template<typename T>
void circularList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	chainNode<T>* currentNode = this->firstNode;
	if (currentNode == nullptr)
		return;
	if (currentNode != nullptr)
		out << currentNode->element << " ";
	for (currentNode = currentNode->next;
		currentNode != this->firstNode;
		currentNode = currentNode->next)
		out << currentNode->element << " ";
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const circularList<T>& x)
{
	x.output(out); return out;
}

template<typename T>
void circularList<T>::push_back(const T& theElement)
{
	extendedChain<T>::push_back(theElement);
	this->lastNode->next = this->firstNode;
}

// ex6_33
template<typename T>
bool circularList<T>::operator ==(const circularList<T>& rhs) const
{
	if (this->listSize != rhs.listSize)
		return false;

	chainNode<T>* currentNodeLhs = this->firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != rhs.lastNode)
		if (currentNodeLhs->element != currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return currentNodeLhs->element == currentNodeRhs->element;
}

template<typename T>
bool circularList<T>::operator !=(const circularList<T>& rhs) const
{
	return !(*this == rhs);
}

template<typename T>
bool circularList<T>::operator >=(const circularList<T>& rhs) const
{
	chainNode<T>* currentNodeLhs = this->firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != rhs.lastNode && currentNodeLhs != this->lastNode)
		if (currentNodeLhs->element < currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return currentNodeLhs->element >= currentNodeRhs->element && this->listSize >= rhs.listSize;
}

template<typename T>
bool circularList<T>::operator <=(const circularList<T>& rhs) const
{
	chainNode<T>* currentNodeLhs = this->firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != rhs.lastNode && currentNodeLhs != this->lastNode)
		if (currentNodeLhs->element > currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return currentNodeLhs->element <= currentNodeRhs->element && this->listSize <= rhs.listSize;
}

template<typename T>
bool circularList<T>::operator <(const circularList<T>& rhs) const
{
	return !(*this >= rhs);
}

template<typename T>
bool circularList<T>::operator >(const circularList<T>& rhs) const
{
	return !(*this <= rhs);
}

#endif
