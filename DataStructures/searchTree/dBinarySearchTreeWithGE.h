// extension of binary search tree with duplicates
// includes findGE

#ifndef dBinarySearchTreeWithGE_
#define dBinarySearchTreeWithGE_

#include "dBinarySearchTree.h"

template<typename K,typename E>
class dBinarySearchTreeWithGE : public dBinarySearchTree<K, E>
{
public:
	std::pair<const K, E>* findGE(const K& theKey) const;
};

template<typename K,typename E>
std::pair<const K, E>* dBinarySearchTreeWithGE<K, E>::findGE(const K& theKey) const
{// Return pointer to pair with smallest key >= theKey.
 // Return nullptr if no element has key >= theKey.
	binaryTreeNode<std::pair<const K, E>>* currentNode = this->root;
	std::pair<const K, E>* bestElement = nullptr;		// element with smallest key >= theKey found so far

	// search the tree
	while (currentNode != nullptr)
		// is currentNode->element a candidate ?
		if (currentNode->element.first >= theKey)
		{// yes, currentNode->element is a better candidate than bestElement
			bestElement = &currentNode->element;
			// smaller keys in left subtree only
			currentNode = currentNode->leftChild;
		}
		else
			// no, currentNode->element.first is too small 
			// try right subtree
			currentNode = currentNode->rightChild;

	return bestElement;
}
#endif // !dBinarySearchTreeWithGE_
