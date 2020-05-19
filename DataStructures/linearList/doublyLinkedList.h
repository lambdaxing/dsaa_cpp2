// doubly linked list

#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "doubleChainNode.h"
#include "myExceptions.h"
#include "extendedLinearList.h"

template<typename T>
class doublyLinkedList :public extendedLinearList<T>
{
public:
	doublyLinkedList(int initialCapacity = 10);
	doublyLinkedList(const doublyLinkedList<T>& theList);
	~doublyLinkedList();

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
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(nullptr); }

	// iterator for chain
	class iterator
	{
	public:
		// typedefs required by C++ for a bidirectional iterator
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		// constructor
		iterator(doubleChainNode<T>* theNode = nullptr)
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

		// decrease
		iterator& operator--()   // preincrement
		{
			node = node->previous; return *this;
		}
		iterator operator--(int) // postincrement
		{
			iterator old = *this;
			node = node->previous;
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
		doubleChainNode<T>* node;
	};  // end of iterator class

protected:
	void checkIndex(int theIndex) const;
	doubleChainNode<T>* firstNode;
	doubleChainNode<T>* lastNode;
	int listSize;
};

template<typename T>
doublyLinkedList<T>::doublyLinkedList(int initialCapacity /* = 10 */)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	firstNode = lastNode = nullptr;
	listSize = 0;
}

template<typename T>
doublyLinkedList<T>::doublyLinkedList(const doublyLinkedList<T>& theList)
{// Copy constructor.
	listSize = theList.listSize;

	if (listSize == 0)
	{// theList is empty
		firstNode = lastNode = nullptr;
		return;
	}

	// non-empty list
	doubleChainNode<T>* sourceNode = theList.firstNode;
	// node in theList to copy from
	firstNode = new doubleChainNode<T>(sourceNode->element);
	// copy first element of theList
	sourceNode = sourceNode->next;
	doubleChainNode<T>* targetNode = firstNode;
	// current last node in *this
	while (sourceNode != nullptr)
	{// copy remaining elements
		targetNode->next = new doubleChainNode<T>(sourceNode->element, targetNode);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = nullptr; // end the chain
}

template<typename T>
doublyLinkedList<T>::~doublyLinkedList()
{// Chain destructor. Delete all nodes in chain.
	doubleChainNode<T>* nextNode;
	while (firstNode != nullptr)
	{// delete firstNode
		nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
	lastNode = firstNode = nullptr;
}

template<typename T>
void doublyLinkedList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& doublyLinkedList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	doubleChainNode<T>* p;
	if (theIndex < listSize / 2)
	{
		p = firstNode;
		for (int i = 0; i < theIndex; ++i)
			p = p->next;
	}
	else
	{
		p = lastNode;
		for (int i = listSize; i > theIndex - 1; --i)
			p = p->previous;
	}
	return p->element;
}

template<typename T>
int doublyLinkedList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search the chain for theElement
	doubleChainNode<T>* currentNode = firstNode;
	int index = 0;  // index of currentNode
	while (currentNode != nullptr &&
		currentNode->element != theElement)
	{
		// move to next node
		currentNode = currentNode->next;
		index++;
	}

	// make sure we found matching element
	if (currentNode == nullptr)
		return -1;
	else
		return index;
}

template<typename T>
void doublyLinkedList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// valid index, locate node with element to delete
	doubleChainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = firstNode;
		firstNode = firstNode->next;
		if (listSize != 1) firstNode->previous = nullptr;
		else lastNode = firstNode;							// = nullptr, remove lastNode
	}
	else
	{  // use p to get to predecessor of desired node
		doubleChainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next;			// remove deleteNode from chain
		if (p->next != nullptr)
			p->next->previous = p;			// remove not lastNode
		else
			lastNode = p;					// remove lastNode
	}

	listSize--;
	delete deleteNode;
}

template<typename T>
void doublyLinkedList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)
	{	// insert at front
		firstNode = new doubleChainNode<T>(theElement, nullptr, firstNode);
		if (firstNode->next != nullptr)
			firstNode->next->previous = firstNode;
		else                                               // insert empty list
			lastNode = firstNode;
	}
	else
	{  // find predecessor of new element
		doubleChainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		// insert after p
		p->next = new doubleChainNode<T>(theElement, p, p->next);
		if (p == lastNode)								 // the index of insert is listSize
			lastNode = p->next;
	}
	++listSize;
}

template<typename T>
void doublyLinkedList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	for (doubleChainNode<T>* currentNode = firstNode;
		currentNode != nullptr;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const doublyLinkedList<T>& x)
{
	x.output(out); return out;
}

template<typename T>
void doublyLinkedList<T>::clear()
{
	doubleChainNode<T>* next;
	while (firstNode != nullptr)
	{
		next = firstNode->next;
		delete firstNode;
		firstNode = next;
	}
	lastNode = nullptr;
	listSize = 0;
}

template<typename T>
void doublyLinkedList<T>::push_back(const T& theElement)
{
	lastNode = new doubleChainNode<T>(theElement, lastNode, nullptr);
	if (lastNode->previous == nullptr)			// push empty list (lastNode = nullptr)
		firstNode = lastNode;
	else
		lastNode->previous->next = lastNode;	// push not-empty list
	++listSize;
}

#endif