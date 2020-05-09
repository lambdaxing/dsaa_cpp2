// array implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// code does not use STL algorithms

#ifndef arrayListNoSTL_
#define arrayListNoSTL_

#include<iostream>
#include<sstream>
#include<string>
#include "linearList.h"
#include "myExceptions.h"
#include "changeLength1D.h"

template<class T>
class arrayListNoSTL : public linearList<T>
{
public:
	// constructor, copy constructor and destructor
	arrayListNoSTL(int initialCapacity = 10);
	arrayListNoSTL(const arrayListNoSTL<T>&);
	~arrayListNoSTL() { delete[] element; }

	// ADT methods
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	// additional method
	int capacity() const { return arrayLength; }

protected:
	void checkIndex(int theIndex) const;
	// throw illegalIndex if theIndex invalid
	T* element;            // 1D array to hold list elements
	int arrayLength;       // capacity of the 1D array
	int listSize;          // number of elements in list
};

template<class T>
arrayListNoSTL<T>::arrayListNoSTL(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<class T>
arrayListNoSTL<T>::arrayListNoSTL(const arrayListNoSTL<T>& theList)
{// Copy constructor.
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];

	// copy the list elements
	for (int i = 0; i < listSize; i++)
		element[i] = theList.element[i];
}

template<class T>
void arrayListNoSTL<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

}

template<class T>
T& arrayListNoSTL<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);
	return element[theIndex];
}

template<class T>
int arrayListNoSTL<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search for theElement
	for (int i = 0; i < listSize; i++)
		if (element[i] == theElement) return i;

	// theElement not found
	return -1;
}

template<class T>
void arrayListNoSTL<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// valid index, shift elements with higher index
	for (int i = theIndex + 1; i < listSize; i++)
		element[i - 1] = element[i];

	element[--listSize].~T();  // destructor for T
}

template<class T>
void arrayListNoSTL<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	// valid index, make sure we have space
	if (listSize == arrayLength)
	{// no space, double capacity
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	// shift elements right one position
	for (int i = listSize - 1; i >= theIndex; i--)
		element[i + 1] = element[i];

	element[theIndex] = theElement;

	listSize++;
}

template<class T>
void arrayListNoSTL<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	for (int i = 0; i < listSize; i++)
		out << element[i] << "  ";
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const arrayListNoSTL<T>& x)
{
	x.output(out); return out;
}

using namespace std;

int testArrayListNoSTL()
{
	// test constructor
	linearList<double>* x = new arrayListNoSTL<double>(20);
	arrayListNoSTL<int> y(2), z;

	// test capacity
	cout << "Capacity of x, y and z = "
		<< ((arrayListNoSTL<double>*) x)->capacity() << ", "
		<< y.capacity() << ", "
		<< z.capacity() << endl;


	// test size
	cout << "Initial size of x, y, and z = "
		<< x->size() << ", "
		<< y.size() << ", "
		<< z.size() << endl;

	// test empty
	if (x->empty()) cout << "x is empty" << endl;
	else cout << "x is not empty" << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;

	// test insert
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;
	y.output(cout);
	cout << endl << "Testing overloaded <<" << endl;
	cout << y << endl;

	// test indexOf
	int index = y.indexOf(4);
	if (index < 0) cout << "4 not found" << endl;
	else cout << "The index of 4 is " << index << endl;

	index = y.indexOf(7);
	if (index < 0) cout << "7 not found" << endl;
	else cout << "The index of 7 is " << index << endl;

	// test get
	cout << "Element with index 0 is " << y.get(0) << endl;
	cout << "Element with index 3 is " << y.get(3) << endl;

	// test erase
	y.erase(1);
	cout << "Element 1 erased" << endl;
	cout << "The list is " << y << endl;
	y.erase(2);
	cout << "Element 2 erased" << endl;
	cout << "The list is " << y << endl;

	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;

	try { y.insert(-3, 0); }
	catch (illegalIndex e)
	{
		cout << "Illegal index exception" << endl;
		cout << "Insert index must be between 0 and list size" << endl;
		e.outputMessage();
	}

	// test copy constructor
	arrayListNoSTL<int> w(y);
	y.erase(0);
	y.erase(0);
	cout << "w should be old y, new y has first 2 elements removed" << endl;
	cout << "w is " << w << endl;
	cout << "y is " << y << endl;

	// a few more inserts, just for fun
	y.insert(0, 4);
	y.insert(0, 5);
	y.insert(0, 6);
	y.insert(0, 7);
	cout << "y is " << y << endl;
	return 0;
}
#endif
