// union/find with weighting and path compaction

#include <iostream>
#include "unionFindNode.h"

unionFindNode* node;

void initialize(int numberOfElements)
{// Initialize numberOfElements trees, 1 element per set/class/tree.
	node = new unionFindNode[numberOfElements + 1];
}

void unite(int rootA, int rootB)
{// Combine trees with different roots rootA and rootB.
 // Use the weighting rule.
    if (node[rootA].parent < node[rootB].parent)
    {// rootA becomes subtree of rootB
        node[rootB].parent += node[rootA].parent;
        node[rootA].root = false;
        node[rootA].parent = rootB;
    }
    else
    {// rootB becomes subtree of rootA
        node[rootA].parent += node[rootB].parent;
        node[rootB].root = false;
        node[rootB].parent = rootA;
    }
}

int find(int theElement)
{// Return root of tree containing theElement.
 // Compact path from theElement to root.

    // theRoot will eventually be the root of the tree
    int theRoot = theElement;
    while (!node[theRoot].parent)
        theRoot = node[theRoot].parent;

    // compact path from theElement to theRoot
    int currentNode = theElement;   // start at theElement
    while (currentNode != theRoot)
    {
        int parentNode = node[currentNode].parent;
        node[currentNode].parent = theRoot;     // move to level 2
        currentNode = parentNode;               // moves to old parent
    }
    return theRoot;
}


void main(void)
{
    initialize(10);
    unite(1, 2);
    unite(3, 4);
    unite(1, 3);
    std::cout << "find(1) = " << find(1) << " find(2) = " << find(2) << std::endl;
    std::cout << "find(3) = " << find(3) << " find(4) = " << find(4) << std::endl;
    std::cout << "find(5) = " << find(5) << " find(6) = " << find(6) << std::endl;
}