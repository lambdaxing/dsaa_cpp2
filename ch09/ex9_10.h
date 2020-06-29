#ifndef dequeStack_
#define dequeStack_

#include "stack.h"
#include "ex9_9.h"

template<typename T>
class dequeStack :public stack<T>, private arrayDeque<T>
{
public:
	dequeStack(int initialCapacity = 10) :arrayDeque<T>(initialCapacity) {}
	bool empty() const { return arrayDeque<T>::empty(); }
	int size() const { return arrayDeque<T>::size(); }
	T& top()
	{
		return arrayDeque<T>::back();
	}
	void pop()
	{
		arrayDeque<T>::pop_back();
	}
	void push(const T& theElement) { arrayDeque<T>::push_back(theElement); }
	void output(std::ostream& out) const { arrayDeque<T>::output(out); }
};

#endif // !dequeStack_
