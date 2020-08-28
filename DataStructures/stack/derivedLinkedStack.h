
#ifndef derivedLinkdedStack_
#define derivedLinkdedStack_

#include "stack.h"
#include "chain.h"

template<typename T>
class derivedLinkdedStack :private chain<T>, public stack<T>
{
public:
	derivedLinkdedStack(int initialCapacity = 10) : chain<T>(initialCapacity) {}
	bool empty() const { return chain<T>::empty(); }
	int size() const { return chain<T>::size(); }
	T& top()
	{
		if (chain<T>::empty())
			throw stackEmpty();
		return this->get(0);
	}
	void pop()
	{
		if (chain<T>::empty())
			throw stackEmpty();
		this->erase(0);
	}
	void push(const T& theElement)
	{
		this->insert(0, theElement);
	}
};

#endif