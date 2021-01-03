
#ifndef twoStacks_
#define twoStacks_

#include <iostream>
#include <iterator>
#include <algorithm>
#include "myExceptions.h"

template<typename T>
class twoStacks
{
public:
	twoStacks(int initialCapacity = 10);
	~twoStacks() { delete[] stacks; }

	bool empty1() const { return stackTop1 == -1; }
	int size1() const { return stackTop1 + 1; }
	T& top1()
	{
		if (stackTop1 == -1)
			throw stackEmpty();
		return stacks[stackTop1];
	}
	void pop1()
	{
		if (stackTop1 == -1)
			throw stackEmpty();
		stacks[stackTop1--].~T();
	}
	void push1(const T& theElement);
	void output1(std::ostream& out) const;

	bool empty2() const { return stackTop2 == arrayLength; }
	int size2() const { return arrayLength - stackTop2; }
	T& top2()
	{
		if (stackTop2 == arrayLength)
			throw stackEmpty();
		return stacks[stackTop2];
	}
	void pop2()
	{
		if (stackTop2 == arrayLength)
			throw stackEmpty();
		stacks[stackTop2++].~T();
	}
	void push2(const T& theElement);
	void output2(std::ostream& out) const;

private:
	void changeLength();
	int stackTop1, stackTop2;
	int arrayLength;
	T* stacks;
};

template<typename T>
void twoStacks<T>::changeLength()
{
	T* temp = new T[arrayLength * 2];
	int stack1Size = size1();
	int stack2Size = size2();
	// copy stack1
	std::copy(stacks, stacks + stack1Size, temp);
	// copy stack2
	std::copy(stacks + stackTop2, stacks + arrayLength, temp + arrayLength * 2 - stack2Size);
	delete[] stacks;
	stacks = temp;
	arrayLength *= 2;
	// update stackTop2
	stackTop2 = arrayLength - stack2Size;
}

template<typename T>
void twoStacks<T>::output1(std::ostream& out) const
{
	std::copy(stacks, stacks + stackTop1 + 1, std::ostream_iterator<T>(out, " "));
}

template<typename T>
void twoStacks<T>::output2(std::ostream& out) const
{
	std::copy(stacks + stackTop2, stacks + arrayLength, std::ostream_iterator<T>(out, " "));
}

template<typename T>
twoStacks<T>::twoStacks(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	stacks = new T[arrayLength];
	stackTop1 = -1;
	stackTop2 = arrayLength;
}

template<typename T>
void twoStacks<T>::push1(const T& theElement)
{
	if (stackTop1 == stackTop2 - 1)
		changeLength();
	stacks[++stackTop1] = theElement;
}

template<typename T>
void twoStacks<T>::push2(const T& theElement)
{
	if (stackTop1 == stackTop2 - 1)
		changeLength();
	stacks[--stackTop2] = theElement;
}

#endif