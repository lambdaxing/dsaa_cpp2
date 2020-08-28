// linked implementation of an extended linear list
// derives from abstract class extendedLinearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for extendedChain included

#ifndef extendedChain_
#define extendedChain_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "extendedLinearList.h"
#include "ex6_2-16_18_20_22_26_27_64_65.h"					// chain<T>
#include "myExceptions.h"

template<typename T>
class extendedChain : public extendedLinearList<T>, public chain<T>
{
public:
	// constructor and copy constructor
	extendedChain(int initialCapacity = 10) :
		chain<T>(initialCapacity),lastNode(nullptr){}
	extendedChain(const extendedChain<T>& c) :
		chain<T>(c) 
	{
		lastNode = this->firstNode;
		while (lastNode != nullptr && lastNode->next != nullptr) lastNode = lastNode->next;
	}

	// ADT methods
	bool empty() const { return this->listSize == 0; }
	int size() const { return this->listSize; }
	T& get(int theIndex) const
	{
		return chain<T>::get(theIndex);
	}
	int indexOf(const T& theElement) const
	{
		return chain<T>::indexOf(theElement);
	}
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void clear()
	{// Delete all nodes in chain.
		while (this->firstNode != nullptr)
		{// delete firstNode
			chainNode<T>* nextNode = this->firstNode->next;
			delete this->firstNode;
			this->firstNode = nextNode;
		}
		this->listSize = 0;
	}
	void push_back(const T& theElement);
	void output(std::ostream& out) const
	{
		chain<T>::output(out);
	}

	// additional method
	void zero()
	{
		this->firstNode = nullptr; this->listSize = 0;
	}

	// ex6_19
	void merge(const extendedChain& a, const extendedChain& b);
	// ex6_20
	void mergeBeEmpty(extendedChain& a, extendedChain& b);
	// ex6_23
	void circularShift(int i);
	//// operators
	//bool operator<=(const extendedChain& rhs) const;
	//bool operator>=(const extendedChain& rhs) const;
	//bool operator <(const extendedChain& rhs) const;
	//bool operator >(const extendedChain& rhs) const;
	//bool operator==(const extendedChain& rhs) const;
	//bool operator!=(const extendedChain& rhs) const;

protected:
	chainNode<T>* lastNode;  // pointer to last node in chain
};


template<typename T>
void extendedChain<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	this->checkIndex(theIndex);

	// valid index, locate node with element to delete
	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = this->firstNode;
		this->firstNode = this->firstNode->next;
	}
	else
	{  // use p to get to predecessor of desired node
		chainNode<T>* p = this->firstNode;
		for (int i = 0; i < theIndex - 1; ++i)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next; // remove deleteNode from chain
		if (deleteNode == lastNode)
			lastNode = p;
	}
	--this->listSize;
	delete deleteNode;
}

template<typename T>
void extendedChain<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
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
			lastNode = this->firstNode;
	}
	else
	{  // find predecessor of new element
		chainNode<T>* p = this->firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		// insert after p
		p->next = new chainNode<T>(theElement, p->next);
		if (this->listSize == theIndex)
			lastNode = p->next;
	}
	++this->listSize;
}

template<typename T>
void extendedChain<T>::push_back(const T& theElement)
{// Insert theElement at the end of the chain.
	chainNode<T>* newNode = new chainNode<T>(theElement, nullptr);
	if (this->firstNode == nullptr)
		// chain is empty
		this->firstNode = lastNode = newNode;
	else
	{  // attach next to lastNode
		lastNode->next = newNode;
		lastNode = newNode;
	}
	++this->listSize;
}

// ex6_17
template<typename T>
extendedChain<T> meld(const extendedChain<T>& a, const extendedChain<T>& b)
{
	extendedChain<T> extendedList;
	auto aCurrentNode = a.cbegin();
	auto bCurrentNode = b.cbegin();
	int i = 0;
	while (aCurrentNode != a.cend() || bCurrentNode != b.cend())
	{
		if (bCurrentNode != b.cend() && i % 2 || aCurrentNode == a.cend() && bCurrentNode != b.cend())
			extendedList.push_back (*bCurrentNode++);
		else
			extendedList.push_back(*aCurrentNode++);
		++i;
	}
	//std::cout << extendedList << std::endl;
	return extendedList;
}

template<typename T>
void extendedChain<T>::merge(const extendedChain& a, const extendedChain& b)
{
	if (this == &a || this == &b || &a == &b)
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

	chainNode<T>* aCurrentNode = a.firstNode;
	chainNode<T>* bCurrentNode = b.firstNode;
	clear();
	while (aCurrentNode != nullptr || bCurrentNode != nullptr)
	{
		if (aCurrentNode != nullptr && bCurrentNode == nullptr ||						// a is not over and b is over
			aCurrentNode != nullptr && aCurrentNode->element <= bCurrentNode->element)	// a,b is not over and a <= b
		{
			push_back(aCurrentNode->element);
			aCurrentNode = aCurrentNode->next;
		}
		else                                                                        // a is over and b is not over
		{																			// or a,b is not over and b < a
			push_back(bCurrentNode->element);										
			bCurrentNode = bCurrentNode->next;
		}
	}
}

template<typename T>
void extendedChain<T>::mergeBeEmpty(extendedChain& a,extendedChain& b)
{
	if (this == &a || this == &b || &a == &b)
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
		}else
			preNode->next = currentNode;
		preNode = currentNode;
		currentNode = currentNode->next;
	}

	this->listSize = a.listSize + b.listSize;
	a.firstNode = nullptr;
	a.listSize = 0;
	b.firstNode = nullptr;
	b.listSize = 0;
}

// ex6_21
template<typename T>
void split(extendedChain<T>& a, extendedChain<T>& b, extendedChain<T>& c)
{
	a.clear();b.clear();
	int i = 0;
	for (i = 0; i < c.size(); ++i)
		if (i % 2) a.push_back(c[i]);
		else b.push_back(c[i]);
}

template<typename T>
void extendedChain<T>::circularShift(int i)
{
	if (i < 0)
	{
		std::ostringstream s;
		s << "extendedChain<T>::circularShift(int i):i must be >= 0." << " i = " << i;
		throw illegalParameterValue(s.str());
	}

	chainNode<T>* currentNode = this->firstNode;
	for (int j = 0; j < i; ++j)
	{
		lastNode->next = currentNode;
		lastNode = lastNode->next;
		currentNode = currentNode->next;
	}
	this->firstNode = currentNode;
	lastNode->next = nullptr;
}

void testEx6_17()
{
	extendedChain<double> a;
	extendedChain<double> b;

	// test meld
	extendedChain<double> c1 = meld(a, b);
	std::cout << "c1: " << c1 << std::endl;
	a.push_back(0);
	a.push_back(2);
	a.push_back(4);
	a.push_back(6);
	a.push_back(8);
	b.push_back(1);
	b.push_back(3);
	b.push_back(5);
	b.push_back(7);
	b.push_back(9);
	b.push_back(10);
	b.push_back(11);
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	extendedChain<double> c2 = meld(a, b);
	std::cout << "c2 = meld(a,b) => c2: " << c2 << std::endl;

	// test merge(a,b)
	c2.merge(a, b);
	std::cout << "c2.merge(a,b) => c2: " << c2 << std::endl;
	a.merge(b, c2);
	std::cout << "a.merge(b,c2) => a: " << a << std::endl;
	b.merge(a, c2);
	std::cout << "b.merge       (a,c2) => b: " << b << std::endl;
	b.mergeBeEmpty(a, c2);
	std::cout << "b.mergeBeEmpty(a,c2) => b: " << b << std::endl;
	std::cout << "b.mergeBeEmpty(a,c2) => a: " << a << std::endl;
	std::cout << "b.mergeBeEmpty(a,c2) => c2: " << c2 << std::endl;

	// test split
	split(c2, a, b);
	std::cout << "split(c2,a,b) => a: " << a << std::endl;
	std::cout << "split(c2,a,b) => b: " << b << std::endl;
	std::cout << "split(c2,a,b) => c2: " << c2 << std::endl;
	
	// test circularShift
	a.circularShift(2);
	std::cout << "a.circularShift(2) => a: " << a << std::endl;
	a.circularShift(100);
	std::cout << "a.circularShift(100) => a: " << a << std::endl;
}

#endif