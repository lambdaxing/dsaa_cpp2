// circular array implementation of a queue
// derives from the ADT queue
#ifndef arrayQueue_
#define arrayQueue_

#include "queue.h"
#include "myExceptions.h"
#include <sstream>

template<typename T>
class arrayQueue :public queue<T>
{
public:
	arrayQueue(int initialCapacity = 10);
	~arrayQueue() { delete[] queue; }
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

private:
	int theFront;		// 1 counterclockwise from theFront element
	int theBack;		// position of theBack element
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
