
#ifndef arrayStack_
#define arrayStack_

#include <iterator>
#include <iostream>
#include <sstream>
#include "stack.h"
#include "myExceptions.h"
#include "changeLength1D.h"

template<typename T>
class arrayStack :public stack<T>
{
public:
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[] stacks; }
	bool empty() const { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	T& top()
	{
		if (stackTop == -1)
			throw stackEmpty();
		return stacks[stackTop];
	}
	void pop()
	{
		if (stackTop == -1)
			throw stackEmpty();
		stacks[stackTop--].~T();
		if (stackTop + 1 < arrayLength / 4)
		{
			changeLength1D(stacks, arrayLength, arrayLength / 4);
			arrayLength /= 4;
		}
	}
	void push(const T& theElement);
	void output(std::ostream& out) const;

protected:
	int stackTop;
	int arrayLength;
	T* stacks;
};

template<typename T>
void arrayStack<T>::output(std::ostream& out) const
{
	std::copy(stacks, stacks + stackTop + 1, std::ostream_iterator<T>(out, " "));
}

template<typename T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	stacks = new T[arrayLength];
	stackTop = -1;
}

template<typename T>
void arrayStack<T>::push(const T& theElement)
{
	if (stackTop == arrayLength - 1)
	{
		changeLength1D(stacks, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	stacks[++stackTop] = theElement;
}

#endif