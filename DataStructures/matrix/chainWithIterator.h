// linked implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for chain included

#ifndef chain_
#define chain_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "linearList.h"
#include "chainNode.h"
#include "myExceptions.h"

class linkedDigraph;
template <typename T> class linkedWDigraph;
template<class T>
class chain : public linearList<T>
{
	friend linkedDigraph;
	friend linkedWDigraph<int>;
	friend linkedWDigraph<float>;
	friend linkedWDigraph<double>;
public:
	// constructor, copy constructor and destructor
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();
	chain& operator=(const chain& rhs);

	// ADT methods
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	void clear()
	{// Delete all nodes in chain.
		while (firstNode != nullptr)
		{// delete firstNode
			chainNode<T>* nextNode = firstNode->next;
			delete firstNode;
			firstNode = nextNode;
		}
		this->listSize = 0;
	}

	// ex6_3
	void set(int theIndex, const T& theElement);
	T& operator[](int i);
	// ex6_7
	bool operator==(const chain& rhs) const;
	// ex6_8
	bool operator!=(const chain& rhs) const;
	// ex6_9
	bool operator <(const chain& rhs) const;
	bool operator>=(const chain& rhs) const;
	bool operator >(const chain& rhs) const;
	bool operator<=(const chain& rhs) const;

	// iterators to start and end of list
	class iterator;
	iterator begin() { return iterator(firstNode); }
	const iterator cbegin() const { return iterator(firstNode); }
	iterator end() { return iterator(nullptr); }
	const iterator cend() const { return iterator(nullptr); }

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
		iterator& operator++() // preincrement
		{
			node = node->next; return *this;
		}
		iterator operator++(int)// postincrement
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		// increment
		iterator& operator++() const // preincrement
		{
			node = node->next; return *this;
		}
		iterator operator++(int) const // postincrement
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
	chainNode<T>* firstNode;  // pointer to first node in chain
	int listSize;             // number of elements in list
};

template<typename T>
chain<T>& chain<T>::operator=(const chain<T>& rhs)
{
	if (this != &rhs)
	{
		clear();
		listSize = rhs.listSize;

		if (listSize == 0)
		{// theList is empty
			firstNode = nullptr;
			return;
		}
		// non-empty list
		chainNode<T>* sourceNode = rhs.firstNode;
		// node in theList to copy from
		firstNode = new chainNode<T>(sourceNode->element);
		// copy first element of theList
		sourceNode = sourceNode->next;
		chainNode<T>* targetNode = firstNode;
		// current last node in *this
		while (sourceNode != nullptr)
		{// copy remaining elements
			targetNode->next = new chainNode<T>(sourceNode->element);
			targetNode = targetNode->next;
			sourceNode = sourceNode->next;
		}
		targetNode->next = nullptr; // end the chain
	}
}

template<typename T>
chain<T>::chain(int initialCapacity)
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
chain<T>::chain(const chain<T>& theList)
{// Copy constructor.
	listSize = theList.listSize;

	if (listSize == 0)
	{// theList is empty
		firstNode = nullptr;
		return;
	}

	// non-empty list
	chainNode<T>* sourceNode = theList.firstNode;
	// node in theList to copy from
	firstNode = new chainNode<T>(sourceNode->element);
	// copy first element of theList
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
	// current last node in *this
	while (sourceNode != nullptr)
	{// copy remaining elements
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = nullptr; // end the chain
}

template<typename T>
chain<T>::~chain()
{// Chain destructor. Delete all nodes in chain.
	chainNode<T>* nextNode;
	while (firstNode != nullptr)
	{// delete firstNode
		nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<typename T>
void chain<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& chain<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// move to desired node
	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
		currentNode = currentNode->next;

	return currentNode->element;
}

template<typename T>
int chain<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search the chain for theElement
	chainNode<T>* currentNode = firstNode;
	int index = 0;  // index of currentNode
	while (currentNode != nullptr &&
		currentNode->element != theElement)
	{
		// move to next node
		currentNode = currentNode->next;
		++index;
	}

	// make sure we found matching element
	if (currentNode == nullptr)
		return -1;
	else
		return index;
}

template<typename T>
void chain<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// valid index, locate node with element to delete
	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{  // use p to get to predecessor of desired node
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next; // remove deleteNode from chain
	}
	--listSize;
	delete deleteNode;
}

template<typename T>
void chain<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)
		// insert at front
		firstNode = new chainNode<T>(theElement, firstNode);
	else
	{  // find predecessor of new element
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		// insert after p
		p->next = new chainNode<T>(theElement, p->next);
	}
	++listSize;
}

template<typename T>
void chain<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	for (chainNode<T>* currentNode = firstNode;
		currentNode != nullptr;
		currentNode = currentNode->next)
		out << currentNode->element << " ";
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x)
{
	x.output(out); return out;
}

template<typename T>
void chain<T>::set(int theIndex, const  T& theElement)
{
	checkIndex(theIndex);

	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; ++i)
		currentNode = currentNode->next;
	currentNode->element = theElement;
}

template<typename T>
T& chain<T>::operator[](int i)
{
	checkIndex(i);
	chainNode<T>* currentNode = firstNode;
	while (i--)
		currentNode = currentNode->next;
	return currentNode->element;
}

template<typename T>
bool chain<T>::operator ==(const chain<T>& rhs) const
{
	if (listSize != rhs.listSize)
		return false;

	chainNode<T>* currentNodeLhs = firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != nullptr)
		if (currentNodeLhs->element != currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return true;
}

template<typename T>
bool chain<T>::operator !=(const chain<T>& rhs) const
{
	return !(*this == rhs);
}

template<typename T>
bool chain<T>::operator >=(const chain<T>& rhs) const
{
	chainNode<T>* currentNodeLhs = firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != nullptr && currentNodeLhs != nullptr)
		if (currentNodeLhs->element < currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return currentNodeRhs == nullptr;
}

template<typename T>
bool chain<T>::operator <=(const chain<T>& rhs) const
{
	chainNode<T>* currentNodeLhs = firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != nullptr && currentNodeLhs != nullptr)
		if (currentNodeLhs->element > currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return currentNodeLhs == nullptr;
}

template<typename T>
bool chain<T>::operator <(const chain<T>& rhs) const
{
	return !(*this >= rhs);
}

template<typename T>
bool chain<T>::operator >(const chain<T>& rhs) const
{
	return !(*this <= rhs);
}

#endif