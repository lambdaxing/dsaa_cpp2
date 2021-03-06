// linked implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// unidirectional iterator for chain included

#ifndef chain_
#define chain_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include "linearList.h"
#include "chainNode.h"
#include "myExceptions.h"
#include "arrayList.h"

template<class T>
class chain : public linearList<T>
{
public:
	// constructor, copy constructor and destructor
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	// ADT methods
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

	void clear()
	{// Delete all nodes in chain.
		while (firstNode != nullptr)
		{// delete firstNode
			chainNode<T>* nextNode = firstNode->next;
			delete firstNode;
			firstNode = nextNode;
		}
		this->listSize = 0;
	}

	// ex6_2
	void setSize(int theSize);
	// ex6_3
	void set(int theIndex, const T& theElement);
	// ex6_4
	void removeRange(int fromIndex, int toIndex);
	// ex6_5
	int lastIndexOf(const T& theElement);
	// ex6_6
	T& operator[](int i);
	// ex6_7
	bool operator==(const chain& rhs) const;
	// ex6_8
	bool operator!=(const chain& rhs) const;
	// ex6_9
	bool operator <(const chain& rhs) const;
	bool operator>=(const chain& rhs) const;
	bool operator >(const chain& rhs) const;
	bool operator<=(const chain& rhs) const;

	// ex6_10
	void swap(chain& theChain);
	// ex6_13
	void fromList(const arrayList<T>& theList);
	arrayList<T> toList() const;
	// ex6_14
	void leftShift(std::size_t i);
	// ex6_15 ex6_16	https://leetcode-cn.com/problems/reverse-linked-list/solution/fan-zhuan-lian-biao-by-leetcode/
	void reverse();
	void recursionReverse();
	// ex6_18
	void meld(chain& a, chain& b);
	// ex6_22
	void split(chain& a, chain& b);
	void splitBeEmpty(chain& a, chain& b);
	// ex6_26_27
	void insertSort();
	void bubbleSort();
	chainNode<T>* nodeOfMin();
	void selectionSort();
	void rank(int*&);
	void rankSort();

	// ex6_64_65
	void binSort(int range, int digit);		// overload for radixSort
	void radixSort(int r, int d);			// r is cardinal number, d is digital number, integers between 0 and pow(r,c) - 1  
	void radixSort();					// c is the digit number , sort n integers between 0 and pow(n,c) - 1, n is cardinal number in this method

	// iterators to start and end of list
	class iterator;
	iterator begin() { return iterator(firstNode); }
	const iterator cbegin() const { return iterator(firstNode); }
	iterator end() { return iterator(nullptr); }
	const iterator cend() const { return iterator(nullptr); }

	// iterator for chain
	class iterator
	{
	public:
		// typedefs required by C++ for a forward iterator
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		typedef const iterator const_iterator;

		// constructor
		iterator(chainNode<T>* theNode = nullptr)
		{
			node = theNode;
		}

		// dereferencing operators
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		// increment
		iterator& operator++()   // preincrement
		{
			node = node->next; return *this;
		}
		iterator operator++(int) // postincrement
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		// equality testing
		bool operator!=(const iterator right) const
		{
			return node != right.node;
		}
		bool operator==(const iterator right) const
		{
			return node == right.node;
		}
	protected:
		chainNode<T>* node;
	};  // end of iterator class

protected:
	void checkIndex(int theIndex) const;
	// throw illegalIndex if theIndex invalid
	chainNode<T>* firstNode;  // pointer to first node in chain
	int listSize;             // number of elements in list
};

template<typename T>
chain<T>::chain(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	firstNode = nullptr;
	listSize = 0;
}

template<typename T>
chain<T>::chain(const chain<T>& theList)
{// Copy constructor.
	listSize = theList.listSize;

	if (listSize == 0)
	{// theList is empty
		firstNode = nullptr;
		return;
	}

	// non-empty list
	chainNode<T>* sourceNode = theList.firstNode;
	// node in theList to copy from
	firstNode = new chainNode<T>(sourceNode->element);
	// copy first element of theList
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
	// current last node in *this
	while (sourceNode != nullptr)
	{// copy remaining elements
		targetNode->next = new chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = nullptr; // end the chain
}

template<typename T>
chain<T>::~chain()
{// Chain destructor. Delete all nodes in chain.
	chainNode<T>* nextNode;
	while (firstNode != nullptr)
	{// delete firstNode
		nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<typename T>
void chain<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}
}

template<typename T>
T& chain<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// move to desired node
	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
		currentNode = currentNode->next;

	return currentNode->element;
}

template<typename T>
int chain<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // search the chain for theElement
	chainNode<T>* currentNode = firstNode;
	int index = 0;  // index of currentNode
	while (currentNode != nullptr &&
		currentNode->element != theElement)
	{
		// move to next node
		currentNode = currentNode->next;
		++index;
	}

	// make sure we found matching element
	if (currentNode == nullptr)
		return -1;
	else
		return index;
}

template<typename T>
void chain<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);

	// valid index, locate node with element to delete
	chainNode<T>* deleteNode;
	if (theIndex == 0)
	{// remove first node from chain
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{  // use p to get to predecessor of desired node
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		deleteNode = p->next;
		p->next = p->next->next; // remove deleteNode from chain
	}
	--listSize;
	delete deleteNode;
}

template<typename T>
void chain<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)
		// insert at front
		firstNode = new chainNode<T>(theElement, firstNode);
	else
	{  // find predecessor of new element
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		// insert after p
		p->next = new chainNode<T>(theElement, p->next);
	}
	++listSize;
}

template<typename T>
void chain<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	for (chainNode<T>* currentNode = firstNode;
		currentNode != nullptr;
		currentNode = currentNode->next)
		out << currentNode->element << " ";
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x)
{
	x.output(out); return out;
}

template<typename T>
void chain<T>::setSize(int theSize)
{
	if (theSize < 0)
	{
		std::ostringstream s;
		s << "theSize = " << theSize << " Must be >= 0 " << listSize;
		throw illegalIndex(s.str());
	}

	if (listSize <= theSize)
		return;

	chainNode<T>* currentNode = firstNode;
	chainNode<T>* temp;
	if (theSize == 0)
	{
		currentNode = firstNode->next;
		delete firstNode;
		firstNode = nullptr;
	}
	else
	{
		for (int i = 0; i < theSize - 1; ++i)
			currentNode = currentNode->next;
		temp = currentNode->next;
		currentNode->next = nullptr;
		currentNode = temp;
	}

	while (currentNode != nullptr)
	{
		temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	listSize = theSize;
}

template<typename T>
void chain<T>::set(int theIndex, const  T& theElement)
{
	checkIndex(theIndex);

	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; ++i)
		currentNode = currentNode->next;
	currentNode->element = theElement;
}

template<typename T>
void chain<T>::removeRange(int fromIndex, int toIndex)
{
	checkIndex(fromIndex); checkIndex(toIndex);
	if (fromIndex > toIndex)
	{
		std::ostringstream s;
		s << "fromIndex = " << fromIndex << " toIndex = " << toIndex;
		throw illegalIndex(s.str());
	}

	chainNode<T>* currentNode = firstNode;
	chainNode<T>* temp;
	chainNode<T>* preFormNode = firstNode;
	for (int i = 0; i < toIndex; ++i)
	{
		if (i > fromIndex - 1)
		{
			temp = currentNode->next;
			delete currentNode;
			currentNode = temp;
			continue;
		}
		if (i == fromIndex - 1)
			preFormNode = currentNode;
		currentNode = currentNode->next;
	}
	if (fromIndex == 0)
		firstNode = currentNode->next;
	else
		preFormNode->next = currentNode->next;
	delete currentNode;
	listSize -= (toIndex - fromIndex + 1);
}

template<typename T>
int chain<T>::lastIndexOf(const T& theElement)
{
	chainNode<T>* currentNode = firstNode;
	int theIndex = -1;
	int currentIndex = 0;
	while (currentNode != nullptr)
	{
		if (currentNode->element == theElement)
			theIndex = currentIndex;
		currentNode = currentNode->next;
		++currentIndex;
	}
	return theIndex;
}

template<typename T>
T& chain<T>::operator[](int i)
{
	checkIndex(i);
	chainNode<T>* currentNode = firstNode;
	while (i--)
		currentNode = currentNode->next;
	return currentNode->element;
}

template<typename T>
bool chain<T>::operator ==(const chain<T>& rhs) const
{
	if (listSize != rhs.listSize)
		return false;

	chainNode<T>* currentNodeLhs = firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != nullptr)
		if (currentNodeLhs->element != currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return true;
}

template<typename T>
bool chain<T>::operator !=(const chain<T>& rhs) const
{
	return !(*this == rhs);
}

template<typename T>
bool chain<T>::operator >=(const chain<T>& rhs) const
{
	chainNode<T>* currentNodeLhs = firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != nullptr && currentNodeLhs != nullptr)
		if (currentNodeLhs->element < currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return currentNodeRhs == nullptr;
}

template<typename T>
bool chain<T>::operator <=(const chain<T>& rhs) const
{
	chainNode<T>* currentNodeLhs = firstNode;
	chainNode<T>* currentNodeRhs = rhs.firstNode;
	while (currentNodeRhs != nullptr && currentNodeLhs != nullptr)
		if (currentNodeLhs->element > currentNodeRhs->element)
			return false;
		else {
			currentNodeRhs = currentNodeRhs->next;
			currentNodeLhs = currentNodeLhs->next;
		}
	return currentNodeLhs == nullptr;
}

template<typename T>
bool chain<T>::operator <(const chain<T>& rhs) const
{
	return !(*this >= rhs);
}

template<typename T>
bool chain<T>::operator >(const chain<T>& rhs) const
{
	return !(*this <= rhs);
}

template<typename T>
void chain<T>::swap(chain& theChain)
{
	using  std::swap;
	swap(firstNode, theChain.firstNode);
	swap(listSize, theChain.listSize);
}

// ex6_11
template<typename T>
chain<T> arrayToChain(const arrayList<T>& aList)
{
	chain<T> cList;
	for (int i = 0; i < aList.size(); ++i)
		cList.insert(i, aList.get(i));
	return cList;
}

// ex6_12
template<typename T>
arrayList<T> chainToArray1(const chain<T>& cList)
{
	arrayList<T> aList(cList.size());
	for (int i = 0; i < cList.size(); ++i)
		aList.insert(i, cList.get(i));
	return aList;
}

template<typename T>
arrayList<T> chainToArray2(const chain<T>& cList)
{
	auto cb = cList.cbegin();
	auto ce = cList.cend();
	arrayList<T> aList(cList.size());
	int i = 0;
	while (cb != cList.cend())
		aList.insert(i++, *cb++);
	return aList;
}

template<typename T>
void chain<T>::fromList(const arrayList<T>& theList)
{
	int i;
	for (i = 0; i < theList.size(); ++i)
		insert(i, theList.get(i));
	
	chainNode<T>* currentNode = firstNode;
	chainNode<T>* temp = firstNode;
	while (i-- > 0) {
		if (temp != currentNode)
			temp = currentNode;				// save preNode
		currentNode = currentNode->next;
	}
	temp->next = nullptr;					// lastNode->next = nullptr

	while (currentNode != nullptr)
	{
		temp = currentNode->next;
		delete currentNode;
		currentNode = temp;
	}
	listSize = theList.size();
}

template<typename T>
arrayList<T> chain<T>::toList() const
{
	arrayList<T> aList(listSize);
	chainNode<T>* currentNode = firstNode;
	int i = 0;
	while (currentNode != nullptr)
	{
		aList.insert(i++, currentNode->element);
		currentNode = currentNode->next;
	}
	return aList;
}

template<typename T>
void chain<T>::leftShift(std::size_t i)
{
	chainNode<T>* nextNode = firstNode;
	while (i--)
	{
		if (firstNode == nullptr)
			break;
		nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
	listSize = ((listSize - i > 0) ? listSize - i : 0);
}

template<typename T>
void chain<T>::reverse()
{	
	chainNode<T>* currentNode = firstNode;
	chainNode<T>* preCurrentNode = nullptr;
	chainNode<T>* temp;
	while (currentNode != nullptr)
	{
		temp = currentNode->next;
		currentNode->next = preCurrentNode;
		preCurrentNode = currentNode;
		currentNode = temp;
	}
	firstNode = preCurrentNode;
}

template<typename T>
void chain<T>::recursionReverse()
{
	if (firstNode == nullptr || firstNode->next == nullptr)
		return;
	chainNode<T>* currentNode = firstNode;
	firstNode = firstNode->next;
	recursionReverse();
	currentNode->next->next = currentNode;
	currentNode->next = nullptr;
}

// ex6_16
template<typename T>
void reverse(chain<T>& theList)
{
	using std::swap;
	for (int i = 0; i < theList.size() / 2; ++i)
		swap(theList[i], theList[theList.size() - 1 - i]);
}

template<typename T>
void chain<T>::meld(chain& a, chain& b)
{
	if (&a == this || &b == this)
	{
		std::ostringstream s;
		s << " can't meld chain<T> self ";
		throw illegalParameterValue(s.str());
	}
	chainNode<T>* aCurrentNode = a.firstNode;
	chainNode<T>* bCurrentNode = b.firstNode;
	clear();
	if (aCurrentNode == nullptr && bCurrentNode == nullptr)
		return;
	if (aCurrentNode != nullptr)
		firstNode = aCurrentNode;
	else
		firstNode = bCurrentNode;

	chainNode<T>* currentNode = firstNode;
	chainNode<T>* nextNode = nullptr;
	int i = 0;

	while (aCurrentNode != nullptr || bCurrentNode != nullptr)
	{
		if (bCurrentNode != nullptr && i % 2 || aCurrentNode == nullptr && bCurrentNode != nullptr)
		{
			nextNode = bCurrentNode->next;
			currentNode->next = bCurrentNode;
			bCurrentNode = nextNode;
		}
		else
		{
			nextNode = aCurrentNode->next;
			currentNode->next = aCurrentNode;
			aCurrentNode = nextNode;
		}
		currentNode = currentNode->next;
		++i;
	}
	currentNode->next = nullptr;
	if (a.firstNode != nullptr)
		a.firstNode = nullptr;
	if (b.firstNode != nullptr)
		b.firstNode = nullptr;
	listSize = i - 1;
	a.listSize = 0;
	b.listSize = 0;
}

template<typename T>
void chain<T>::split(chain& a, chain& b)
{
	a.clear(); b.clear();
	int i = 0; int j = 0; int k = 0;
	chainNode<T>* currentNode = firstNode;
	while (currentNode != nullptr)
	{
		if (i++ % 2) a.insert(j++, currentNode->element);
		else b.insert(k++, currentNode->element);
		currentNode = currentNode->next;
	}
}

template<typename T>
void chain<T>::splitBeEmpty(chain& a, chain& b)
{
	a.clear(); b.clear();
	chainNode<T>* currentNode = firstNode;
	chainNode<T>* aCurrentNode = a.firstNode;
	chainNode<T>* aPreCurrentNode = nullptr;
	chainNode<T>* bCurrentNode = b.firstNode;
	chainNode<T>* bPreCurrentNode = nullptr;
	int i = 0;
	while (currentNode != nullptr)
	{
		if (i % 2)
		{
			aCurrentNode = currentNode;
			if (i == 1) 
				a.firstNode = aCurrentNode;
			else
				aPreCurrentNode->next = aCurrentNode;
			aPreCurrentNode = aCurrentNode;
			aCurrentNode = aCurrentNode->next;
		}
		else 
		{
			bCurrentNode = currentNode;
			if (i == 0) 
				b.firstNode = bCurrentNode;
			else
				bPreCurrentNode->next = bCurrentNode;
			bPreCurrentNode = bCurrentNode;
			bCurrentNode = bCurrentNode->next;
		}
		currentNode = currentNode->next;
		++i;
	}
	if(bPreCurrentNode != nullptr && bPreCurrentNode->next != nullptr)
		bPreCurrentNode->next = nullptr;
	if (aPreCurrentNode != nullptr && aPreCurrentNode->next != nullptr)
		aPreCurrentNode->next = nullptr;
	a.listSize = i / 2;
	b.listSize = (i + 1) / 2;
	listSize = 0;
	firstNode = nullptr;
}

template<typename T>
void chain<T>::insertSort()
{
	if (firstNode == nullptr || firstNode->next == nullptr)
		return;
	chainNode<T>* head = firstNode;
	chainNode<T>* head2 = head->next;	// the head of not sorted part 
	chainNode<T>* current = nullptr;
	chainNode<T>* p = nullptr;
	chainNode<T>* q = nullptr;

	head->next = nullptr;				// the head of already sorted part 

	while (head2)
	{
		current = head2;
		head2 = head2->next;

		// find the address of insert ??in the middle of p and q.
		for (q = head; q && q->element <= current->element; p = q, q = q->next);

		if (q == head)
		{
			// insert to the first
			head = current;
		}
		else
		{
			p->next = current;
		}
		current->next = q;
	}
	firstNode = head;
}

template<typename T>
void chain<T>::bubbleSort()
{
	chainNode<T>* p, * q, * tail;

	tail = nullptr;
	T t = {};
	chainNode<T>* temp = new chainNode<T>(t, firstNode);
	firstNode = temp;
	while ((firstNode->next) != tail)
	{
		p = firstNode;
		q = firstNode->next;
		while (q->next != tail)
		{
			if ((q->element) > (q->next->element))		// swap q and q->next
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = p->next;
			}
			q = q->next;
			p = p->next;
		}
		tail = q;
	}
	firstNode = temp->next;
	delete temp;
}

template<typename T>
chainNode<T>* chain<T>::nodeOfMin()
{
	if (firstNode == nullptr || firstNode->next == nullptr)
		return firstNode;
	chainNode<T>* minNode = firstNode;
	chainNode<T>* currentNode = firstNode;
	while (currentNode != nullptr)							// find the minNode from first to end
	{
		//std::cout << 1;
		if (currentNode->element < minNode->element)
			minNode = currentNode;
		currentNode = currentNode->next;
	}
	if (minNode != firstNode)								// minNode is not the firstNode
	{
		currentNode = firstNode;
		while (currentNode->next != minNode)
			currentNode = currentNode->next;
		currentNode->next = currentNode->next->next;		// remove the minNode in primary list ( not sorted)
	}
	else
		firstNode = minNode->next;							// minNode is the firstNode , remove it = update firstNode
	return minNode;
}

template<typename T>
void chain<T>::selectionSort()
{
	if (firstNode == nullptr || firstNode->next == nullptr)
		return;
	
	chainNode<T>* minNode = nodeOfMin();
	chainNode<T>* head = minNode;					// the head of already sorted 
	chainNode<T>* preNode = head;
	while (firstNode->next != nullptr)				// find the minNode between first and end , add it to the part of already sorted
	{
		//std::cout << 2;
		minNode = nodeOfMin();						
		preNode->next = minNode;					// join
		preNode = preNode->next;						 
	}
	preNode->next = firstNode;						// the last(max) node ,just last one firstNode
	firstNode = head;								// update firstNode
}

template<typename T>
void chain<T>::rank(int*& rankArray)
{
	int j;
	int i = 0;
	for (i = 0; i < listSize; ++i)
		rankArray[i] = 0;
	chainNode<T>* currentNode = firstNode;
	chainNode<T>* compareNode = nullptr;
	i = 0;
	while (currentNode != nullptr)
	{
		compareNode = currentNode->next;
		j = 1;
		while (compareNode != nullptr)
		{
			if (currentNode->element > compareNode->element)
				++rankArray[i];
			else
				++rankArray[i + j];
			compareNode = compareNode->next;
			++j;
		}
		currentNode = currentNode->next;
		++i;
	}
}

template<typename T>
void chain<T>::rankSort()
{
	using std::swap;
	int *rankArray = new int[listSize];
	rank(rankArray);
	chainNode<T>* b = nullptr;
	chainNode<T>* currentNode = firstNode;
	int i = 0;
	for (int i = 0; i < listSize; ++i)
		// get proper element to a[i]
		while (rankArray[i] != i)
		{
			int t = rankArray[i];
			swap(operator[](i), operator[](t));
			swap(rankArray[i], rankArray[t]);
		}
	delete[] rankArray;
}

// Theta(n+range)
template <typename T>
void chain<T>::binSort(int range, int digit)
{// Sort the nodes in the chain. The sort key is value(theElement).
   // create and initialize the bins
	chainNode<T>** bottom, ** top;
	bottom = new chainNode<T> * [range + 1];
	top = new chainNode<T> * [range + 1];
	for (int b = 0; b <= range; ++b)
		bottom[b] = nullptr;

	// distribute to bins
	for (; firstNode != nullptr; firstNode = firstNode->next)
	{
		int theBin = (firstNode->element % static_cast<int>(pow(range, digit))) / static_cast<int>(pow(range, digit - 1));	 // calculate the "digit" digit of this element (from the lowest(1) to the highest(d))
		if (bottom[theBin] == nullptr)		 // bin is empty
			bottom[theBin] = top[theBin] = firstNode;
		else
		{// bin not empty
			top[theBin]->next = firstNode;
			top[theBin] = firstNode;
		}
	}

	// collect from bins into sorted chain
	chainNode<T>* y = nullptr;
	for (int theBin = 0; theBin <= range; ++theBin)
		if (bottom[theBin] != nullptr)
		{// bin not empty
			if (y == nullptr)	// first nonempty bin
				firstNode = bottom[theBin];
			else    // not first nonempty bin
				y->next = bottom[theBin];
			y = top[theBin];
		}

	if (y != nullptr)
		y->next = nullptr;

	delete[] bottom;
	delete[] top;
}

template <typename T>
void chain<T>::radixSort(int r, int d)
{
	for (int i = 1; i <= d; i++)
		binSort(r, i);
}

template<typename T>
void chain<T>::radixSort()
{
	int n = size();
	int maxElement = getMaxToInt();					// pow(n,c) - 1 >= maxElement
	int c = static_cast<int>(std::log(maxElement + 1) / std::log(n) + 1);	// "+ 1" for round up to an integer

	int r = n;			// use n as the cardinal number
	int d = c;			// the number of digits calculated from cardinal n is the degree of binSort
	for (int i = 1; i <= d; i++)
		binSort(r, i);
}

void testEx6_2()
{
	chain<double> x;
	x.insert(0, 0);
	x.insert(1, 1);
	x.insert(2, 2);
	x.insert(3, 3);
	x.insert(4, 4);
	x.insert(5, 5);
	chain<double> y(x);
	std::cout << "x: " << x << std::endl;
	std::cout << "y: " << y << std::endl;

	// test setSize(int theSize)
	x.setSize(6);
	std::cout << "x.setSize(6): " << x << std::endl;
	x.setSize(1);
	std::cout << "x.setSize(1): " << x << std::endl;
	x.setSize(0);
	std::cout << "x.setSize(0): " << x << std::endl;

	// test set(theIndex,theElement)
	y.set(0, 1);
	y.set(1, 2);
	y.set(2, 3);
	y.set(3, 4);
	y.set(4, 5);
	y.set(5, 6);
	std::cout << "y.set(0,1)->y.set(5,6): " << y << std::endl;

	// test removeRnage(f,t)
	y.removeRange(0, 4);
	std::cout << "y.removeRange(0,4): " << y << std::endl;

	// test lastIndexOf(theElement)
	x.insert(0, 0);
	x.insert(1, 1);
	x.insert(2, 2);
	x.insert(3, 1);
	x.insert(4, 2);
	x.insert(5, 3);
	std::cout << "x: " << x << std::endl;
	std::cout << "x.lastIndexOf(2) = " << x.lastIndexOf(2) << std::endl;
	std::cout << "x.lastIndexOf(1) = " << x.lastIndexOf(1) << std::endl;
	std::cout << "x.lastIndexOf(4) = " << x.lastIndexOf(4) << std::endl;

	// test []
	std::cout << "x[0] = " << x[0] << std::endl;
	x[1] = x[0];
	std::cout << "x[1] = x[0] = " << x[1] << std::endl;
	std::cout << "x[5] = " << x[5] << std::endl;

	// test == != <
	chain<double> z(x);
	std::cout << "x: " << x << std::endl;
	std::cout << "y: " << y << std::endl;
	std::cout << "z: " << z << std::endl;
	std::cout << "x != y is " << (x != y ? "true" : "false") << std::endl;
	std::cout << "x == z is " << (x == z ? "true" : "false") << std::endl;
	z[5] = 5;
	std::cout << "z: " << z << std::endl;
	std::cout << "x < z is " << (x < z ? "true" : "false") << std::endl;

	// test swap
	x.swap(y);
	std::cout << "x.swap(y):" << std::endl;
	std::cout << "x: " << x << std::endl;
	std::cout << "y: " << y << std::endl;

	// test arrayToChain
	arrayList<double> am;
	am.insert(0, 0);
	am.insert(1, 1);
	am.insert(2, 2);
	chain<double> cm = arrayToChain(am);
	std::cout << "am: " << am << std::endl;
	std::cout << "cm: " << cm << std::endl;

	// test chainToArray
	std::cout << "x: " << x << std::endl;
	arrayList<double>am1 = chainToArray1(x);		// arrayList is no copy assignment operator
	arrayList<double>am2 = chainToArray2(x);
	std::cout << "x: " << x << std::endl;
	std::cout << "am1: " << am1 << std::endl;
	std::cout << "am2: " << am2 << std::endl;

	// test fromList toList
	x.fromList(am);
	std::cout << "x.fromList(am): " << x << std::endl;
	arrayList<double> am3 = x.toList();
	std::cout << "am3 = x.toList(): " << am3 << std::endl;

	// test leftShift
	x.leftShift(1);
	std::cout << "x.leftShift(1): " << x << std::endl;
	x.leftShift(2);
	std::cout << "x.leftShift(2): " << x << std::endl;

	// test reverse
	y.reverse();
	std::cout << "y.reverse(): " << y << std::endl;
	y.recursionReverse();
	std::cout << "y.recursionReverse(): " << y << std::endl;

	// test meld
	z.meld(x, y);
	std::cout << "z.meld(x,y)=>z: " << z << std::endl;
	std::cout << "z.meld(x,y)=>x: " << x << std::endl;
	std::cout << "z.meld(x,y)=>y: " << y << std::endl;
	y.insert(0, 0);
	y.insert(1, 1);
	y.insert(2, 2);
	y.insert(3, 3);
	y.insert(4, 4);
	std::cout << "y: " << y << std::endl;
	x.meld(z, y);
	std::cout << "x.meld(z,y)=>x: " << x << std::endl;
	std::cout << "x.meld(z,y)=>z: " << z << std::endl;
	std::cout << "x.meld(z,y)=>y: " << y << std::endl;
	std::cout << std::endl;
	z.meld(y, x);
	std::cout << "z.meld(y,x)=>z: " << z << std::endl;
	std::cout << "z.meld(y,x)=>y: " << y << std::endl;
	std::cout << "z.meld(y,x)=>y: " << x << std::endl;
	std::cout << std::endl;
	z.meld(y, x);
	std::cout << "z.meld(y,x)=>z: " << z << std::endl;
	std::cout << "z.meld(y,x)=>y: " << y << std::endl;
	std::cout << "z.meld(y,x)=>x: " << x << std::endl;

	// test split
	z.split(y, x);
	std::cout << std::endl;
	std::cout << "z.split(y,x)=>z: " << z << std::endl;
	std::cout << "z.split(y,x)=>y: " << y << std::endl;
	std::cout << "z.split(y,x)=>x: " << x << std::endl;
	for (int i = 0; i < 6; ++i) z.insert(i, i);
	for (int i = 0; i < 6; ++i) x.insert(i, i);
	for (int i = 0; i < 6; ++i) y.insert(i, i);
	std::cout << "z: " << z << std::endl;
	std::cout << "y: " << y << std::endl;
	std::cout << "x: " << x << std::endl;
	z.split(y, x);
	std::cout << "z.split(y,x)=>z: " << z << std::endl;
	std::cout << "z.split(y,x)=>y: " << y << std::endl;
	std::cout << "z.split(y,x)=>x: " << x << std::endl;
	z.splitBeEmpty(y, x);
	std::cout << "z.splitBeEmpty(y,x)=>z: " << z << std::endl;
	std::cout << "z.splitBeEmpty(y,x)=>y: " << y << std::endl;
	std::cout << "z.splitBeEmpty(y,x)=>x: " << x << std::endl;

	// test sort
	std::cout << "insertSort: " << std::endl;
	x.insertSort();
	std::cout << "x: " << x << std::endl; 
	x.insert(3, 1);
	x.insertSort();
	std::cout << "x: " << x << std::endl;
	x.insert(4, 0);
	x.insertSort();
	std::cout << "x: " << x << std::endl;
	x.insert(5, 5);
	x.insertSort();
	std::cout << "x: " << x << std::endl;
	x.insert(0, 1);
	std::cout << "x: " << x << std::endl;
	x.insertSort();
	std::cout << "x: " << x << std::endl;

	// bubble
	std::cout << "bubbleSort: " << std::endl;
	x.bubbleSort();
	std::cout << "x: " << x << std::endl;
	x.insert(3, 1);
	x.bubbleSort();
	std::cout << "x: " << x << std::endl;
	x.insert(4, 0);
	x.bubbleSort();
	std::cout << "x: " << x << std::endl;
	x.insert(5, 5);
	x.bubbleSort();
	std::cout << "x: " << x << std::endl;
	x.insert(0, 1);
	std::cout << "x: " << x << std::endl;
	x.bubbleSort();
	std::cout << "x: " << x << std::endl;

	// rank
	std::cout << "rankSort: " << std::endl;
	x.rankSort();
	std::cout << "x: " << x << std::endl;
	chain<double> m;
	m.insert(0, 3);
	m.insert(1, 5);
	m.insert(2, 4);
	m.insert(3, 6);
	m.insert(4, 2);
	m.insert(5, 1);
	std::cout << "m: " << m << std::endl;
	m.rankSort();
	std::cout << "m: " << m << std::endl;

	// selection
	std::cout << "selectionSort: " << std::endl;
	x.selectionSort();
	std::cout << "x: " << x << std::endl;
	x.insert(3, 1);
	x.selectionSort();
	std::cout << "x: " << x << std::endl;
	x.insert(4, 0);
	x.selectionSort();
	std::cout << "x: " << x << std::endl;
	x.insert(5, 5);
	x.selectionSort();
	std::cout << "x: " << x << std::endl;
	x.insert(0, 1);
	std::cout << "x: " << x << std::endl;
	x.selectionSort();
	std::cout << "x: " << x << std::endl;
}

#endif