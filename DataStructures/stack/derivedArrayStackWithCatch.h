
#ifndef derivedArrayStackWithCatch_
#define derivedArrayStackWithCatch_

#include "arrayList.h"
#include "stack.h"
#include <string>

template<typename T>
class derivedArrayStackWithCatch :protected arrayList<T>, public stack<T>
{
public:
	derivedArrayStackWithCatch(int initialCapacity = 10) : arrayList<T>(initialCapacity) {}
	bool empty() const { return arrayList<T>::empty(); }
	int size() const { return arrayList<T>::size(); }
	T& top()
	{
		try {
			return arrayList<T>::get(arrayList<T>::size() - 1);
		}
		catch (illegalIndex)
		{
			throw stackEmpty();
		}
	}
	void pop()
	{
		try{
			arrayList<T>::erase(arrayList<T>::size() - 1);
		}catch (illegalIndex)
		{
			throw stackEmpty();
		}
	}
	void push(const T& theElement)
	{
		arrayList<T>::insert(arrayList<T>::size(), theElement);
	}
};

#endif