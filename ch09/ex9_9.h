#ifndef arrayDeque_
#define arrayDeque_

#include "deque.h"
#include "myExceptions.h"
#include <iostream>
#include <sstream>

template<typename T>
class arrayDeque :public dequeBase<T>
{
	friend std::istream& operator>>(std::istream& in, arrayDeque<T>& q);
	friend std::ostream& operator<<(std::ostream& out, const arrayDeque<T>& q);
public:
	arrayDeque(int initialCapacity = 10);
	~arrayDeque() { delete[]deque; }
	arrayDeque(const arrayDeque& rhs);

	bool empty() const { return theFront == theBack; }
	int size() const { return (theBack - theFront + arrayLength) % arrayLength; }
	T& front()
	{// return front element
		if (theFront == theBack)
			throw queueEmpty();
		return deque[(theFront + 1) % arrayLength];
	}
	T& back()
	{// return theBack element
		if (theFront == theBack)
			throw queueEmpty();
		return deque[theBack];
	}
	void pop_front()
	{// remove the Front element
		if (theFront == theBack)
			throw queueEmpty();
		theFront = (theFront + 1) % arrayLength;
		deque[theFront].~T();	// destructor for T
	}
	void pop_back()
	{// remove the Back element
		if (theFront == theBack)
			throw queueEmpty();
		deque[theBack].~T();
		theBack = (theBack == 0 ? arrayLength - 1 : theBack - 1);
	}
	void push_back(const T& theElement);
	void push_front(const T& theElement);

	// i
	void input(std::istream& in);
	// ii
	void output(std::ostream& out) const;

private:
	T* deque;
	int theFront;
	int theBack;
	int arrayLength;
};

template<typename T>
arrayDeque<T>::arrayDeque(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capaticy = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	deque = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}

template<typename T>
arrayDeque<T>::arrayDeque(const arrayDeque<T>& rhs)
{
	arrayLength = rhs.arrayLength;
	deque = new T[arrayLength];
	theFront = rhs.theFront;
	theBack = rhs.theBack;
	std::copy(rhs.deque, rhs.deque + arrayLength, deque);
}

template<typename T>
void arrayDeque<T>::push_back(const T& theElement)
{// Add theElement to deque.

	// increase array length if necessary
	if ((theBack + 1) % arrayLength == theFront)
	{// double array length
		// allocate a new array
		T* newQueue = new T[2 * arrayLength];

		// copy elements into new array
		int start = (theFront + 1) % arrayLength;
		if (start < 2)	// no wrap around
			std::copy(deque + start, deque + start + arrayLength - 1, newQueue);
		else
		{// deque wraps around
			std::copy(deque + start, deque + arrayLength, newQueue);
			std::copy(deque, deque + theBack + 1, newQueue + arrayLength - start);
		}

		// switch to newQueue and set theFront and theBack
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;	// deque size arrayLength - 1
		arrayLength *= 2;
		delete[] deque;
		deque = newQueue;
	}

	// put theElement at theBack of the deque
	theBack = (theBack + 1) % arrayLength;
	deque[theBack] = theElement;
}

template<typename T>
void arrayDeque<T>::push_front(const T& theElement)
{// Add theElement to deque.

	// increase array length if necessary
	if ((theBack + 1) % arrayLength == theFront)
	{// double array length
		// allocate a new array
		T* newQueue = new T[2 * arrayLength];

		// copy elements into new array
		int start = (theFront + 1) % arrayLength;
		if (start < 2)	// no wrap around
			std::copy(deque + start, deque + start + arrayLength - 1, newQueue);
		else
		{// deque wraps around
			std::copy(deque + start, deque + arrayLength, newQueue);
			std::copy(deque, deque + theBack + 1, newQueue + arrayLength - start);
		}

		// switch to newQueue and set theFront and theBack
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;	// deque size arrayLength - 1
		arrayLength *= 2;
		delete[] deque;
		deque = newQueue;
	}
	
	// put theElement at theFront of the deque
	deque[theFront] = theElement;
	theFront = theFront == 0 ? arrayLength - 1 : theFront - 1;
}


template<typename T>
void arrayDeque<T>::input(std::istream& in)
{
	T t;
	while (in >> t)
		push_back(t);
}

template<typename T>
void arrayDeque<T>::output(std::ostream& out) const
{
	auto font = theFront, back = theBack;
	while (font != back)
	{
		out << deque[(font + 1) % arrayLength] << " ";
		font = (font + 1) % arrayLength;
	}
}

template<typename T>
std::istream& operator>>(std::istream& in, arrayDeque<T>& q)
{
	q.input(in);
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, arrayDeque<T>& q)
{
	q.output(out);
	return out;
}

std::istream& operator>>(std::istream& in, arrayDeque<int>& q)
{
	q.input(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, arrayDeque<int>& q)
{
	q.output(out);
	return out;
}

#endif // !arrayDeque_
