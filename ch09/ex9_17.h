#ifndef linkedDeque_
#define linkedDeque_

#include "deque.h"
#include "chainNode.h"

template<typename T>
class linkedDeque :public dequeBase<T>
{
	friend std::istream& operator>>(std::istream& in, linkedDeque<T>& q);
	friend std::ostream& operator<<(std::ostream& out, const linkedDeque<T>& q);
public:
	linkedDeque(int initialCapacity = 10);
	linkedDeque(const doublyLinkedDeque&);
	~linkedDeque();

	bool empty() const { return queueSize == 0; }
	int size() const { return queueSize; }
	T& front()
	{// return front element
		if (queueSize == 0)
			throw queueEmpty();
		return theFront->element;
	}
	T& back()
	{// return theBack element
		if (queueSize == 0)
			throw queueEmpty();
		return theBack->element;
	}
	void pop_front()
	{// remove the Front element
		if (queueSize == 0)
			throw queueEmpty();
		doubleChainNode<T>* nextNode = theFront->next;
		delete theFront;
		theFront = nextNode;
		--queueSize;
		if (queueSize == 0)
			theFront = theBack = nullptr;
		else
			theFront->previous = nullptr;
	}
	void pop_back()
	{// remove the Back element
		if (queueSize == 0)
			throw queueEmpty();
		doubleChainNode<T>* preNode = theBack->previous;
		delete theBack;
		theBack = preNode;
		--queueSize;
		if (queueSize == 0)
			theFront = theBack = nullptr;
		else
			theBack->next = nullptr;
	}
	void push_back(const T& theElement);
	void push_front(const T& theElement);

	// i
	void input(std::istream& in);
	// ii
	void output(std::ostream& out) const;

private:
	chainNode<T>* theFront;
	chainNode<T>* theBack;
	int queueSize;
};
#endif // !linkedDeque_
