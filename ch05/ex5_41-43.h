// m linearLists in one array

#ifndef mArrayList_
#define mArrayList_

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "myExceptions.h"
#include "changeLength1D.h"

template<typename T>
class mArrayList
{
public:
	mArrayList(int theM = 10, int initialCapacity = 10);
	mArrayList(const mArrayList&);
	~mArrayList() { delete[] element; delete[] front; delete[] last; }

	bool empty(int i) const { checkI(i); return front[i] == last[i]; }
	int size(int i) const { checkI(i); return last[i] - front[i]; }
	int sizeOfList() const { return m; }
	T& get(int i, int theIndex) const { checkIndex(i, theIndex); return element[front[i] + 1 + theIndex]; }
	int indexOf(int i, const T& theElement) const;
	void erase(int i, int theIndex);
	void insert(int i, int theIndex, const T& theElement);
	void output(int i, std::ostream& out)const;

private:
	// Check the index of the tables
	void checkI(int i) const;
	// Check the index of the table and the element
	void checkIndex(int i, int theIndex) const;
	T* element;						// 1D array to hold all lists' elements
	int* front, * last;				// front[i] is first element's index of list i in the element; last[i] is last element's index of list i in the element

	int m,arrayLength, alSize;		// m is the number of lists and the range of i is 1~m
	// arrayLength is capacity of the 1D array
	// alSize is number of elements in all lists
};

template<typename T>
mArrayList<T>::mArrayList(int theM /* = 10 */, int initialCapacity /* = 10*/)
{
	if (theM < 1 || initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " and the number of arrayLists = " << theM << " Must be > 0";
		throw illegalParameterValue(s.str());
	}

	m = theM;
	arrayLength = (m * initialCapacity) + 2;		// 2 for the border list
	element = new T[arrayLength];
	front = new int[m + 2];
	last = new int[m + 2];

	front[0] = last[0] = -1;
	front[m + 1] = last[m + 1] = arrayLength - 1;
	for (int i = 1; i < m + 1; ++i)
		front[i] = last[i] = (i - 1) * initialCapacity;

	alSize = 2;		// already used in elment: element[0] and element[arrayLength-1]
}

template<typename T>
mArrayList<T>::mArrayList(const mArrayList& x)
{
	m = x.m;
	arrayLength = x.arrayLength;
	alSize = x.alSize;

	element = new T[arrayLength];
	front = new int[m + 2];
	last = new int[m + 2];

	std::copy(x.element, x.element + x.arrayLength, element);
	std::copy(x.front, x.front + x.m + 2, front);
	std::copy(x.last, x.last + x.m + 2, last);	
}

template<typename T>
void mArrayList<T>::checkI(int i) const
{// Verify that theIndex of m list is between 1 and m.
	if (i < 1 || i > m)
	{
		std::ostringstream s;
		s << "i = " << i << " num of lists = " << m;
		throw illegalIndex(s.str());
	}
}

template<typename T>
void mArrayList<T>::checkIndex(int i, int theIndex) const
{
	// Verify that theIndex is between 0 and last[i] - front[i].
	if (theIndex < 0 || theIndex > size(i) - 1)		// there will be checkI(i)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << last[i] - front[i];
		throw illegalIndex(s.str());
	}
}

template<typename T>
int mArrayList<T>::indexOf(int i, const T& theElement) const
{
	checkI(i);

	int theIndex = static_cast<int>(std::find(element + front[i] + 1, element + last[i] + 1, theElement) - (element + front[i] + 1));

	// check if theElement was found
	if (theIndex == size(i))
		return -1;		// not found
	else
		return theIndex;
}

template<typename T>
void mArrayList<T>::erase(int i, int theIndex)
{
	checkIndex(i, theIndex);

	// valid index, shift elements with higher index
	std::copy(element + front[i] + 1 + theIndex + 1, element + last[i] + 1, element + front[i] + 1 + theIndex);

	element[last[i]--].~T();	// invoke destructor
}

template<typename T>
void mArrayList<T>::insert(int i, int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > size(i))		// there will be checkI(i)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << last[i] - front[i];
		throw illegalIndex(s.str());
	}

	if (alSize == arrayLength)
	{
		// no space, double capacity
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;

		front[m + 1] = last[m + 1] = arrayLength - 1;
	}

	// 有空间的表的序号
	int hasSpaceM = i;
	// 向右寻找有空间的表
	while (hasSpaceM != m + 1 && last[hasSpaceM] == front[hasSpaceM + 1])
		++hasSpaceM;

	// found list that has space at right
	if (hasSpaceM != m + 1)
	{
		// 向右移动腾出插入元素的位置
		std::copy_backward(element + front[i] + 1 + theIndex, element + last[hasSpaceM] + 1, element + last[hasSpaceM] + 2);

		element[front[i] + 1 + theIndex] = theElement;
		++last[i];

		// 更新移动了的表的序号 add 1
		for (int j = i + 1; j <= hasSpaceM; ++j)
			++front[j], ++last[j];
	}
	else // not found, and found at left
	{
		hasSpaceM = i;
		// 向左寻找有空间的表
		while (hasSpaceM != 0 && last[hasSpaceM - 1] == front[hasSpaceM])
			--hasSpaceM;

		if (hasSpaceM == 0)
		{// 左右均未找到有空间的表，按理说进行了扩容不会存在此种情况，为防万一，抛出异常
			throw std::runtime_error("programe logical error:发生了不会出现的情况！");
		}
		else
		{// found list that has space at left
			// 向左移动元素腾出插入位置
			std::copy(element + front[hasSpaceM] + 1, element + front[i] + 1 + theIndex, element + front[hasSpaceM]);

			element[front[i] + 1 + theIndex] = theElement;
			--front[i];

			// 更新移动了的表的序号,表 hasSpaceM 前(left)有空间 
			for (int j = hasSpaceM; j < i; ++j)
				--front[j], --last[j];
		}
	}

	++alSize;
}

template<typename T>
void mArrayList<T>::output(int i, std::ostream& out) const
{
	checkI(i);
	std::copy(element + front[i] + 1, element + last[i] + 1, std::ostream_iterator<T>(out, " "));
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const mArrayList<T>& x)
{
	for (int i = 1; i <= x.sizeOfList(); ++i)
	{
		out << "list " << i << ": ";
		x.output(i, out);
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const mArrayList<int>& x)
{
	for (int i = 1; i <= x.sizeOfList(); ++i)
	{
		out << "list " << i << ": " << std::endl;
			x.output(i, out);
		out << std::endl;
	}
	return out;
}

void testMArrayList()
{
	mArrayList<int> m1(17, 100);
	mArrayList<int> m2;

	for (int i = 1; i <= 17; ++i)
		for (int j = 0; j < 1000; ++j)
			m1.insert(i, j, j);

	for (int i = 1; i <= 10; ++i)
		for (int j = 0; j < 1000; ++j)
			m2.insert(i, j, j);

	mArrayList<int> m3(m1);

	std::cout << "m3.empty(1): " << m3.empty(1) << std::endl;
	std::cout << "m3.size(2):  " << m3.size(2) << std::endl;
	std::cout << "m3.get(3, 3): " << m3.get(3, 3) << std::endl;
	std::cout << "m3.indexOf(4,5): " << m3.indexOf(4, 5) << std::endl;

	m3.erase(5, 88);
	while (m3.size(5) < 2000)
		m3.insert(5, 1, 1);
	m3.insert(6, 10, 10);
	m2.erase(5, 88);
	std::cout << "m3.output(5): ";
	m3.output(5, std::cout);
	std::cout << std::endl;
	std::cout << "m2.output(5): ";
	m2.output(5, std::cout);
	std::cout << std::endl;
	std::cout << m1 << std::endl << m2 << std::endl << m3 << std::endl;

}
#endif // !mArrayList_
