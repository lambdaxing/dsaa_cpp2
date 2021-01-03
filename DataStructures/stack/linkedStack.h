// linked implementation of a stack
// derives from the ADT stack

#ifndef linkedStack_
#define linkedStack_

#include "stack.h"
#include "myExceptions.h"
#include "chainNode.h"

template<typename T>
class linkedStack :public stack<T>
{
public:
	linkedStack(int initialCapacity = 10) { stackTop = nullptr; stackSize = 0; }
	~linkedStack();
	bool empty() const { return stackSize == 0; }
	int size() const { return stackSize; }
	T& top()
	{
		if (stackSize == 0)
			throw stackEmpty();
		return stackTop->element;
	}
	void pop();
	void push(const T& theElement)
	{
		stackTop = new chainNode<T>(theElement, stackTop);
		++stackSize;
	}
	void pushNode(chainNode<T>* theNode)
	{
		theNode->next = stackTop;
		stackTop = theNode;
		++stackSize;
	}
	chainNode<T>* popNode()
	{
		if (stackSize == 0)
			throw stackEmpty();
		chainNode<T>* t = stackTop;
		stackTop = stackTop->next;
		--stackSize;
		return t;
	}

	void output(std::ostream& out) const;

protected:
	chainNode<T>* stackTop;  // pointer to stack top
	int stackSize;           // number of elements in stack
};

template<typename T>
void linkedStack<T>::output(std::ostream& out) const
{
	chainNode<T>* c = stackTop;
	while (c != nullptr)
	{
		out << c->element << " ";
		c = c->next;
	}
}

template<typename T>
linkedStack<T>::~linkedStack()
{
	while (stackTop != nullptr)
	{
		chainNode<T>* nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
	}
}

template<typename T>
void linkedStack<T>::pop()
{
	if (stackSize == 0)
		throw stackEmpty();

	chainNode<T>* nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	--stackSize;
}

#endif