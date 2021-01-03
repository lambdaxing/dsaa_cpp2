// binary tree traversal methods

#include <iostream>
#include <queue>
#include "binaryTreeNode.h"
#include "myExceptions.h"

template<typename T>
void visit(binaryTreeNode<T>* x)
{
	std::cout << x->element << ' ';
}

template<typename T>
void preOrder(binaryTreeNode<T>* t)
{
	if (t != nullptr)
	{
		visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<typename T>
void inOrder(binaryTreeNode<T>* t)
{
	if (t != nullptr)
	{
		inOrder(t->leftChild);
		visit(t);
		inOrder(t->rightChild);
	}
}

template<typename T>
void postOrder(binaryTreeNode<T>* t)
{
	if (t != nullptr)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		visit(t);
	}
}

template<typename T>
void levelOrder(binaryTreeNode<T>* t)
{// Level-order traversal of *t
	std::deque<binaryTreeNode<T>*> q;
	while (t != nullptr)
	{
		visit(t);		// visit t

		// put t's children on queue
		if (t->leftChild != nullptr)
			q.push_back(t->leftChild);
		if (t->rightChild != nullptr)
			q.push_back(t->rightChild);

		// get next node to visit
		if (q.empty())
			return;
		else
			t = q.front();
		q.pop_front();

	}
}