// height biased leftist tree emplementation of a max priority queue
// derives from the ADT maxPriorityQueue
// also derives from linkedBinaryTree<pair<int,T>>
// first component of a pair is the s value and the second is the data

#ifndef MAX_HBLT_
#define MAX_HBLT_

#include "maxPriorityQueue.h"
#include "linkedBinaryTree.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include <sstream>

template<typename T>
class maxHblt :public maxPriorityQueue<T>, public linkedBinaryTree<std::pair<int, T>>
{
public:
	bool empty() const { return this->treeSize == 0; }
	int size() const { return this->treeSize; }
	const T& top()
	{// return max element
		if (this->treeSize == 0)
			throw queueEmpty();
		return this->root->element.second;
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void meld(maxHblt<T>& theHblt)
	{// meld *this and theHblt
		meld(root, theHblt.root);
		this->treeSize += theHblt.treeSize;
		theHblt.root = nullptr;
		theHblt.treeSize = 0;
	}
	void output() { this->postOrder(hbltOutput); std::cout << std::endl; }

private:
	void meld(binaryTreeNode <std::pair<int, T>>*&, binaryTreeNode<std::pair<int, T>>*&);
	static void hbltOutput(binaryTreeNode<std::pair<int, T>>* t)
	{
		std::cout << t->element.second << ' ';
	}
};

template<typename T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int, T>>*& x, binaryTreeNode<std::pair<int, T>>*& y)
{// Meld leftist trees with roots *x and *y
 // Return pointer to new root in x.
	if (y == nullptr)		// y is empty
		return;
	if (x == nullptr)		// x is empty
	{
		x = y;
		return;
	}

	// neither is empty, swap x and y if necessary
	if (x->element.second < y->element.second)
	{
		using std::swap();
		swap(x, y);
	}

	// now x->element.second >= y->element.second
	// x is the root in the melded hblt

	meld(x->rightChild, y);

	// swap subtrees of x if necessary and set x->element.first
	if (x->leftChild == nullptr)
	{// left subtree empty, swap the subtree
		x->leftChild = x->rightChild;
		x->rightChild = nullptr;
		x->element.first = 1;
	}
	else
	{// swap only if left subtree has smaller s value
		if (x->leftChild->element.first < x->rightChild->element.first)
		{
			using std::swap();
			swap(x->leftChild, x->rightChild);
		}
		// update s value of x
		x->element.first = x->rightChild->element.first + 1;
	}
}

template<typename T>
void maxHblt<T>::push(const T& theElement)
{// Insert theElement into the leftist tree.
 // Create tree with one node.
	binaryTreeNode<std::pair<int, T>>* q = new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement));

	// meld q and original tree
	meld(this->root, q);
	++this->treeSize;
}

template<typename T>
void maxHblt<T>::pop()
{// Delete max element.
	if (this->root == nullptr)
		throw queueEmpty();

	// tree not empty
	binaryTreeNode<std::pair<int, T>>* left = this->root->leftChild, * right = this->root->rightChild;

	delete this->root;
	this->root = left;
	meld(this->root, right);
	--this->treeSize;
}

template<typename T>
void maxHblt<T>::initialize(T* theElements, int theSize)
{// Initialize hblt with theElements[1:theSize].
	std::queue<binaryTreeNode<std::pair<int, T>>*> q(theSize);
	this->erase();		// make *this empty

	// initialize queue of trees
	for (int i = 1; i <= theSize; ++i)
		// create trees with one node each
		q.push(new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElements[i])));

	// repeatedly meld from queue
	for (int i = 1; i <= theSize - 1; ++i)
	{// pop and meld two trees from queue
		binaryTreeNode<std::pair<int, T>>* b = q.front();
		q.pop();
		binaryTreeNode<std::pair<int, T>>* c = q.front();
		q.pop();
		meld(b, c);
		// put melded tree on queue
		q.push(b);
	}
	if (theSize > 0)
		this->root = q.front();
	this->treeSize = 0;
}
#endif // !MAX_HBLT_
