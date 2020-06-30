#ifndef doublyLinkedDeque_
#define doublyLinkedDeque_

#include "deque.h"
#include "doubleChainNode.h"
#include "myExceptions.h"	

template<typename T>
class doublyLinkedDeque :public dequeBase<T>
{
	friend std::istream& operator>>(std::istream& in, doublyLinkedDeque<T>& q);
	friend std::ostream& operator<<(std::ostream& out, const doublyLinkedDeque<T>& q);
public:
	doublyLinkedDeque(int initialCapacity = 10);
	doublyLinkedDeque(const doublyLinkedDeque&);
	~doublyLinkedDeque();

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
		doubleChainNode<T>* nextNode = theFront->next;
		delete theFront;
		theFront = nextNode;
		--queueSize;
		if (queueSize == 0)
			theFront = theBack = nullptr;
		else
			theFront->previous = nullptr;
	}
	void pop_back()
	{// remove the Back element
		if (queueSize == 0)
			throw queueEmpty();
		doubleChainNode<T>* preNode = theBack->previous;
		delete theBack;
		theBack = preNode;
		--queueSize;
		if (queueSize == 0)
			theFront = theBack = nullptr;
		else
			theBack->next = nullptr;
	}
	void push_back(const T& theElement);
	void push_front(const T& theElement);

	// i
	void input(std::istream& in);
	// ii
	void output(std::ostream& out) const;
private:
	doubleChainNode<T>* theFront;
	doubleChainNode<T>* theBack;
	int queueSize;
};

template<typename T>
doublyLinkedDeque<T>::doublyLinkedDeque(int initialCapacity)
{
	theFront = theBack = nullptr;
	queueSize = 0;
}

template<typename T>
doublyLinkedDeque<T>::doublyLinkedDeque(const doublyLinkedDeque& x)
{
	// Copy constructor.
	queueSize = x.queueSize;

	if (queueSize == 0)
	{// theList is empty
		theFront = theBack = nullptr;
		return;
	}

	// non-empty list
	doubleChainNode<T>* sourceNode = x.theFront;
	// node in theList to copy from
	theFront = new doubleChainNode<T>(sourceNode->element);
	// copy first element of theList
	sourceNode = sourceNode->next;
	doubleChainNode<T>* targetNode = theFront;
	// current last node in *this
	while (sourceNode != nullptr)
	{// copy remaining elements
		targetNode->next = new doubleChainNode<T>(sourceNode->element, targetNode);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	//targetNode->next = nullptr;		// end the chain
	theBack = targetNode;
	//theFront->previous = nullptr;	// begin the chain 
}

template<typename T>
doublyLinkedDeque<T>::~doublyLinkedDeque()
{
	while (theFront != nullptr)
	{
		doubleChainNode<T>* nextNode = theFront->next;
		delete theFront;
		theFront = nextNode;
	}
}

template<typename T>
void doublyLinkedDeque<T>::push_back(const T& theElement)
{
	doubleChainNode<T>* newNode = new doubleChainNode<T>(theElement, theBack, nullptr);

	// add new node to back of queue
	if (queueSize == 0)
		theFront = theBack = newNode;		// queue empty
	else
		theBack->next = newNode;			// queue not empty
	theBack = newNode;

	++queueSize;
}

template<typename T>
void doublyLinkedDeque<T>::push_front(const T& theElement)
{
	doubleChainNode<T>* newNode = new doubleChainNode<T>(theElement, nullptr, theFront);

	// add new node to back of queue
	if (queueSize == 0)
		theFront = theBack = newNode;		// queue empty
	else
		theFront->previous = newNode;			// queue not empty
	theFront = newNode;

	++queueSize;
}

template<typename T>
void doublyLinkedDeque<T>::input(std::istream& in)
{
	T t;
	while (in >> t)
		push_back(t);
}

template<typename T>
void doublyLinkedDeque<T>::output(std::ostream& out) const
{
	doubleChainNode<T>* c = theFront;
	while (c != nullptr)
	{
		out << c->element << " ";
		c = c->next;
	}
}

template<typename T>
std::istream& operator>>(std::istream& in, doublyLinkedDeque<T>& q)
{
	q.input(in);
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, doublyLinkedDeque<T>& q)
{
	q.output(out);
	return out;
}

std::istream& operator>>(std::istream& in, doublyLinkedDeque<int>& q)
{
	q.input(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, doublyLinkedDeque<int>& q)
{
	q.output(out);
	return out;
}

#endif // !doublyLinkedDeque_
