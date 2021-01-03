
#ifndef extendedQueue_
#define extendedQueue_

#include "queue.h"
#include <iostream>

template<typename T>
class extendedQueue :public queueBase<T>
{
public:
	virtual ~extendedQueue() {}
	virtual void input(std::istream&) = 0;
	virtual void output(std::ostream&) const = 0;
	//virtual void split(extendedQueue<T>&, extendedQueue<T>&) const = 0;
	//virtual void merge(const extendedQueue<T>&, const extendedQueue<T>&) = 0;

};

#endif // !extendedQueue_