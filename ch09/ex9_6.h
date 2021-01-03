#ifndef slowArrayQueue_
#define slowArrayQueue_

#include "queue.h"
#include "myExceptions.h"
#include <iostream>
#include <sstream>
template<typename T>
class slowArrayQueue :public queueBase<T>
{
	friend std::istream& operator>>(std::istream& in, slowArrayQueue& q);
	friend std::ostream& operator<<(std::ostream& out, const slowArrayQueue& q);
public:
	slowArrayQueue(int initialCapacity = 10);
	~slowArrayQueue() { delete[] queue; }
	slowArrayQueue(const slowArrayQueue& rhs);

	bool empty() const { return theBack < theFront; }
	int size() const { return (theBack < theFront ? 0 : theBack - theFront); }
	T& front()
	{// return front element
		if (theBack < theFront)
			throw queueEmpty();
		return queue[theFront];
	}
	T& back()
	{// return theBack element
		if (theBack < theFront)
			throw queueEmpty();
		return queue[theBack];
	}
	void pop()
	{// remove the Front element
		if (theBack < theFront)
			throw queueEmpty();
		queue[theFront++].~T();	// destructor for T
	}
	void push(const T& theElement);

	// i
	void input(std::istream& in);
	// ii
	void output(std::ostream& out) const;

private:
	T* queue;
	int theFront;
	int theBack;
	int arrayLength;
};

template<typename T>
slowArrayQueue<T>::slowArrayQueue(int initialCapacity)
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
	theBack = -1;
}

template<typename T>
slowArrayQueue<T>::slowArrayQueue(const slowArrayQueue<T>& rhs)
{
	arrayLength = rhs.arrayLength;
	queue = new T[arrayLength];
	theFront = rhs.theFront;
	theBack = rhs.theBack;
	std::copy(rhs.queue, rhs.queue + arrayLength, queue);
}

template<typename T>
void slowArrayQueue<T>::push(const T& theElement)
{// Add theElement to queue.

	// increase array length or move elements to the left 
	if (theBack + 1 >= arrayLength)
	{
		if (theFront > 0)
		{// move to the left
			std::copy(queue + theFront, queue + arrayLength, queue);
			theBack -= theFront;
			theFront = 0;
		}
		else
		{// increase length
			// double array length
			// allocate a new array
			T* newQueue = new T[2 * arrayLength];
			std::copy(queue, queue + arrayLength, newQueue);
			arrayLength *= 2;
			delete[] queue;
			queue = newQueue;
		}
	}

	// put theElement at theBack of the queue
	++theBack;
	queue[theBack] = theElement;
}


template<typename T>
void slowArrayQueue<T>::input(std::istream& in)
{
	T t;
	while (in >> t)
		push(t);
}

template<typename T>
void slowArrayQueue<T>::output(std::ostream& out) const
{
	auto font = theFront;
	while (font <= theBack)
		out << queue[font++] << " ";
}

template<typename T>
std::istream& operator>>(std::istream& in, slowArrayQueue<T>& q)
{
	q.input(in);
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, slowArrayQueue<T>& q)
{
	q.output(out);
	return out;
}

std::istream& operator>>(std::istream& in, slowArrayQueue<int>& q)
{
	q.input(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, slowArrayQueue<int>& q)
{
	q.output(out);
	return out;
}
#endif // !slowArrayQueue_