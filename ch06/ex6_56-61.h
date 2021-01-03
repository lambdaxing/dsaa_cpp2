// circular doubly linked list with header node

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

	// ex6_57
	void append(doubleCircularWithHeader<T>& appendList);
	// ex6_56
	void reverse();
	// ex6_58
	void meld(doubleCircularWithHeader<T>& a, doubleCircularWithHeader<T>& b);
	// ex6_59
	void merge(doubleCircularWithHeader<T>& a, doubleCircularWithHeader<T>& b);
	// ex6_60
	void split(doubleCircularWithHeader<T>& a, doubleCircularWithHeader<T>& b);

	class iterator;
	iterator begin() { return iterator(header->next); }
	iterator end() { return iterator(header); }
	const iterator cbegin() const { return iterator(header->next); }
	const iterator cend() const { return iterator(header); }

	// ex6_61
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

template<typename T>
void doubleCircularWithHeader<T>::append(doubleCircularWithHeader<T>& appendList)
{
	if (appendList.empty())
		return;
	if (empty())							// *this is empty list
	{
		header = appendList.header;
		listSize = appendList.listSize;
	}										// *this is not empty
	else
	{
		header->previous->next = appendList.header->next;
		appendList.header->previous->next = header;
		doubleChainNode<T>* temp = header->previous;
		header->previous = appendList.header->previous;
		appendList.header->next->previous = temp;
		listSize += appendList.listSize;
	}

	appendList.header = new doubleChainNode<T>();
	appendList.header->previous = appendList.header->next = appendList.header;
	appendList.listSize = 0;
}

template<typename T>
void doubleCircularWithHeader<T>::reverse()
{
	using std::swap;
	doubleChainNode<T>* currentNode = header->next;
	doubleChainNode<T>* nextNode;
	while (currentNode != header)
	{
		nextNode = currentNode->next;
		swap(currentNode->previous, currentNode->next);		// swap
		currentNode = nextNode;
	}
	swap(header->previous, header->next);
}

template<typename T>
void doubleCircularWithHeader<T>::meld(doubleCircularWithHeader<T>& a, doubleCircularWithHeader<T>& b)
{
	clear();
	doubleChainNode<T>* currentNode = header;
	doubleChainNode<T>* aCurrentNode = a.header->next;
	doubleChainNode<T>* bCurrentNode = b.header->next;
	int i = 0;
	while (aCurrentNode != a.header || bCurrentNode != b.header)
	{
		if (bCurrentNode != b.header && i % 2 || bCurrentNode != b.header && aCurrentNode == a.header)
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
	currentNode->next = header;
	header->previous = currentNode;
	listSize = a.listSize + b.listSize;

	a.header->next = a.header->previous = a.header;
	a.listSize = 0;

	b.header->next = b.header->previous = b.header;
	b.listSize = 0;
}

template<typename T>
void doubleCircularWithHeader<T>::merge(doubleCircularWithHeader<T>& a, doubleCircularWithHeader<T>& b)
{
	if (!(std::is_sorted(a.begin(), a.end()) && std::is_sorted(b.begin(), b.end())))
	{
		std::ostringstream s;
		s << "a and b must be sorted.";
		throw illegalParameterValue(s.str());
	}

	clear();
	doubleChainNode<T>* currentNode = header;
	doubleChainNode<T>* aCurrentNode = a.header->next;
	doubleChainNode<T>* bCurrentNode = b.header->next;

	while (aCurrentNode != a.header || bCurrentNode != b.header)
	{
		if (bCurrentNode != b.header && aCurrentNode != a.header && bCurrentNode->element <= aCurrentNode->element
			|| bCurrentNode != b.header && aCurrentNode == a.header)
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

	currentNode->next = header;
	header->previous = currentNode;
	listSize = a.listSize + b.listSize;

	a.header->next = a.header->previous = a.header;
	a.listSize = 0;

	b.header->next = b.header->previous = b.header;
	b.listSize = 0;
}

template<typename T>
void doubleCircularWithHeader<T>::split(doubleCircularWithHeader<T>& a, doubleCircularWithHeader<T>& b)
{
	doubleChainNode<T>* currentNode = header->next;
	a.clear(); b.clear();
	doubleChainNode<T>* aCurrentNode = a.header;
	doubleChainNode<T>* bCurrentNode = b.header;
	int i, j, k;
	i = j = k = 0;
	while (currentNode != header)
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
	aCurrentNode->next = a.header;
	a.header->previous = aCurrentNode;
	a.listSize = j;
	bCurrentNode->next = b.header;
	b.header->previous = bCurrentNode;
	b.listSize = k;

	header->previous = header->next = header;
	listSize = 0;
}

using namespace std;
void testEx6_56()
{
	// create an extended chain
	doubleCircularWithHeader<int> y;
	doubleCircularWithHeader<int> x;
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
	doubleCircularWithHeader<int> z;
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

	// again

	// test reverse
	y.reverse();
	cout << "y.reverse(): " << y << endl;
	x.push_back(0);
	cout << "x: " << x << endl;
	x.reverse();
	cout << "x.reverse(): " << x << endl;

	// test meld
	z.meld(x, y);
	cout << "z.meld(x,y): " << z << endl;
	cout << "x: " << x << endl;
	cout << "y: " << y << endl;

	for (int i = 0; i < 6; ++i)
	{
		x.push_back(i);
		y.push_back(i + 6);
	}
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