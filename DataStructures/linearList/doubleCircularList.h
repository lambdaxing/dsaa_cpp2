// circular doubly linked list without header node

#ifndef DOUBLE_CIRCULAR_LIST
#define DOUBLE_CIRCULAR_LIST

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "doubleChainNode.h"
#include "myExceptions.h"
#include "extendedLinearList.h"

template<typename T>
class doubleCircularList :public extendedLinearList<T>
{
public:
	doubleCircularList(int initialCapacity = 10);
	doubleCircularList(const doubleCircularList<T>& theList);
	~doubleCircularList();

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	void clear();
	void push_back(const T& theElement);

	// iterators to start and end of list. one question: the iterator is not [ begin,end ) , it is [ begin,end ] .
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(firstNode->previous); }

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
	doubleChainNode<T>* firstNode;			// lastNode == firstNode->previous
	int listSize;
};

template<typename T>
doubleCircularList<T>::doubleCircularList(int initialCapacity /* = 10 */)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	firstNode = nullptr;
	listSize = 0;
}

template<typename T>
doubleCircularList<T>::doubleCircularList(const doubleCircularList<T>& theList)
{// Copy constructor.
	listSize = theList.listSize;

	if (listSize == 0)
	{// theList is empty
		firstNode = nullptr;
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
	while (sourceNode != theList.firstNode)
	{// copy remaining elements
		targetNode->next = new doubleChainNode<T>(sourceNode->element, targetNode);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = firstNode;		// end the chain
	firstNode->previous = targetNode;	// begin the chain 
}

template<typename T>
doubleCircularList<T>::~doubleCircularList()
{// Chain destructor. Delete all nodes in chain.
	if (firstNode == nullptr)
		return;
	doubleChainNode<T>* currentNode = firstNode->next;;
	doubleChainNode<T>* nextNode;
	while (currentNode != firstNode)
	{// delete firstNode
		nextNode = currentNode->next;
		delete currentNode;
		currentNode = nextNode;
	}
	delete currentNode;
	currentNode = nullptr;
}

template<typename T>
void doubleCircularList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& doubleCircularList<T>::get(int theIndex) const
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
		p = firstNode->previous;
		for (int i = listSize; i > theIndex - 1; --i)
			p = p->previous;
	}
	return p->element;
}

template<typename T>
int doubleCircularList<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

	if (firstNode == nullptr)
		return -1;
	else
		firstNode->previous->next = nullptr;		// become to no-circular list
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
	firstNode->previous->next = firstNode;			// restore circular
	// make sure we found matching element
	if (currentNode == nullptr)
		return -1;
	else
		return index;
}

template<typename T>
void doubleCircularList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// valid index, locate node with element to delete
	doubleChainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = firstNode;
		if (listSize == 1)
			firstNode = nullptr;
		else
		{
			firstNode->previous->next = firstNode->next;
			firstNode->next->previous = firstNode->previous;
			firstNode = firstNode->next;
		}
	}
	else
	{  // use p to get to predecessor of desired node
		doubleChainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next;
		p->next->previous = p;
	}

	listSize--;
	delete deleteNode;
}

template<typename T>
void doubleCircularList<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)
	{	// insert at front
		if (listSize == 0)	// insert empty
		{
			firstNode = new doubleChainNode<T>(theElement);
			firstNode->next = firstNode->previous = firstNode;
		}
		else
		{
			firstNode = new doubleChainNode<T>(theElement, firstNode->previous, firstNode);
			firstNode->next->previous = firstNode;
			firstNode->previous->next = firstNode;
		}
	}
	else
	{  // find predecessor of new element
		doubleChainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		// insert after p
		p->next = new doubleChainNode<T>(theElement, p, p->next);
		p->next->next->previous = p->next;
	}
	++listSize;
}

template<typename T>
void doubleCircularList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	if (firstNode == nullptr)
		return;
	out << firstNode->element << " ";
	for (doubleChainNode<T>* currentNode = firstNode->next;
		currentNode != firstNode;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const doubleCircularList<T>& x)
{
	x.output(out); return out;
}

template<typename T>
void doubleCircularList<T>::clear()
{
	doubleChainNode<T>* next;
	if (firstNode != nullptr)
		firstNode->previous->next = nullptr;		// become to no-circular list
	while (firstNode != nullptr)
	{
		next = firstNode->next;
		delete firstNode;
		firstNode = next;
	}
	listSize = 0;
}

template<typename T>
void doubleCircularList<T>::push_back(const T& theElement)
{
	insert(0, theElement);
	firstNode = firstNode->next;
}

#endif
