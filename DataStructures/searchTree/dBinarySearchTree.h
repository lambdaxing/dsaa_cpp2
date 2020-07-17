// linked binary tree implementation of a binary search tree with duplicates
// implements all dictionary and bsTree methods

#ifndef DBINARY_SEARCH_TREE_
#define DBINARY_SEARCH_TREE_

#include "binarySearchTree.h"

template<typename K,typename E>
class dBinarySearchTree :public binarySearchTree<K, E>
{
public:
	// override insert method of binarySearchTree
	void insert(const std::pair<const K, E>&);
};

template<typename K,typename E>
void dBinarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair)
{// Insert thePair into the tree. Duplicate keys permitted.
	// find place to insert
	binaryTreeNode<std::pair<const K, E>>* p = this->root, * pp = nullptr;

	while (p != nullptr)
	{// examine p->element
		pp = p;
		// move p to a child
		if (thePair.first <= p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}

	// get a node for thePair and attach to pp
	binaryTreeNode<std::pair<const K, E>>* newNode = new binaryTreeNode<std::pair<const K, E>>(thePair);
	if (this->root != nullptr)	// the tree is not empty
		if (thePair.first <= pp->element.first)
			pp->leftChild = newNode;
		else
			pp->rightChild = newNode;
	else
		this->root = newNode;
	++this->treeSize;
}
#endif // !DBINARY_SEARCH_TREE_
