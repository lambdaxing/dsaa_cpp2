#ifndef huffmanNode_
#define huffmanNode_

#include "linkedBinaryTree.h"

template<class T>
struct huffmanNode
{
    linkedBinaryTree<int>* tree;
    T weight;

    operator T () const { return weight; }
};

#endif
