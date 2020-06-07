
#ifndef extendedStack_
#define extendedStack_

#include <iostream>
#include "stack.h"

template<typename T>
class extendedStack : public stack<T>
{
public:
	~extendedStack() {}
	virtual void input(std::istream& in) = 0;
	virtual std::string to_string() const = 0;
};

#endif