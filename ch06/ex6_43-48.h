//

#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "doubleChainNode.h"
#include "myExceptions.h"
#include "extendedLinearList.h"

template<typename T>
class doubleLinkedList :public move<T>
{
public:
	doubleLinkedList(int initialCapacity = 10);
	doubleLinkedList(const doubleLinkedList<T>& theList);
	~doubleLinkedList();

	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	void clear();
	void push_back(const T& theElement);

	// ex6_44
	void append(doubleLinkedList<T>& appendList);
	// ex6_45
	void reverse();
	// ex6_46
	void meld(doubleLinkedList<T>& a, doubleLinkedList<T>& b);
	// ex6_47
	void merge(doubleLinkedList<T>& a, doubleLinkedList<T>& b);
	// ex6_48
	void split(doubleLinkedList<T>& a, doubleLinkedList<T>& b);

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
doubleLinkedList<T>::doubleLinkedList(int initialCapacity /* = 10 */)
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
doubleLinkedList<T>::doubleLinkedList(const doubleLinkedList<T>& theList)
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
		targetNode->next = new doubleChainNode<T>(sourceNode->element,targetNode);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = nullptr; // end the chain
}

template<typename T>
doubleLinkedList<T>::~doubleLinkedList()
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
void doubleLinkedList<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& doubleLinkedList<T>::get(int theIndex) const
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
int doubleLinkedList<T>::indexOf(const T& theElement) const
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
void doubleLinkedList<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// valid index, locate node with element to delete
	doubleChainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = firstNode;
		firstNode = firstNode->next;
		if(listSize !=  1) firstNode->previous = nullptr;
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
void doubleLinkedList<T>::insert(int theIndex, const T& theElement)
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
void doubleLinkedList<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	for (doubleChainNode<T>* currentNode = firstNode;
		currentNode != nullptr;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const doubleLinkedList<T>& x)
{
	x.output(out); return out;
}

template<typename T>
void doubleLinkedList<T>::clear()
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
void doubleLinkedList<T>::push_back(const T& theElement)
{
	lastNode = new doubleChainNode<T>(theElement, lastNode, nullptr);
	if (lastNode->previous == nullptr)			// push empty list (lastNode = nullptr)
		firstNode = lastNode;
	else
		lastNode->previous->next = lastNode;	// push not-empty list
	++listSize;
}

template<typename T>
void doubleLinkedList<T>::append(doubleLinkedList<T>& appendList)
{
	if (appendList.empty())
		return;
	if (empty())							// *this is empty list
	{
		firstNode = appendList.firstNode;
		lastNode = appendList.lastNode;
		listSize = appendList.listSize;
	}										// *this is not empty
	else
	{
		lastNode->next = appendList.firstNode;
		lastNode->next->previous = lastNode;
		lastNode = appendList.lastNode;
		listSize += appendList.listSize;
	}

	appendList.lastNode = appendList.firstNode = nullptr;
	appendList.listSize = 0;
}

template<typename T>
void doubleLinkedList<T>::reverse()
{
	doubleChainNode<T>* currentNode = firstNode;
	doubleChainNode<T>* temp;

	while (currentNode != nullptr)
	{
		temp = currentNode->next;
		currentNode->next = currentNode->previous;
		currentNode->previous = temp;
		currentNode = temp;
	}

	temp = firstNode;
	firstNode = lastNode;
	lastNode = temp;
}

template<typename T>
void doubleLinkedList<T>::meld(doubleLinkedList<T>& a, doubleLinkedList<T>& b)
{
	clear();
	firstNode = a.firstNode;
	doubleChainNode<T>* currentNode = firstNode;
	doubleChainNode<T>* aCurrentNode = a.firstNode->next;
	doubleChainNode<T>* bCurrentNode = b.firstNode;
	int i = 1;
	while (aCurrentNode != nullptr || bCurrentNode != nullptr)
	{
		if (bCurrentNode != nullptr && i % 2 || bCurrentNode != nullptr && aCurrentNode == nullptr)
		{
			currentNode->next = bCurrentNode;
			bCurrentNode = bCurrentNode->next;
		}
		else
		{
			currentNode->next = aCurrentNode;
			aCurrentNode = aCurrentNode->next;
		}
		currentNode->next->previous = currentNode;
		currentNode = currentNode->next;
		++i;
	}
	lastNode = currentNode;
	lastNode->next = nullptr;
	listSize = a.listSize + b.listSize;

	a.lastNode = a.firstNode = nullptr;
	a.listSize = 0;

	b.lastNode = b.firstNode = nullptr;
	b.listSize = 0;
}

template<typename T>
void doubleLinkedList<T>::merge(doubleLinkedList<T>& a, doubleLinkedList<T>& b)
{
	if (!(std::is_sorted(a.begin(), a.end()) && std::is_sorted(b.begin(), b.end())) || a.empty() || b.empty())
	{
		std::ostringstream s;
		s << "a and b must be sorted and not be empty.";
		throw illegalParameterValue(s.str());
	}

	clear();
	doubleChainNode<T>* aCurrentNode = a.firstNode;
	doubleChainNode<T>* bCurrentNode = b.firstNode;
	if (aCurrentNode->element <= bCurrentNode->element)
	{
		firstNode = aCurrentNode;
		aCurrentNode = aCurrentNode->next;
	}
	else
	{
		firstNode = bCurrentNode;
		bCurrentNode = bCurrentNode->next;
	}
	doubleChainNode<T>* currentNode = firstNode;

	while (aCurrentNode != nullptr || bCurrentNode != nullptr)
	{
		if (bCurrentNode != nullptr && aCurrentNode != nullptr && bCurrentNode->element <= aCurrentNode->element
			|| bCurrentNode != nullptr && aCurrentNode == nullptr)
		{
			currentNode->next = bCurrentNode;
			bCurrentNode = bCurrentNode->next;
		}
		else
		{
			currentNode->next = aCurrentNode;
			aCurrentNode = aCurrentNode->next;
		}
		currentNode->next->previous = currentNode;
		currentNode = currentNode->next;
	}
	lastNode = currentNode;
	lastNode->next = nullptr;
	listSize = a.listSize + b.listSize;

	a.lastNode = a.firstNode = nullptr;
	a.listSize = 0;

	b.lastNode = b.firstNode = nullptr;
	b.listSize = 0;
}

template<typename T>
void doubleLinkedList<T>::split(doubleLinkedList<T>& a, doubleLinkedList<T>& b)
{
	doubleChainNode<T>* currentNode = firstNode;
	if (currentNode == nullptr)						// *this is empty
		return;

	a.clear(); b.clear();
	b.firstNode = currentNode;						// first(0) add to b
	currentNode = currentNode->next;
	if (currentNode == nullptr)						// *this has one node
	{
		b.lastNode = b.firstNode;
		b.listSize = 1;
		return;
	}
	a.firstNode = currentNode;						// second(1) add to a
	a.firstNode->previous = nullptr;

	currentNode = currentNode->next;
	doubleChainNode<T>* aCurrentNode = a.firstNode;
	doubleChainNode<T>* bCurrentNode = b.firstNode;

	int i, j, k;
	j = k = 1; i = 2;

	while (currentNode != nullptr)
	{
		if (i % 2)
		{
			aCurrentNode->next = currentNode;
			aCurrentNode->next->previous = aCurrentNode;
			aCurrentNode = aCurrentNode->next;
			++j;
		}
		else
		{
			bCurrentNode->next = currentNode;
			bCurrentNode->next->previous = bCurrentNode;
			bCurrentNode = bCurrentNode->next;
			++k;
		}
		currentNode = currentNode->next;
		++i;
	}
	a.lastNode = aCurrentNode;
	a.lastNode->next = nullptr;
	a.listSize = j;
	b.lastNode = bCurrentNode;
	b.lastNode->next = nullptr;
	b.listSize = k;

	lastNode = firstNode = nullptr;
	listSize = 0;
}

using namespace std;
void testEx6_43()
{
	// create an extended chain
	doubleLinkedList<int> y;
	doubleLinkedList<int> x;
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;

	// test iterator
	cout << "Ouput using forward iterators pre and post ++" << endl;
	for (auto i = y.begin();
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;
	for (auto i = y.begin();
		i != y.end(); ++i)
	{
		cout << *i << "  ";
		*i += 1;
	}
	cout << endl;

	cout << "Incremented by 1 list is " << y << endl;

	// try out an STL algorithm
	int sum = std::accumulate(y.begin(), y.end(), 0);
	cout << "The sum of the elements is " << sum << endl;

	// clear the chain and do a few appends
	y.clear();
	y.push_back(1);
	y.push_back(2);
	y.push_back(3);
	cout << "Appended 3 integers, list y should be 1 2 3" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;

	y.insert(3, 4);
	y.insert(0, 0);
	cout << "List y should be 0 1 2 3 4" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;

	y.erase(4);
	y.erase(0);
	y.push_back(6);
	cout << "List y should be 1 2 3 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;

	// test reverse
	y.reverse();
	cout << "y.reverse(): " << y << endl;
	x.push_back(0);
	cout << "x: " << x << endl;
	x.reverse();
	cout << "x.reverse(): " << x << endl;

	// test meld
	doubleLinkedList<int> z;
	z.meld(x, y);
	cout << "z.meld(x,y): " << z << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;

	// test merge
	for (int i = 0; i < 6; ++i)
	{
		x.push_back(i);
		y.push_back(i + 6);
	}
	cout << "test merge" << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;
	z.merge(x, y);
	cout << "z.merge(x,y): " << z << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;

	// test split
	z.split(x, y);
	cout << "z.split(x,y): " << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;


	// test append
	x.append(y);
	cout << "x.append(y): " << x << endl;
	cout << "y: " << y << endl;
}

#endif