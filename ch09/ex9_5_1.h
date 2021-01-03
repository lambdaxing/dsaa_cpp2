// circular array implementation of a queue
// derives from the ADT queue
#ifndef arrayQueue_
#define arrayQueue_

#include "queue.h"
#include "myExceptions.h"
#include <sstream>
#include <iostream>

template<typename T>
class arrayQueue :public queueBase<T>
{
	friend std::istream& operator>>(std::istream& in, arrayQueue& q);
	friend std::ostream& operator<<(std::ostream& out, const arrayQueue& q);
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[] queue; }
	arrayQueue(const arrayQueue& rhs);

	bool empty() const { return theFront == theBack; }
	int size() const { return (theBack - theFront + arrayLength) % arrayLength; }
	T& front()
	{// return front element
		if (theFront == theBack)
			throw queueEmpty();
		return queue[(theFront + 1) % arrayLength];
	}
	T& back()
	{// return theBack element
		if (theFront == theBack)
			throw queueEmpty();
		return queue[theBack];
	}
	void pop()
	{// remove the Front element
		if (theFront == theBack)
			throw queueEmpty();
		theFront = (theFront + 1) % arrayLength;
		queue[theFront].~T();	// destructor for T
	}
	void push(const T& theElement);

	// i
	void input(std::istream& in);
	// ii
	void output(std::ostream& out) const;
	// iii
	void split(arrayQueue<T>& oddQ, arrayQueue<T>& evenQ) const;
	// iv
	void merge(const arrayQueue<T>& q1, const arrayQueue<T>& q2);
private:
	int theFront;		// 1 counterclockwise from theFront element
	int theBack;		// position of theBack element
	int arrayLength;	// queue capacity
	T* queue;			// element array
};

template<typename T>
arrayQueue<T>::arrayQueue(const arrayQueue<T>& rhs)
{
	arrayLength = rhs.arrayLength;
	queue = new T[arrayLength];
	theFront = rhs.theFront;
	theBack = rhs.theBack;
	std::copy(rhs.queue, rhs.queue + arrayLength, queue);
}

template<typename T>
void arrayQueue<T>::merge(const arrayQueue<T>& q1, const arrayQueue<T>& q2)
{
	delete[] queue;
	queue = new T[q1.size() + q2.size() + 1];
	theFront = theBack = 0;

	auto font1 = q1.theFront, font2 = q2.theFront;
	for (int i = 1; font1 != q1.theBack && font2 != q2.theBack; ++i)
	{
		if (i % 2)
		{
			push(q1.queue[(font1 + 1) % q1.arrayLength]);
			font1 = (font1 + 1) % q1.arrayLength;
		}
		else
		{
			push(q2.queue[(font2 + 1) % q2.arrayLength]);
			font2 = (font2 + 1) % q2.arrayLength;
		}
	}
	while (font1 != q1.theBack)
	{
		push(q1.queue[(font1 + 1) % q1.arrayLength]);
		font1 = (font1 + 1) % q1.arrayLength;
	}
	while (font2 != q2.theBack)
	{
		push(q2.queue[(font2 + 1) % q2.arrayLength]);
		font2 = (font2 + 1) % q2.arrayLength;
	}
}

template<typename T>
void arrayQueue<T>::split(arrayQueue<T>& oddQ, arrayQueue<T>& evenQ) const 
{
	auto font = theFront, back = theBack;
	int i = 1;
	while (font != back)
	{
		if (i % 2)
			oddQ.push(queue[(font + 1) % arrayLength]);
		else
			evenQ.push(queue[(font + 1) % arrayLength]);
		font = (font + 1) % arrayLength;
		++i;
	}
}

template<typename T>
void arrayQueue<T>::input(std::istream& in)
{
	T t;
	while (in >> t)
		push(t);
}

template<typename T>
void arrayQueue<T>::output(std::ostream& out) const
{
	auto font = theFront, back = theBack;
	while (font != back)
	{
		out << queue[(font + 1) % arrayLength] << " ";
		font = (font + 1) % arrayLength;
	}
}

template<typename T>
std::istream& operator>>(std::istream& in, arrayQueue<T>& q)
{
	q.input(in);
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, arrayQueue<T>& q)
{
	q.output(out);
	return out;
}

std::istream& operator>>(std::istream& in, arrayQueue<int>& q)
{
	q.input(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, arrayQueue<int>& q)
{
	q.output(out);
	return out;
}

template<typename T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capaticy = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}

template<typename T>
void arrayQueue<T>::push(const T& theElement)
{// Add theElement to queue.

	// increase array length if necessary
	if ((theBack + 1) % arrayLength == theFront)
	{// double array length
		// allocate a new array
		T* newQueue = new T[2 * arrayLength];

		// copy elements into new array
		int start = (theFront + 1) % arrayLength;
		if (start < 2)	// no wrap around
			std::copy(queue + start, queue + start + arrayLength - 1, newQueue);
		else
		{// queue wraps around
			std::copy(queue + start, queue + arrayLength, newQueue);
			std::copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
		}

		// switch to newQueue and set theFront and theBack
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;	// queue size arrayLength - 1
		arrayLength *= 2;
		delete[] queue;
		queue = newQueue;
	}

	// put theElement at theBack of the queue
	theBack = (theBack + 1) % arrayLength;
	queue[theBack] = theElement;
}
#endif // !arrayQueue_
