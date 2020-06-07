
#ifndef extendedLinkedStack_
#define extendedLinkedStack_

#include "linkedStack.h"
#include "extendedStack.h"

template<typename T>
class extendedLinkedStack :public linkedStack<T>, public extendedStack<T>
{
public:
	extendedLinkedStack(int initialCapacity = 10) :linkedStack<T>(initialCapacity) {}
	~extendedLinkedStack() {}
	bool empty() const { return linkedStack<T>::empty(); }
	int size() const { return linkedStack<T>::size(); }
	T& top() { return linkedStack<T>::top(); }
	void pop() { linkedStack<T>::pop(); }
	void push(const T& theElement) { linkedStack<T>::push(theElement); }
	void pushNode(chainNode<T>* theNode) { linkedStack<T>::pushNode(theNode); }
	chainNode<T>* popNode() { return linkedStack<T>::popNode(); }
	void output(std::ostream& out) const { linkedStack<T>::output(out); }

	void input(std::istream& in);
	std::string to_string() const;
};


template<typename T>
std::istream& operator>>(std::istream& in, extendedLinkedStack<T>& x)
{
	x.input(in);
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, extendedLinkedStack<T>& x)
{
	out << x.to_string();
	return out;
}

template<typename T>
void extendedLinkedStack<T>::input(std::istream& in)
{
	std::cout << "Enter Ctrl+Z to stop:" << std::endl;
	T t;
	while (in >> t)
		push(t);
}

template<typename T>
std::string extendedLinkedStack<T>::to_string() const
{
	std::ostringstream s;
	s << "top -> bottom: ";
	output(s);
	return s.str();
}

#endif