//

#ifndef AVL_TREE_
#define AVL_TREE_

#include "linkedBinaryTree.h"
#include "bsTree.h"

template<typename K,typename E>
class avlTree :public bsTree<K, E>, public linkedBinaryTree<std::pair<const K, E>>
{
public:
	typedef binaryTreeNode<std::pair<const K, E> >* position;
	// methods of dictionary
	bool empty() const { return this->treeSize == 0; }
	int size() const { return this->treeSize; }
	std::pair<const K, E>* find(const K& theKey) const;
	void insert(const std::pair<const K, E>& thePair) { this->root = insert(thePair, this->root); }
	void erase(const K& theKey) { this->root = erase(theKey, this->root); }

	// additional method of bsTree
	void ascend() { this->inOrderOutput(); }

private:
	position insert(const std::pair<const K, E>& thePair, position t);
	position erase(const K& theKey, position t);
	position singleRotateWithLeft(position K2)	// LL
	{
		position K1;

		K1 = K2->leftChild;
		K2->leftChild = K1->rightChild;
		K1->rightChild = K2;
		return K1;
	}
	position singleRotateWithRight(position K1)	// RR
	{
		position K2;

		K2 = K1->rightChild;
		K1->rightChild = K2->leftChild;
		K2->leftChild = K1;
		return K2;
	}
	position doubleRotateWithLeft(position K3)	// LR
	{
		// K1 is the leftChild of K3
		// K2 is the rightChild of K1
		// K1 and K2 perform right rotation
		K3->leftChild = singleRotateWithRight(K3->leftChild);
		// now, the leftChild of K3 is K2
		// K3 and K2 perform left rotation
		return singleRotateWithLeft(K3);
	}
	position doubleRotateWithRight(position K1)	// RL
	{
		// K3 is the rightChild of K1
		// K2 is the leftChild of K3
		// K3 and K2 perform left rotation
		K1->rightChild = singleRotateWithLeft(K1->rightChild);
		// now, the rightChild of K1 is K2
		// K1 and K2 perform right rotation
		return singleRotateWithRight(K1);
	}
};

template<typename K, typename E>
std::pair<const K, E>* avlTree<K, E>::find(const K& theKey) const
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
auto avlTree<K, E>::insert(const std::pair<const K, E>& thePair, position t) -> position
{// Insert the new element recursively into the AVL

	if (t == nullptr)
	{// find the position of insert, and create memory to storage the element
		t = new binaryTreeNode<std::pair<const K, E>>(thePair);
		++this->treeSize;
	}
	else
	{
		if (thePair.first < t->element.first)
		{// insert the element into the left avl of t
			t->leftChild = insert(thePair, t->leftChild);
			if (this->height(t->leftChild) - this->height(t->rightChild) == 2)
				if (thePair.first < t->leftChild->element.first)	// inserted to the LL of t
					t = singleRotateWithLeft(t);
				else    // insert to the LR of t
					t = doubleRotateWithLeft(t);
		}
		else if (thePair.first > t->element.first)
		{// insert the element into the right avl of t
			t->rightChild = insert(thePair, t->rightChild);
			if (this->height(t->rightChild) - this->height(t->leftChild) == 2)
				if (thePair.first > t->rightChild->element.first)	// inserted to the RR of t
					t = singleRotateWithRight(t);	
				else
					t = doubleRotateWithRight(t);
		}
		else // else the pair is in the tree already; we'll cover old value
		{
			t->element.second = thePair.second;
		}
	}
	return t;
}

template<typename K, typename E>
auto avlTree<K, E>::erase(const K& theKey, position t) -> position
{
	if (t == nullptr)	// not found the key theKey
		return t;

	if (theKey < t->element.first)
	{
		t->leftChild = erase(theKey, t->leftChild);
		if (this->height(t->rightChild) - this->height(t->leftChild) == 2)
			if (this->height(t->rightChild->leftChild) < this->height(t->rightChild->rightChild))
				t = singleRotateWithRight(t);
			else
				t = doubleRotateWithRight(t);
	}
	else if (theKey > t->element.first)
	{
		t->rightChild = erase(theKey, t->rightChild);
		if (this->height(t->leftChild) - this->height(t->rightChild) == 2)
			if (this->height(t->leftChild->rightChild) < this->height(t->leftChild->leftChild))
				t = singleRotateWithLeft(t);
			else
				t = doubleRotateWithLeft(t);
	}
	else
	{
		// t has two children
		if (t->leftChild != nullptr && t->rightChild != nullptr)
		{
			position s = t->leftChild, ps = t;	// parent of s
			while (s->rightChild != nullptr)
			{// move to larger element
				ps = s;
				s = s->rightChild;
			}
			position q = new binaryTreeNode<std::pair<const K, E>>(s->element, t->leftChild, t->rightChild);
			delete t;
			t = q;
			t->leftChild = erase(s->element.first, t->leftChild);
		}
		else
		{
			// t has at most one child
			position c;
			if (t->leftChild != nullptr)
				c = t->leftChild;
			else
				c = t->rightChild;
			delete t;
			t = c;
			--this->treeSize;
		}
	}
	return t;
}

// overload << for pair
template<typename K, typename E>
std::ostream& operator<<(std::ostream& out, const std::pair<K, E>& x)
{
	out << x.first << ' ' << x.second;
	return out;
}
#endif // !AVL_TREE_
