
#ifndef extendedArrayStack_
#define extendedArrayStack_

#include "extendedStack.h"
#include "arrayStack.h"

template<typename T>
class extendedArrayStack :public arrayStack<T>, public extendedStack<T>
{
public:
	extendedArrayStack(int initialCapacity = 10) :arrayStack<T>::arrayStack(initialCapacity) {}
	~extendedArrayStack() {}
	bool empty() const { return arrayStack<T>::empty(); }
	int size() const { return arrayStack<T>::size(); }
	T& top() { return arrayStack<T>::top(); }
	void pop() { arrayStack<T>::pop(); }
	void push(const T& theElement) { arrayStack<T>::push(theElement); }
	void output(std::ostream& out) const { arrayStack<T>::output(out); }

	void input(std::istream& in);
	std::string to_string() const;
	void split(extendedArrayStack& a, extendedArrayStack& b) const;
	void append(extendedArrayStack& x);
};

template<typename T>
std::istream& operator>>(std::istream& in, extendedArrayStack<T>& x)
{
	x.input(in);
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, extendedArrayStack<T>& x)
{
	out << x.to_string();
	return out;
}

template<typename T>
void extendedArrayStack<T>::input(std::istream& in)
{
	std::cout << "Enter Ctrl+Z to stop:" << std::endl;
	T t;
	while (in >> t)
		push(t);
}

template<typename T>
std::string extendedArrayStack<T>::to_string() const
{
	std::ostringstream s;
	s << "top -> bottom: ";
	output(s);
	return s.str();
}

template<typename T>
void extendedArrayStack<T>::split(extendedArrayStack<T>& a, extendedArrayStack<T>& b) const
{
	int size = this->stackTop + 1;
	a.stackTop = b.stackTop = -1;
	for (int i = 0; i < size; ++i)
	{
		if (i < size / 2)
			a.push(this->stacks[i]);
		else
			b.push(this->stacks[i]);
	}
}

template<typename T>
void extendedArrayStack<T>::append(extendedArrayStack<T>& x)
{
	for (int i = 0; i < x.size(); ++i)
		arrayStack<T>::push(x.stacks[i]);
}


#endif
