#ifndef extendedLinkedQueue_
#define extendedLinkedQueue_

#include "extendedQueue.h"
#include "ex9_13_1.h"

template<typename T>
class extendedLinkedQueue :public linkedQueue<T>, public extendedQueue<T>
{
	friend std::istream& operator>>(std::istream& in, extendedLinkedQueue& q);
	friend std::ostream& operator<<(std::ostream& out, const extendedLinkedQueue& q);
public:
	extendedLinkedQueue(int initialCapacity = 10) :linkedQueue<T>(initialCapacity) {}

	bool empty() const { return this->queueSize == 0; }
	int size() const { return this->queueSize; }
	T& front() { return linkedQueue<T>::front(); }
	T& back() { return linkedQueue<T>::back(); }
	void pop() { linkedQueue<T>::pop(); }
	void push(const T& theElement) { linkedQueue<T>::push(theElement); }

	void input(std::istream& in) { linkedQueue<T>::input(in); }
	void output(std::ostream& out) const { linkedQueue<T>::output(out); }
	void split(extendedLinkedQueue<T>& oddQ, extendedLinkedQueue<T>& evenQ) const { linkedQueue<T>::split(oddQ, evenQ); }
	void merge(const extendedLinkedQueue<T>& q1, const extendedLinkedQueue<T>& q2) { linkedQueue<T>::merge(q1, q2); }
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const extendedLinkedQueue<T>& q)
{
	q.output(out);
	return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, extendedLinkedQueue<T>& q)
{
	q.input(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, const extendedLinkedQueue<int>& q)
{
	q.output(out);
	return out;
}

std::istream& operator>>(std::istream& in, extendedLinkedQueue<int>& q)
{
	q.input(in);
	return in;
}
#endif // !extendedLinkedQueue_