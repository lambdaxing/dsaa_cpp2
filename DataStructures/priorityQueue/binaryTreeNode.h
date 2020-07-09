#ifndef BINARY_TREE_NODE_
#define BINARY_TREE_NODE_

template<typename T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild, * rightChild;

	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftNode = nullptr, binaryTreeNode* theRightNode = nullptr) :element(theElement), leftChild(theLeftNode), rightChild(theRightNode) {}
};
#endif // !BINARY_TREE_NODE_
