
#ifndef stackWithArrayList_
#define stackWithArrayList_

#include "stack.h"
#include  "arrayList.h"

template<typename T>
class stackWithArrayList :public stack<T>
{
public:
	stackWithArrayList(int initialCapacity = 10) : stack({ initialCapacity }) {}
	bool empty() const { return stack.empty(); }
	int size() const { return stack.size(); }
	T& top()
	{
		if (stack.empty())
			throw stackEmpty();
		return stack.get(stack.size() - 1);
	}
	void pop()
	{
		if (stack.empty())
			throw stackEmpty();
		stack.erase(stack.size() - 1);
	}
	void push(const T& theElement)
	{
		stack.insert(stack.size(), theElement);
	}
private:
	arrayList<T> stack;
};

#endif