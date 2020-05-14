
#ifndef CIRCULAR_LIST
#define CIRCULAR_LIST

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <numeric>
#include "ex6_17_19_21_23.h"

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

	// ex6_30
	void reverse();
	
	// ex6_33
	bool operator==(const circularList& rhs) const;
	bool operator!=(const circularList& rhs) const;
	bool operator <(const circularList& rhs) const;
	bool operator>=(const circularList& rhs) const;
	bool operator >(const circularList& rhs) const;
	bool operator<=(const circularList& rhs) const;
	// ex6_34
	void merge(circularList<T>& a, circularList<T>& b);
	// ex6_36
	void split(circularList<T>& a, circularList<T>& b);
	// ex6_37
	void del(chainNode<T>*& x);
	void testDel();

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
	if(currentNode != nullptr)
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

template<typename T>
void circularList<T>::reverse()
{
	chainNode<T>* currentNode = this->firstNode;
	chainNode<T>* nextNode;
	chainNode<T>* preNode = this->lastNode;
	while (currentNode->next != this->firstNode)
	{
		nextNode = currentNode->next;
		currentNode->next = preNode;
		preNode = currentNode;
		currentNode = nextNode;
	}
	currentNode->next = preNode;
	this->firstNode = currentNode;
}

// ex6_31
//// the same as reverse(chain<T>&)
//template<typename T>
//void reverse(circularList<T>& theList)
//{
//	using std::swap;
//	for (int i = 0; i < theList.size() / 2; ++i)
//		swap(theList[i],theList[theList.size() - 1 - i]);
//}

// ex6_32
template<typename T>
circularList<T> meld(const circularList<T>& a, const circularList<T>& b)
{
	circularList<T> theList;
	int ai, bi, i;
	ai = bi = i = 0;
	while (ai < a.size() || bi < b.size())
	{
		if (bi < b.size() && i % 2 || ai >= a.size() && bi < b.size())
			theList.push_back(b.get(bi++));
		else
			theList.push_back(a.get(ai++));
		++i;
	}
	return theList;
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

template<typename T>
circularList<T> merge(const circularList<T>& a, const circularList<T>& b)
{
	circularList<T> theList;
	int ai, bi, i;
	ai = bi = i = 0;
	//std::cout << a.size() << " " << b.size() << std::endl;
	while (ai < a.size() || bi < b.size())
	{
		if (bi < b.size() && ai < a.size() && b.get(bi) <= a.get(ai) || ai >= a.size() && bi < b.size())
			theList.push_back(b.get(bi++));
		else
			theList.push_back(a.get(ai++));
		++i;
	}
	return theList;
}

template<typename T>
void circularList<T>::merge(circularList<T>& a,circularList<T>& b)
{
	if (this == &a || this == &b || &a == &b || a.size() == 0 || b.size() == 0)
	{
		std::ostringstream s;
		s << "extendedChain<T>::merge(a,b): a,b must not be this and a must not be b.";
		throw illegalIndex(s.str());
	}

	using std::is_sorted;
	if (!(is_sorted(a.cbegin(), a.cend()) && is_sorted(b.cbegin(), b.cend())))
	{
		std::ostringstream s;
		s << "extendedChain<T>::merge(a,b):a , b must be sorted.";
		throw illegalParameterValue(s.str());
	}

	// a,b become to no-circularList
	a.lastNode->next = nullptr;
	b.lastNode->next = nullptr;
	chainNode<T>* aCurrentNode = a.firstNode;
	chainNode<T>* bCurrentNode = b.firstNode;
	clear();
	chainNode<T>* currentNode = nullptr;
	chainNode<T>* preNode = nullptr;
	bool i = true;
	while (aCurrentNode != nullptr || bCurrentNode != nullptr)
	{
		if (aCurrentNode != nullptr && bCurrentNode == nullptr ||						// a is not over and b is over
			aCurrentNode != nullptr && aCurrentNode->element <= bCurrentNode->element)	// a,b is not over and a <= b
		{
			currentNode = aCurrentNode;
			aCurrentNode = aCurrentNode->next;
		}
		else                                                                        // a is over and b is not over
		{																			// or a,b is not over and b < a
			currentNode = bCurrentNode;
			bCurrentNode = bCurrentNode->next;
		}

		if (i)
		{
			this->firstNode = currentNode;
			i = false;
		}
		else
			preNode->next = currentNode;
		preNode = currentNode;
		currentNode = currentNode->next;
	}
	
	this->lastNode = preNode;
	this->lastNode->next = this->firstNode;
	this->listSize = a.listSize + b.listSize;
	a.firstNode = a.lastNode = nullptr;
	a.listSize = 0;
	b.firstNode = b.lastNode = nullptr;
	b.listSize = 0;
}

// ex6_35
template<typename T>
void split(circularList<T>& a, circularList<T>& b, circularList<T>& c)
{
	a.clear(); b.clear();
	int i = 0;
	for (i = 0; i < c.size(); ++i)
		if (i % 2) a.push_back(c[i]);
		else b.push_back(c[i]);
}

template<typename T>
void circularList<T>::split(circularList<T>& a, circularList<T>& b)
{
	if (this->listSize == 0)
	{
		return;		// throw
	}
	a.clear(); b.clear();
	chainNode<T>* currentNode = this->firstNode;
	chainNode<T>* aCurrentNode = a.firstNode;
	chainNode<T>* aPreCurrentNode = nullptr;
	chainNode<T>* bCurrentNode = b.firstNode;
	chainNode<T>* bPreCurrentNode = nullptr;
	int i = 0;
	this->lastNode->next = nullptr;				// to no-circularList
	while (currentNode != nullptr)
	{
		if (i % 2)
		{
			aCurrentNode = currentNode;
			if (i == 1)
				a.firstNode = aCurrentNode;
			else
				aPreCurrentNode->next = aCurrentNode;
			aPreCurrentNode = aCurrentNode;
			aCurrentNode = aCurrentNode->next;
		}
		else
		{
			bCurrentNode = currentNode;
			if (i == 0)
				b.firstNode = bCurrentNode;
			else
				bPreCurrentNode->next = bCurrentNode;
			bPreCurrentNode = bCurrentNode;
			bCurrentNode = bCurrentNode->next;
		}
		currentNode = currentNode->next;
		++i;
	}
	//if (bPreCurrentNode != nullptr && bPreCurrentNode->next != nullptr)
	//	bPreCurrentNode->next = nullptr;
	//if (aPreCurrentNode != nullptr && aPreCurrentNode->next != nullptr)
	//	aPreCurrentNode->next = nullptr;

	if (aPreCurrentNode != nullptr)
	{
		a.lastNode = aPreCurrentNode;
		a.lastNode->next = a.firstNode;
	}

	if (bPreCurrentNode != nullptr)
	{
		b.lastNode = bPreCurrentNode;
		b.lastNode->next = b.firstNode;
	}

	a.listSize = i / 2;
	b.listSize = (i + 1) / 2;
	this->listSize = 0;
	this->firstNode = this->lastNode = nullptr;
}

template<typename T>
void circularList<T>::del(chainNode<T>*& x)
{
	if (x == this->lastNode)			// delete lastNode
		this->firstNode = this->lastNode;
	if (x->next == this->lastNode)
		this->lastNode = x;

	x->element = x->next->element;
	chainNode<T>* t = x->next->next;
	delete x->next;
	x->next = t;

	while (this->lastNode->next != this->firstNode) this->lastNode = this->lastNode->next;		// relocation lastNode
}

template<typename T>
void circularList<T>::testDel()
{
	del(this->firstNode); del(this->lastNode);
}

using namespace std;

void testEx6_29()
{
	// create an extended chain
	circularList<int> y;
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;

	// test iterator
	cout << "Output using forward iterators pre and post ++" << endl;
	for (circularList<int>::iterator i = y.begin();
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;
	for (circularList<int>::iterator i = y.begin();
		i != y.end(); ++i)
	{
		cout << *i << "  ";
		*i += 1;
	}
	cout << endl;

	cout << "Incremented by 1 list is " << y << endl;

	// try out an STL algorithm
	int sum = accumulate(y.begin(), y.end(), 0);
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
	y.push_back(1);
	y.push_back(2);
	y.push_back(3);
	cout << y << endl;

	// test reverse
	y.reverse();
	cout << "y.reverse(): " << y << endl;
	reverse(y);
	cout << " reverse(y): " << y << endl;

	// test meld 
	circularList<int> x;
	x.push_back(0);
	x.push_back(1);
	x.push_back(2);
	x.push_back(3);
	x.push_back(4);
	cout << "x: " << x << endl;
	circularList<int> z = meld(x, y);
	cout << "z: " << z << endl;

	// test merge
	z.erase(8);
	z.erase(8);
	z.erase(8);
	z.erase(8);
	circularList<int> m = merge(x, z);
	cout << "m: " << m << endl;
	m.merge(x, z);
	cout << "m: " << m << endl;
	cout << "x: " << x << endl;
	cout << "z: " << z << endl;

	// test split
	split(x, z, m);
	cout << "m: " << m << endl;
	cout << "x: " << x << endl;
	cout << "z: " << z << endl;
	m.split(x, z);
	cout << "m: " << m << endl;
	cout << "x: " << x << endl;
	cout << "z: " << z << endl;
	
	// test del
	x.testDel();
	z.testDel();
	cout << "x: " << x << endl;
	cout << "z: " << z << endl;

}

#endif
