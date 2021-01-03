// array implementation of a stack
// derives from the ADT stack

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
	~arrayStack() { delete[] stack; }
	bool empty() const { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	T& top()
	{
		if (stackTop == -1)
			throw stackEmpty();
		return stack[stackTop];
	}
	void pop()
	{
		if (stackTop == -1)
			throw stackEmpty();
		stack[stackTop--].~T();	 // destructor for T
		if (stackTop + 1 < arrayLength / 4)
		{
			changeLength1D(stack, arrayLength, arrayLength / 4);
			arrayLength /= 4;
		}
	}
	void push(const T& theElement);
	void output(std::ostream& out) const;

protected:
	int stackTop;         // current top of stack
	int arrayLength;      // stack capacity
	T* stack;             // element array
};

template<typename T>
void arrayStack<T>::output(std::ostream& out) const
{
	std::copy(stack, stack + stackTop + 1, std::ostream_iterator<T>(out, " "));
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
	stack = new T[arrayLength];
	stackTop = -1;
}

template<typename T>
void arrayStack<T>::push(const T& theElement)
{// Add theElement to stack.
	if (stackTop == arrayLength - 1)
	{
		changeLength1D(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	// add at stack top
	stack[++stackTop] = theElement;
}

#endif