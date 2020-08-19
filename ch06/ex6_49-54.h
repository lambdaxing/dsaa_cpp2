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

	// ex6_51
	void append(doubleCircularList<T>& appendList);
	// ex6_50
	void reverse();
	// ex6_52
	void meld(doubleCircularList<T>& a, doubleCircularList<T>& b);
	// ex6_53
	void merge(doubleCircularList<T>& a, doubleCircularList<T>& b);
	// ex6_54
	void split(doubleCircularList<T>& a, doubleCircularList<T>& b);

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

template<typename T>
void doubleCircularList<T>::append(doubleCircularList<T>& appendList)
{
	if (appendList.empty())
		return;
	if (empty())							// *this is empty list
	{
		firstNode = appendList.firstNode;
		listSize = appendList.listSize;
	}										// *this is not empty
	else
	{
		firstNode->previous->next = appendList.firstNode;
		appendList.firstNode->previous->next = firstNode;
		doubleChainNode<T>* temp = firstNode->previous;
		firstNode->previous = appendList.firstNode->previous;
		appendList.firstNode->previous = temp;
		listSize += appendList.listSize;
	}

	appendList.firstNode = nullptr;
	appendList.listSize = 0;
}

template<typename T>
void doubleCircularList<T>::reverse()
{
	if (firstNode != nullptr)
	{
		using std::swap;
		firstNode->previous->next = nullptr;			// becomme to no-circular
		doubleChainNode<T>* currentNode = firstNode;
		doubleChainNode<T>* nextNode;
		while (currentNode != nullptr)
		{
			nextNode = currentNode->next;
			swap(currentNode->previous, currentNode->next);		// swap
			currentNode = nextNode;
		}
		firstNode->next->previous = firstNode;					// restore
		firstNode = firstNode->next;
	}
}

template<typename T>
void doubleCircularList<T>::meld(doubleCircularList<T>& a, doubleCircularList<T>& b)
{
	if (a.firstNode == nullptr)
	{
		return;		// throw
	}
	else {
		clear();
		a.firstNode->previous->next = nullptr;
		if (b.firstNode != nullptr)
			b.firstNode->previous->next = nullptr;

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
		currentNode->next = firstNode;
		firstNode->previous = currentNode;
		listSize = a.listSize + b.listSize;

		a.firstNode = b.firstNode = nullptr;
		a.listSize = b.listSize = 0;
	}
}

template<typename T>
void doubleCircularList<T>::merge(doubleCircularList<T>& a, doubleCircularList<T>& b)
{
	if (!(std::is_sorted(a.begin(), a.end()) && std::is_sorted(b.begin(), b.end())) || a.empty() || b.empty())
	{
		std::ostringstream s;
		s << "a and b must be sorted and not be empty.";
		throw illegalParameterValue(s.str());
	}

	clear();
	a.firstNode->previous->next = nullptr;
	b.firstNode->previous->next = nullptr;
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
	currentNode->next = firstNode;
	firstNode->previous = currentNode;
	listSize = a.listSize + b.listSize;

	a.firstNode = b.firstNode = nullptr;
	a.listSize = b.listSize = 0;
}

template<typename T>
void doubleCircularList<T>::split(doubleCircularList<T>& a, doubleCircularList<T>& b)
{
	doubleChainNode<T>* currentNode = firstNode;
	if (currentNode == nullptr)						// *this is empty
		return;

	a.clear(); b.clear();
	b.firstNode = currentNode;						// first(0) add to b
	currentNode = currentNode->next;
	if (currentNode == nullptr)						// *this has one node
	{
		b.firstNode->previous = b.firstNode->next = b.firstNode;
		b.listSize = 1;
	}
	else 
	{
		a.firstNode = currentNode;						// second(1) add to a
		currentNode = currentNode->next;
		doubleChainNode<T>* aCurrentNode = a.firstNode;
		doubleChainNode<T>* bCurrentNode = b.firstNode;

		int i, j, k;
		j = k = 1; i = 2;

		while (currentNode != firstNode)
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
		aCurrentNode->next = a.firstNode;
		a.firstNode->previous = aCurrentNode;
		a.listSize = j;
		bCurrentNode->next = b.firstNode;
		b.firstNode->previous = bCurrentNode;
		b.listSize = k;
	}
	firstNode = nullptr;
	listSize = 0;
}

using namespace std;
void testEx6_49()
{
	// create an extended chain
	doubleCircularList<int> y;
	doubleCircularList<int> x;
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
	doubleCircularList<int> z;
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
