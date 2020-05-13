// abstract class moveLeftAndRightLinearList

#ifndef moveLeftAndRightLinearList_
#define moveLeftAndRightLinearList_
#include <iostream>
#include "linearList.h"

template<typename T>
class moveLeftAndRightLinearList : linearList<T>
{
public:
	virtual ~moveLeftAndRightLinearList() {}
	virtual void reset() = 0;
	virtual T& current() = 0;
	virtual bool attend() = 0;
	virtual bool atFront() = 0;
	virtual void moveToNext() = 0;
	virtual void moveToPrevious() = 0;
};

#endif
