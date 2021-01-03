// change the length of an array

#ifndef changeLength1D_
#define changeLength1D_

#include "myExceptions.h"

template <typename T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >= 0");

	T* temp = new T[newLength];
	int number = std::min(oldLength, newLength);
	std::copy(a, a + number, temp);
	delete[] a;
	a = temp;
}

#endif