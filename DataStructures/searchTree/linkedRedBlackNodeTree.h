// linked binary tree using nodes of type redBlackNode
// derives from the abstract class binaryTree

#ifndef LINKED_BINARY_TREE_
#define LINKED_BINARY_TREE_

#include <iostream>
#include <queue>
#include "binaryTree.h"
#include "redBlackNode.h"
#include "myExceptions.h"

template<typename E>
class linkedRedBlackNodeTree :public binaryTree<redBlackNode<E>>
{
public:
	linkedRedBlackNodeTree() :root(nullptr), treeSize(0) {}
	~linkedRedBlackNodeTree() { erase(); }

	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	E* rootElement() const;
	void makeTree(const E& element, linkedRedBlackNodeTree<E>&, linkedRedBlackNodeTree<E>&);
	linkedRedBlackNodeTree<E>& removeLeftSubtree();
	linkedRedBlackNodeTree<E>& removeRightSubtree();
	void preOrder(void(*theVisit)(redBlackNode<E>*))
	{
		visit = theVisit;
		preOrder(root);
	}
	void inOrder(void(*theVisit)(redBlackNode<E>*))
	{
		visit = theVisit;
		inOrder(root);
	}
	void postOrder(void(*theVisit)(redBlackNode<E>*))
	{
		visit = theVisit;
		postOrder(root);
	}
	void levelOrder(void(*theVisit)(redBlackNode<E>*));

	void preOrderOutput() { preOrder(output); std::cout << std::endl; }
	void inOrderOutput() { inOrder(output); std::cout << std::endl; }
	void postOrderOutput() { postOrder(output); std::cout << std::endl; }
	void levelOrderOutput() { levelOrder(output); std::cout << std::endl; }

	void erase()
	{
		postOrder(dispose);
		root = nullptr;
		treeSize = 0;
	}
	int height() const { return height(root); }

protected:
	redBlackNode<E>* root;		// pointer to root
	int treeSize;					// number of nodes in tree
	static void(*visit)(redBlackNode<E>*);	// visit function
	static int count;				// used to count nodes in a subtree
	static void preOrder(redBlackNode<E>* t);
	static void inOrder(redBlackNode<E>* t);
	static void postOrder(redBlackNode<E>* t);
	static void countNodes(redBlackNode<E>* t)
	{
		visit = addToCount;
		count = 0;
		preOrder(t);
	}
	static void dispose(redBlackNode<E>* t) { delete t; }
	static void output(redBlackNode<E>* t) { std::cout << t->element << ' '; }
	static void addToCount(redBlackNode<E>* t) { ++count; }
	static int height(redBlackNode<E>* t);
};

// the following should work but gives an internal compoler error
// template<typename E> void (*linkedRedBlackNodeTree<E>::visit)(redBlackNode<E>*);
// so that explicit declarations that follow are used for out purpose instead
void (*linkedRedBlackNodeTree<int>::visit)(redBlackNode<int>*);
//void (*linkedRedBlackNodeTree<booster>::visit)(redBlackNode<booster>*);
void (*linkedRedBlackNodeTree<std::pair<int, int> >::visit)(redBlackNode<std::pair<int, int> >*);
void (*linkedRedBlackNodeTree<std::pair<const int, char> >::visit)(redBlackNode<std::pair<const int, char> >*);
void (*linkedRedBlackNodeTree<std::pair<const char, int> >::visit)(redBlackNode<std::pair<const char, int> >*);
void (*linkedRedBlackNodeTree<std::pair<const int, int> >::visit)(redBlackNode<std::pair<const int, int> >*);

template<typename E>
E* linkedRedBlackNodeTree<E>::rootElement() const
{// Return nullpt if no root. Otherwise, return pointer to root element.
	if (treeSize == 0)
		return nullptr;		// no root
	else
		return &root->element;
}

template<typename E>
void linkedRedBlackNodeTree<E>::makeTree(const E& element, linkedRedBlackNodeTree<E>& left, linkedRedBlackNodeTree<E>& right)
{// Combine left, right, and element to make new tree.
 // left, right, and this must be different trees.
	// create combined tree
	root = new redBlackNode<E>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;

	// deny access from trees left and right
	left.root = right.root = nullptr;
	left.treeSize = right.treeSize = 0;
}

template<typename E>
linkedRedBlackNodeTree<E>& linkedRedBlackNodeTree<E>::removeLeftSubtree()
{// Remove and return the left subtree.
	// check if empty
	if (treeSize == 0)
		throw emptyTree();

	// detach left subtree and save in leftSubtree
	linkedRedBlackNodeTree<E> leftSubtree;
	leftSubtree.root = root->leftChild;
	count = 0;
	leftSubtree.treeSize = countNodes(leftSubtree.root);
	root->leftChild = nullptr;
	treeSize -= leftSubtree.treeSize;

	return leftSubtree;
}

template<typename E>
linkedRedBlackNodeTree<E>& linkedRedBlackNodeTree<E>::removeRightSubtree()
{// Remove and return the right subtree.
	// check if empty
	if (treeSize == 0)
		throw emptyTree();

	// detach right subtree and save in rightSubtree
	linkedRedBlackNodeTree<E> rightSubtree;
	rightSubtree.root = root->rightChild;
	count = 0;
	rightSubtree.treeSize = countNodes(rightSubtree.root);
	root->rightChild = nullptr;
	treeSize -= rightSubtree.treeSize;

	return rightSubtree;
}

template<typename E>
void linkedRedBlackNodeTree<E>::preOrder(redBlackNode<E>* t)
{// Preorder traversal.
	if (t != nullptr)
	{
		linkedRedBlackNodeTree<E>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}

template<typename E>
void linkedRedBlackNodeTree<E>::inOrder(redBlackNode<E>* t)
{// Inorder traversal.
	if (t != nullptr)
	{
		inOrder(t->leftChild);
		linkedRedBlackNodeTree<E>::visit(t);
		inOrder(t->rightChild);
	}
}

template<typename E>
void linkedRedBlackNodeTree<E>::postOrder(redBlackNode<E>* t)
{// Postorder traversal.
	if (t != nullptr)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedRedBlackNodeTree<E>::visit(t);
	}
}

template<typename E>
void linkedRedBlackNodeTree<E>::levelOrder(void(*theVisit)(redBlackNode<E>*))
{// Level-order traversal.
	std::deque<redBlackNode<E>*> q;
	redBlackNode<E>* t = root;
	while (t != nullptr)
	{
		theVisit(t);	// visit t

		// put t's children no queue
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

template<typename E>
int linkedRedBlackNodeTree<E>::height(redBlackNode<E>* t)
{// Return height of tree rooted at *t.
	if (t == nullptr)
		return 0;						// empty tree
	int hl = height(t->leftChild);		// height of left
	int hr = height(t->rightChild);		// height of right
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}
#endif // !LINKED_BINARY_TREE_

