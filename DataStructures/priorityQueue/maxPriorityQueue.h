// abstract class max priority queue
// all methods are pure virtual function

#ifndef MAX_PRIORITY_QUEUE_
#define MAX_PRIORITY_QUEUE_

template<typename T>
class maxPriorityQueue
{
public:
	virtual ~maxPriorityQueue() {}
	virtual bool empty() const = 0;
					// return true if queue is empty
	virtual int size() const = 0;
					// return number of elements in queue
	virtual const T& top() = 0;
					// return reference to the max element
	virtual void pop() = 0;
					// remove the top element
	virtual void push(const T& theElement) = 0;
					// add theElement to the queue
};
#endif // !MAX_PRIORITY_QUEUE_
