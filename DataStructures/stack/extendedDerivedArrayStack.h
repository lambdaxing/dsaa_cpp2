
#ifndef extendedDerivedArrayStack_
#define extendedDerivedArrayStack_

#include "extendedStack.h"
#include "derivedArrayStackWithCatch.h"

template<typename T>
class extendedDerivedArrayStack : protected derivedArrayStackWithCatch<T>, public extendedStack<T>
{
public:
	extendedDerivedArrayStack(int initialCapacity = 10) : derivedArrayStackWithCatch<T>(initialCapacity) {}
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
		try {
			arrayList<T>::erase(arrayList<T>::size() - 1);
		}
		catch (illegalIndex)
		{
			throw stackEmpty();
		}
	}
	void push(const T& theElement)
	{
		arrayList<T>::insert(arrayList<T>::size(), theElement);
	}

	void input(std::istream& in);
	std::string to_string() const;
	void split(extendedDerivedArrayStack& a, extendedDerivedArrayStack& b) const;
	void append(extendedDerivedArrayStack& x);
};

template<typename T>
std::istream& operator>>(std::istream& in, extendedDerivedArrayStack<T>& x)
{
	x.input(in); 
	return in;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, extendedDerivedArrayStack<T>& x)
{
	out << x.to_string();
	return out;
}

template<typename T>
void extendedDerivedArrayStack<T>::input(std::istream& in)
{
	std::cout << "Enter Ctrl+Z to stop:" << std::endl;
	T t;
	while(in >> t)
		derivedArrayStackWithCatch<T>::push(t);
}

template<typename T>
std::string extendedDerivedArrayStack<T>::to_string() const
{
	std::ostringstream s;
	s << "top -> bottom: ";
	arrayList<T>::output(s);
	return s.str();
}

template<typename T>
void extendedDerivedArrayStack<T>::split(extendedDerivedArrayStack<T>& a, extendedDerivedArrayStack<T>& b) const
{
	int size = derivedArrayStackWithCatch<T>::size();
	a.listSize = b.listSize = 0;
	for (int i = 0; i < size; ++i)
	{
		if (i < size / 2)
			a.push(this->element[i]);
		else
			b.push(this->element[i]);
	}
}

template<typename T>
void extendedDerivedArrayStack<T>::append(extendedDerivedArrayStack<T>& x)
{
	for (int i = 0; i < x.size(); ++i)
		derivedArrayStackWithCatch<T>::push(x.element[i]);
}

#endif