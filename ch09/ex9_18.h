#ifndef circularDeque_
#define circularDeque_

#include "deque.h"
#include "chainNode.h"
#include "myExceptions.h"
#include <iostream>

template<typename T>
class circularDeque :public dequeBase<T>
{
	friend std::istream& operator>>(std::istream& in, circularDeque<T>& q);
	friend std::ostream& operator<<(std::ostream& out, const circularDeque<T>& q);
public:
	circularDeque(int initialCapacity = 10);
	circularDeque(const circularDeque&);
	~circularDeque();

	bool empty() const { return queueSize == 0; }
	int size() const { return queueSize; }
	T& front()
	{// return front element
		if (queueSize == 0)
			throw queueEmpty();
		return theFront->element;
	}
	T& back()
	{// return theBack element
		if (queueSize == 0)
			throw queueEmpty();
		return theBack->element;
	}
	void pop_front()
	{// remove the Front element
		if (queueSize == 0)
			throw queueEmpty();
		chainNode<T>* nextNode = theFront->next;
		delete theFront;
		theFront = nextNode;
		--queueSize;
		if (queueSize == 0)
			theFront = theBack = nullptr;
		else
			theBack->next = theFront;
	}
	void pop_back()
	{// remove the Back element
		if (queueSize == 0)
			throw queueEmpty();

		chainNode<T>* c = theFront;
		while (c->next != nullptr && c->next != theBack) c = c->next;
		c->next = theFront;
		delete theBack;
		--queueSize;
		if (queueSize == 0)
			theFront = theBack = nullptr;
		else
			theBack = c;
	}
	void push_back(const T& theElement);
	void push_front(const T& theElement);

	// i
	void input(std::istream& in);
	// ii
	void output(std::ostream& out) const;

private:
	chainNode<T>* theFront;
	chainNode<T>* theBack;
	int queueSize;
};

template<typename T>
circularDeque<T>::circularDeque(int initialCapacity)
{
	theFront = theBack = nullptr;
	queueSize = 0;
}

template<typename T>
circularDeque<T>::circularDeque(const circularDeque<T>& x)
{
	// Copy constructor.
	queueSize = x.queueSize;

	if (queueSize == 0)
	{// theList is empty
		theFront = theBack = nullptr;
		return;
	}

	// non-empty list
	chainNode<T>* sourceNode = x.theFront;
	// node in theList to copy from
	theFront = new chainNode<T>(sourceNode->element);
	// copy first element of theList
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = theFront;
	// current last node in *this
	while (sourceNode != x.theFront)
	{// copy remaining elements
		targetNode->next = new chainNode<T>(sourceNode->element, nullptr);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = theFront;		// end the chain
	theBack = targetNode;
}

template<typename T>
circularDeque<T>::~circularDeque()
{
	if(theBack != nullptr)
		theBack->next = nullptr;
	while (theFront != nullptr)
	{
		chainNode<T>* nextNode = theFront->next;
		delete theFront;
		theFront = nextNode;
	}
}

template<typename T>
void circularDeque<T>::push_back(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, theFront);

	if (queueSize == 0)
	{
		newNode->next = newNode;
		theFront = theBack = newNode;	
	}
	else
	{
		theBack->next = newNode;
		theBack = newNode;
	}
	++queueSize;
}

template<typename T>
void circularDeque<T>::push_front(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement, theFront);

	if (queueSize == 0)
	{
		newNode->next = newNode;
		theFront = theBack = newNode;
	}
	else
	{
		theFront = newNode;
		theBack->next = theFront;
	}
	++queueSize;
}

template<typename T>
void circularDeque<T>::input(std::istream& in)
{
	T t;
	while (in >> t)
		push_back(t);
}

template<typename T>
void circularDeque<T>::output(std::ostream& out) const
{
	chainNode<T>* c = theFront;
	if (theBack != nullptr) theBack->next = nullptr;
	while (c != nullptr)
	{
		out << c->element << " ";
		c = c->next;
	}
	if (theBack != nullptr) theBack->next = theFront;
}

template<typename T>
std::istream& operator>>(std::istream& in, circularDeque<T>& q)
{
	q.input(in);
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, circularDeque<T>& q)
{
	q.output(out);
	return out;
}

std::istream& operator>>(std::istream& in, circularDeque<int>& q)
{
	q.input(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, circularDeque<int>& q)
{
	q.output(out);
	return out;
}
#endif // !circularDeque_
