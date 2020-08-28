
#ifndef MOVE_AND_LEFT_RIGHT_ON_CHAIN
#define MOVE_AND_LEFT_RIGHT_ON_CHAIN

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "myExceptions.h"
#include "chainNode.h"
#include "moveLeftAndRightLinearList.h"
#include "ex6_2-16_18_20_22_26_27_64_65.h"

template<typename T>
class moveLeftAndRightOnChain : public moveLeftAndRightLinearList<T>, public chain<T>
{
public:
	// constructor and copy constructor
	moveLeftAndRightOnChain(int initialCapacity = 10) :
		chain<T>(initialCapacity), p(nullptr),l(nullptr),currentElement(-1) {}
	moveLeftAndRightOnChain(const moveLeftAndRightOnChain<T>& c) :
		chain<T>(c)
	{
		currentElement = c.currentElement;
		resetToP();
	}
	~moveLeftAndRightOnChain() {}

	// ADT methods
	bool empty() const { return this->listSize == 0; }
	int size() const { return this->listSize; }
	T& get(int theIndex) const
	{
		return chain<T>::get(theIndex);
	}
	int indexOf(const T& theElement) const
	{
		return chain<T>::indexOf(theElement);
	}
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void clear()
	{// Delete all nodes in chain.
		while (this->firstNode != nullptr)
		{// delete firstNode
			chainNode<T>* nextNode = this->firstNode->next;
			delete this->firstNode;
			this->firstNode = nextNode;
		}
		this->listSize = 0;
		currentElement = -1;
		resetToP();
	}
	void output(std::ostream& out) const
	{
		chain<T>::output(out);
	}

	// moveLeftAndRight
	void reset() override
	{
		currentElement = 0;
		resetToP();
	}
	T& current() override { return p->element; }
	bool attend() override { return currentElement == this->size() - 1; }
	bool atFront() override { return p == this->firstNode; }
	void moveToNext() override
	{
		this->checkIndex(currentElement + 1);
		++currentElement;
		resetToP();
	}
	void moveToPrevious() override
	{
		this->checkIndex(currentElement - 1);
		--currentElement;
		resetToP();
	}

	//// operators
	//bool operator<=(const extendedChain& rhs) const;
	//bool operator>=(const extendedChain& rhs) const;
	//bool operator <(const extendedChain& rhs) const;
	//bool operator >(const extendedChain& rhs) const;
	//bool operator==(const extendedChain& rhs) const;
	//bool operator!=(const extendedChain& rhs) const;

protected:
	void resetToP()
	{
		if (currentElement == 0)
		{
			l = nullptr;
			p = this->firstNode;
			return;
		}
		if (currentElement == -1)
		{
			l = p = nullptr;
			return;
		}
		chainNode<T>* currentNode = this->firstNode;
		int i = 0;
		while (i++ < currentElement - 1)
			currentNode = currentNode->next;
		l = currentNode;
		p = currentNode->next;
	}
	int currentElement;			// the index of p
	chainNode<T>* p;			// p -> ... -> lastNode
	chainNode<T>* l;			// firstNode -> ... -> l -> p
};

template<typename T>
void moveLeftAndRightOnChain<T>::erase(int theIndex)
{
	// when p is the lastNode ,can't delete lastNode
	if (theIndex == currentElement && currentElement == this->size() - 1)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << this->listSize << " index must be < size - 1, the last element can't erase.";
		throw illegalIndex(s.str());
	}

	chain<T>::erase(theIndex);
	if (currentElement != -1 && theIndex < currentElement)
		--currentElement;
	if(theIndex <= currentElement)
		resetToP();
}

template<typename T>
void moveLeftAndRightOnChain<T>::insert(int theIndex, const T& theElement)
{
	chain<T>::insert(theIndex, theElement);
	if (currentElement != -1 && theIndex < currentElement)
		++currentElement;
	resetToP();
}

using namespace std;

void testEx_6_25()
{
	// test constructor
	moveLeftAndRightOnChain<double>* x = new moveLeftAndRightOnChain<double>;
	moveLeftAndRightOnChain<int> y, z;

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
	y.erase(0);
	cout << "Element 0 erased" << endl;
	cout << "The list is " << y << endl;

	cout << "Size of y = " << y.size() << endl;
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
	moveLeftAndRightOnChain<int> w(y);
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
	cout << endl;

	// test moveLeftAndRight
	x->insert(0, 4);
	x->insert(0, 5);
	x->insert(0, 6);
	x->insert(0, 7);
	cout << "x: " << *x << endl;
	cout << "y: " << y << endl;
	cout << "w: " << w << endl;
	x->reset();
	y.moveToNext();
	w.moveToNext();
	x->moveToNext();
	cout << "x->attend() is " << (x->attend() ? "true" : "false ") << endl;
	cout << "y.attend() is " << (y.attend() ? "true" : "false ") << endl;
	cout << "w.attend() is " << (y.attend() ? "true" : "false ") << endl;
	x->moveToNext();
	w.moveToNext();
	x->erase(2);
	y.erase(4);
	w.erase(0);
	y.moveToNext();
	w.moveToNext();
	cout << "x: " << *x << endl;
	cout << "y: " << y << endl;
	cout << "w: " << w << endl;
	cout << "x->current() is " << x->current() << endl;
	cout << "y.current() is " << y.current() << endl;
	cout << "w.current() is " << w.current() << endl;
	x->moveToPrevious();
	w.moveToPrevious();
	y.moveToPrevious();
	cout << "x->atFront() is " << (x->atFront() ? "true" : "false ") << endl;
	cout << "y.atFront() is " << (y.atFront() ? "true" : "false ") << endl;
	cout << "w.atFront() is " << (y.atFront() ? "true" : "false ") << endl;
	cout << "x->current() is " << x->current() << endl;
	cout << "y.current() is " << y.current() << endl;
	cout << "w.current() is " << w.current() << endl;
	cout << "x: " << *x << endl;
	cout << "y: " << y << endl;
	cout << "w: " << w << endl;
	x->reset();
	cout << "x->atFront() is " << (x->atFront() ? "true" : "false ") << endl;
}

#endif