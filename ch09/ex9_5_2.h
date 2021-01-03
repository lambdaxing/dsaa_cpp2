#ifndef extendedarrayQueue_
#define extendedarrayQueue_

#include "extendedQueue.h"
#include "arrayQueue.h"

template<typename T>
class extendedarrayQueue : public extendedQueue<T>, public arrayQueue<T>
{
	friend std::istream& operator>>(std::istream& in, extendedarrayQueue& q);
	friend std::ostream& operator<<(std::ostream& out, const extendedarrayQueue& q);

public:
	extendedarrayQueue(int initialCapacity = 10) :arrayQueue<T>(initialCapacity) {}

	bool empty() const { return this->theFront == this->theBack; }
	int size() const { return (this->theBack - this->theFront + this->arrayLength) % this->arrayLength; }
	T& front() { return arrayQueue<T>::front(); }
	T& back() { return arrayQueue<T>::back(); }
	void pop() { arrayQueue<T>::pop(); }
	void push(const T& theElement) { arrayQueue<T>::push(theElement); }

	void input(std::istream& in);
	void output(std::ostream& out) const;
	void split(extendedarrayQueue<T>& oddQ, extendedarrayQueue<T>& evenQ) const;
	void merge(const extendedarrayQueue<T>& q1, const extendedarrayQueue<T>& q2);
};

template<typename T>
void extendedarrayQueue<T>::merge(const extendedarrayQueue<T>& q1, const extendedarrayQueue<T>& q2)
{
	delete[] this->queue;
	this->queue = new T[q1.size() + q2.size() + 1];
	this->theFront = this->theBack = 0;

	auto font1 = q1.theFront, font2 = q2.theFront;
	for (int i = 1; font1 != q1.theBack && font2 != q2.theBack; ++i)
	{
		if (i % 2)
		{
			this->push(q1.queue[(font1 + 1) % q1.arrayLength]);
			font1 = (font1 + 1) % q1.arrayLength;
		}
		else
		{
			this->push(q2.queue[(font2 + 1) % q2.arrayLength]);
			font2 = (font2 + 1) % q2.arrayLength;
		}
	}
	while (font1 != q1.theBack)
	{
		this->push(q1.queue[(font1 + 1) % q1.arrayLength]);
		font1 = (font1 + 1) % q1.arrayLength;
	}
	while (font2 != q2.theBack)
	{
		this->push(q2.queue[(font2 + 1) % q2.arrayLength]);
		font2 = (font2 + 1) % q2.arrayLength;
	}
}

template<typename T>
void extendedarrayQueue<T>::split(extendedarrayQueue<T>& oddQ, extendedarrayQueue<T>& evenQ) const
{
	auto font = this->theFront, back = this->theBack;
	int i = 1;
	while (font != back)
	{
		if (i % 2)
			oddQ.push(this->queue[(font + 1) % this->arrayLength]);
		else
			evenQ.push(this->queue[(font + 1) % this->arrayLength]);
		font = (font + 1) % this->arrayLength;
		++i;
	}
}

template<typename T>
void extendedarrayQueue<T>::input(std::istream& in)
{
	T t;
	while (in >> t)
		this->push(t);
}

template<typename T>
void extendedarrayQueue<T>::output(std::ostream& out) const
{
	auto font = this->theFront, back = this->theBack;
	while (font != back)
	{
		out << this->queue[(font + 1) % this->arrayLength] << " ";
		font = (font + 1) % this->arrayLength;
	}
}

template<typename T>
std::istream& operator>>(std::istream& in, extendedarrayQueue<T>& q)
{
	q.input(in);
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, extendedarrayQueue<T>& q)
{
	q.output(out);
	return out;
}

std::istream& operator>>(std::istream& in, extendedarrayQueue<int>& q)
{
	q.input(in);
	return in;
}

std::ostream& operator<<(std::ostream& out, extendedarrayQueue<int>& q)
{
	q.output(out);
	return out;
}
#endif // !extendedarrayQueue_
