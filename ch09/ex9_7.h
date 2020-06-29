// circular array implementation of a queue
// derives from the ADT queue
#ifndef arrayQueue_9_7_
#define arrayQueue_9_7_

#include "queue.h"
#include "myExceptions.h"
#include <sstream>

template<typename T>
class arrayQueue :public queueBase<T>
{
	friend std::istream& operator>>(std::istream& in, arrayQueue& q);
	friend std::ostream& operator<<(std::ostream& out, const arrayQueue& q);
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[] queue; }
	bool empty() const { return theSize == 0; }
	int size() const { return theSize; }
	T& front()
	{// return front element
		if (theSize == 0)
			throw queueEmpty();
		return queue[theFront];
	}
	T& back()
	{// return theBack element
		if (theSize == 0)
			throw queueEmpty();
		return queue[(theFront + theSize - 1) % arrayLength];
	}
	void pop()
	{// remove the Front element
		if (theSize == 0)
			throw queueEmpty();
		queue[theFront].~T();	// destructor for T
		theFront = (theFront + 1) % arrayLength;
		--theSize;
	}
	void push(const T& theElement);

	// i
	void input(std::istream& in);
	// ii
	void output(std::ostream& out) const;
protected:
	int theFront;		// 1 counterclockwise from theFront element
	int theSize;		    // theSize of queue
	int arrayLength;	// queue capacity
	T* queue;			// element array
};

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
	theSize = 0;
}

template<typename T>
void arrayQueue<T>::push(const T& theElement)
{// Add theElement to queue.

	// increase array length if necessary
	if (theSize == arrayLength)
	{// double array length
		// allocate a new array
		T* newQueue = new T[2 * arrayLength];

		// copy elements into new array
		int start = theFront;
		if (start == 0)	// no wrap around
			std::copy(queue + start, queue + start + arrayLength, newQueue);
		else
		{// queue wraps around
			std::copy(queue + start, queue + arrayLength, newQueue);
			std::copy(queue, queue + start, newQueue + arrayLength - start);
		}

		// switch to newQueue and set theFront and theBack
		theFront = 0;
		arrayLength *= 2;
		delete[]queue;
		queue = newQueue;
	}

	// put theElement at theBack of the queue
	++theSize;
	queue[(theFront + theSize - 1) % arrayLength] = theElement;
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
	auto font = theFront;
	for (int i = 0; i < theSize; ++i)
		out << queue[font++] << " ";
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

#endif // !arrayQueue_
