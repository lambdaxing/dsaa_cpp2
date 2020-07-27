// dictionary by red black tree

#ifndef RED_BLACK_TREE_
#define RED_BLACK_TREE_

#include "bsTree.h"
#include "linkedRedBlackNodeTree.h"

template<typename K,typename E>
class redBlackTree :public bsTree<K, E>, public linkedRedBlackNodeTree<std::pair<const K, E>>
{
public:
	typedef redBlackNode<std::pair<const K, E>>* position;
	redBlackTree() :linkedRedBlackNodeTree<std::pair<const K, E>>::linkedRedBlackNodeTree(), X(nullptr), P(nullptr), GP(nullptr), GGP(nullptr) {};

	// methods of dictionary
	bool empty() const { return this->treeSize == 0; }
	int size() const { return this->treeSize; }
	std::pair<const K, E>* find(const K& theKey) const;
	void insert(const std::pair<const K, E>& thePair);
	void erase(const K& theKey) {}

	// additional method of bsTree
	void ascend() { this->inOrderOutput(); }

private:
	// help variables and functions
	position X, P, GP, GGP;
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
	position rotate(const K& theKey, position parent)
	{
		if (theKey < parent->element.first)
			return parent->leftChild = theKey < parent->leftChild->element.first ? singleRotateWithLeft(parent->leftChild) : singleRotateWithRight(parent->leftChild);		// LL or RR
		else
			return parent->rightChild = theKey < parent->rightChild->element.first ? singleRotateWithLeft(parent->rightChild) : singleRotateWithRight(parent->rightChild);
	}

	void handleReorient(const K& theKey)
	{
		X->color = Red;		// Do the color flip
		if (X->leftChild != nullptr)
			X->leftChild->color = Black;
		if (X->rightChild != nullptr)
			X->rightChild->color = Black;

		if (P->color == Red)		// have to rotate
		{
			GP->color = Red;
			if ((theKey < GP->element.first) != (theKey < P->element.first))
				P = rotate(theKey, GP);		// start double rotation
			X = rotate(theKey, GGP);
			X->color = Black;
		}
		this->root->color = Black;
	}
};

template<typename K,typename E>
std::pair<const K, E>* redBlackTree<K, E>::find(const K& theKey) const
{// Return pointer to matching pair.
 // Return null if no matching pair.
	// p starts at the this->root and moves through the tree looking for an element with key theKey
	position p = this->root;
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
void redBlackTree<K, E>::insert(const std::pair<const K, E>& thePair)
{
	// tree is empty
	if (this->root == nullptr)
	{
		this->root = new redBlackNode<std::pair<const K, E>>(thePair);
		this->root->color = Black;
		++this->treeSize;
		return;
	}

	// tree is not empty
	X = P = GP = this->root;
	while (X != nullptr && X->element.first != thePair.first)	// Descend down the tree
	{
		GGP = GP; GP = P; P = X;
		if (thePair.first < X->element.first)
			X = X->leftChild;
		else
			X = X->rightChild;
		if (X != nullptr && X->leftChild != nullptr && X->rightChild != nullptr && X->leftChild->color == Red && X->rightChild->color == Red)
			handleReorient(thePair.first);
	}

	if (X != nullptr)
		return;		// duplicate

	X = new redBlackNode<std::pair<const K, E>>(thePair);
	if (X->element.first < P->element.first)		// Attach to its parent
		P->leftChild = X;
	else
		P->rightChild = X;
	handleReorient(X->element.first);		// Color red; maybe rotate
	++this->treeSize;
}

// overload << for pair
template<typename K, typename E>
std::ostream& operator<<(std::ostream& out, const std::pair<K, E>& x)
{
	out << x.first << ' ' << x.second;
	return out;
}

#endif // !RED_BLACK_TREE_
