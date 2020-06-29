#ifndef dequeQueue_
#define dequeQueue_

#include "queue.h"
#include "ex9_9.h"

template<typename T>
class dequeQueue :public queueBase<T>, private arrayDeque<T>
{
public:
	dequeQueue(int initialCapacity = 10) :arrayDeque<T>(initialCapacity) {}
	~dequeQueue() {}

	bool empty() const { return arrayDeque<T>::empty(); }
	int size() const { return arrayDeque<T>::size(); }
	T& front()
	{// return front element
		return arrayDeque<T>::front();
	}
	T& back()
	{// return theBack element
		return arrayDeque<T>::back();
	}
	void pop()
	{// remove the Front element
		arrayDeque<T>::pop_front();
	}
	void push(const T& theElement) { arrayDeque<T>::push_back(theElement); }

	// i
	void input(std::istream& in) { arrayDeque<T>::input(in); }
	// ii
	void output(std::ostream& out) const { arrayDeque<T>::output(out); }
};

#endif // !dequeQueue_
