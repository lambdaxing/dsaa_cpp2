// linked binary tree implementation of a binary search tree
// implements all dictionary and bsTree methods

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "bsTree.h"
#include "linkedBinaryTree.h"

template<typename K,typename E>
class binarySearchTree : public bsTree<K, E>, public linkedBinaryTree<std::pair<const K, E>>
{
public:
	// methods of dictionary
	bool empty() const { return this->treeSize == 0; }
	int size() const { return this->treeSize; }
	std::pair<const K, E>* find(const K& theKey) const;
	void insert(const std::pair<const K, E>& thePair);
	void erase(const K& theKey);

	// additional method of bsTree
	void ascend() { this->inOrderOutput(); }
};

template<typename K,typename E>
std::pair<const K, E>* binarySearchTree<K, E>::find(const K& theKey) const
{// Return pointer to matching pair.
 // Return null if no matching pair.
	// p starts at the root and moves through the tree looking for an element with key theKey
	binaryTreeNode<std::pair<const K, E>>* p = this->root;
	while (p != nullptr)
		// examine p->element
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			if (theKey > p->element.first)
				p = p->rightChild;
			else // found matching pair
				return &p->element;

	// no matching pair
	return nullptr;
}

template<typename K,typename E>
void binarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair)
{// Insert thePair into the tree. Overwrite existing pair, if any, with same key.
	//find place to insert
	binaryTreeNode<std::pair<const K, E>>* p = this->root, * pp = nullptr;

	while (p != nullptr)
	{// examine p->element
		pp = p;
		// move p to a child
		if (thePair.first < p->element.first)
			p = p->leftChild;
		else
			if (thePair.first > p->element.first)
				p = p->rightChild;
			else {
				// replace old value
				p->element.second = thePair.second;
				return;
			}
	}

	// get a node for thePair and attach to pp
	binaryTreeNode<std::pair<const K, E>>* newNode = new binaryTreeNode<std::pair<const K, E>>(thePair);
	if (this->root != nullptr) // the tree is not empty
		if (thePair.first < pp->element.first)
			pp->leftChild = newNode;
		else
			pp->rightChild = newNode;
	else
		this->root = newNode;	// insertion into empty tree
	++this->treeSize;
}

template<typename K,typename E>
void binarySearchTree<K, E>::erase(const K& theKey)
{// Delete the pair, if any, whose key equals theKey.

	// search for node with key theKey
	binaryTreeNode<std::pair<const K, E>>* p = this->root, * pp = nullptr;
	while (p != nullptr && p->element.first != theKey)
	{// move to a child of p
		pp = p;
		if (theKey < p->element.first)
			p = p->leftChild;
		else
			p = p->rightChild;
	}

	if (p == nullptr)
		return;		// no pair with key theKey

	// restructure tree
	// handle case when p has two children
	if (p->leftChild != nullptr && p->rightChild != nullptr)
	{// two children
		// convert to zero or one child case
		// find largest element in left subtree of p
		binaryTreeNode<std::pair<const K, E>>* s = p->leftChild, * ps = p;	// parent of s
		
		while (s->rightChild != nullptr)
		{// move to larger element
			ps = s;
			s = s->rightChild;
		}

		// move largest from s to p, can't do a simple move
		// p->element = s->element as key is const
		binaryTreeNode<std::pair<const K, E>>* q = new binaryTreeNode<std::pair<const K, E>>(s->element, p->leftChild, p->rightChild);
		if (pp == nullptr)
			this->root = q;
		else
			if (p == pp->leftChild)
				pp->leftChild = q;
			else
				pp->rightChild = q;
		if (ps == p) pp = q;
		else pp = ps;
		delete p;
		p = s;
	}

	// p has at most one child
	// save child pointer in x
	binaryTreeNode<std::pair<const K, E>>* c;
	if (p->leftChild != nullptr)
		c = p->leftChild;
	else
		c = p->rightChild;

	// delete p
	if (p == this->root)
		this->root = c;
	else
	{// is p left or right child of pp ?
		if (p == pp->leftChild)
			pp->leftChild = c;
		else
			pp->rightChild = c;
	}
	--this->treeSize;
	delete p;
}

// overload << for pair
template<typename K,typename E>
std::ostream& operator<<(std::ostream& out, const std::pair<K, E>& x)
{
	out << x.first << ' ' << x.second;
	return out;
}

#endif // !BINARY_SEARCH_TREE_
