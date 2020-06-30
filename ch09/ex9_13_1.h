
// linked implementation of a queue
// derives from the ADT queue

#ifndef linkdedQueue_
#define linkdedQueue_

#include "queue.h"
#include "chainNode.h"
#include "myExceptions.h"
#include <sstream>

template<typename T>
class linkedQueue : public queueBase<T>
{
	friend std::istream& operator>>(std::istream& in, linkedQueue& q);
	friend std::ostream& operator<<(std::ostream& out, const linkedQueue& q);
public:
	linkedQueue(int initialCapacity = 10) { queueFront = queueBack =  nullptr; queueSize = 0; }
	~linkedQueue();
	void zero();

	bool empty() const { return queueSize == 0; }
	int size() const { return queueSize; }
	T& front()
	{
		if (queueSize == 0)
			throw queueEmpty();
		return queueFront->element;
	}
	T& back()
	{
		if (queueSize == 0)
			throw queueEmpty();
		return queueBack->element;
	}
	void pop();
	void push(const T&);

	// 9_15
	chainNode* popNode();
	void pushNode(chainNode* theNode);

	// i
	void input(std::istream& in);
	// ii
	void output(std::ostream& out) const;
	// iii
	void split(linkedQueue<T>& oddQ, linkedQueue<T>& evenQ) const;
	// iv
	void merge(const linkedQueue<T>& q1, const linkedQueue<T>& q2);

protected:
	chainNode<T>* queueFront;	// pointer to queue front
	chainNode<T>* queueBack;	// pointer to queue back
	int queueSize;				// number of elements in queue
};

template<typename T>
chainNode<T>* linkedQueue<T>::popNode()
{
	if (queueFront == nullptr)
		throw queueEmpty();

	chainNode<T>* retNode = queueFront;
	queueFront = queueFront->next;
	--queueSize;
	return retNode;
}

template<typename T>
void linkedQueue<T>::pushNode(chainNode<T>* theNode)
{
	// add new node to back of queue
	if (queueSize == 0)
		queueFront = theNode;		// queue empty
	else
		queueBack->next = theNode;	// queue not empty
	queueBack = theNode;

	++queueSize;
}

template<typename T>
void linkedQueue<T>::zero()
{
	while (queueFront != nullptr)
	{// delete front node
		chainNode<T>* nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
	queueSize = 0;
}

template<typename T>
linkedQueue<T>::~linkedQueue()
{// Destructor.
	while (queueFront != nullptr)
	{// delete front node
		chainNode<T>* nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
}

template<typename T>
void linkedQueue<T>::pop()
{// Delete front element
	if (queueFront == nullptr)
		throw queueEmpty();

	chainNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	--queueSize;
}

template<typename T>
void linkedQueue<T>::push(const T& theElement)
{// Add theElement to back of queue.

	// create node for new element
	chainNode<T>* newNode = new chainNode<T>(theElement, nullptr);

	// add new node to back of queue
	if (queueSize == 0)
		queueFront = newNode;		// queue empty
	else
		queueBack->next = newNode;	// queue not empty
	queueBack = newNode;

	++queueSize;
}

template<typename T>
void linkedQueue<T>::input(std::istream& in)
{
	T t;
	while (in >> t)
		push(t);
}

template<typename T>
void linkedQueue<T>::output(std::ostream& out) const
{
	chainNode<T>* c = queueFront;
	while (c != nullptr)
	{
		out << c->element << " ";
		c = c->next;
	}
}

template<typename T>
void linkedQueue<T>::split(linkedQueue<T>& oddQ, linkedQueue<T>& evenQ) const
{
	oddQ.zero();
	evenQ.zero();
	chainNode<T>* c = queueFront;
	int i = 1;
	while (c != nullptr)
	{
		if (i % 2)
			oddQ.push(c->element);
		else
			evenQ.push(c->element);
		c = c->next;
		++i;
	}
}

template<typename T>
void linkedQueue<T>::merge(const linkedQueue<T>& q1, const linkedQueue<T>& q2)
{
	zero();
	chainNode<T>* c1 = q1.queueFront;
	chainNode<T>* c2 = q2.queueFront;

	int i = 1;
	while (c1 != nullptr && c2 != nullptr)
	{
		if (i % 2)
		{
			push(c1->element);
			c1 = c1->next;
		}
		else
		{
			push(c2->element);
			c2 = c2->next;
		}
		++i;
	}
	while (c1 != nullptr)
	{
		push(c1->element);
		c1 = c1->next;
	}
	while (c2 != nullptr)
	{
		push(c2->element);
		c2 = c2->next;
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const linkedQueue<T>& q)
{
	q.output(out);
	return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, linkedQueue<T>& q)
{
	q.input(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const linkedQueue<int>& q)
{
	q.output(out);
	return out;
}

std::istream& operator>>(std::istream& in, linkedQueue<int>& q)
{
	q.input(in);
	return in;
}
#endif
