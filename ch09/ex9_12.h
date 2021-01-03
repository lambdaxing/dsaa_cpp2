#ifndef linkedQueueFromExtendedChain_
#define linkedQueueFromExtendedChain_

#include "extendedChain.h"
#include "queue.h"

template<typename T>
class linkedQueueFromExtendedChain :private extendedChain<T>, public queueBase<T>
{

public:
	linkedQueueFromExtendedChain(int initialCapacity = 10) :extendedChain<T>(initialCapacity) {}

	bool empty() const { return extendedChain<T>::empty(); }
	int size() const { return extendedChain<T>::size(); }
	T& front()
	{
		if (extendedChain<T>::empty())
			throw queueEmpty();
		return extendedChain<T>::get(0);								// get front == get first element
	}
	T& back()
	{
		if (extendedChain<T>::empty())
			throw queueEmpty();
		return extendedChain<T>::get(extendedChain<T>::size() - 1);		// get back == get last element
	}
	void pop()
	{ 
		if (extendedChain<T>::empty())
			throw queueEmpty();
		extendedChain<T>::erase(0);										// pop == erase first element
	}
	void push(const T& theElement)
	{
		extendedChain<T>::push_back(theElement);						// push == push_back
	}

	void output(std::ostream& out) { extendedChain<T>::output(out); }
};

#endif // !linkedQueueFromExtendedChain_