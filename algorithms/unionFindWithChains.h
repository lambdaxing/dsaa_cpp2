// union/find using chains and size info
// integer pointers used

#ifndef UNION_FIND_WITH_CHAINS_
#define UNION_FIND_WITH_CHAINS_

#include <iostream>
#include <algorithm>

struct equivNode
{
    int equivClass,  // element class identifier                the equivalence class identifier for this element, is usually the first element of the equivalence class.
        size,        // number of elements in class             when the element represents the first element of the equivalence class, 
                     //                                         size represents the number of elements of the equivalence class, that is, the number of elements linked in this linked list.
        next;        // pointer to next element in class        an integer(index) as a pointer, 0 can be used to represent a null pointer.     
};

equivNode* node; // array of nodes
int n;           // number of elements

void initialize(int numberOfElements)
{// Initialize numberOfElements classes with one element each.
    n = numberOfElements;
    node = new equivNode[n + 1];

    for (int e = 1; e <= n; e++)
    {
        node[e].equivClass = e;
        node[e].next = 0;
        node[e].size = 1;
    }
}

void unite(int classA, int classB)
{// Unite the classes classA and classB.
 // Assume classA != classB
 // classA and classB are first elements in their chains

   // make classA smaller class
    if (node[classA].size > node[classB].size)
        std::swap(classA, classB);

    //  change equivClass values of smaller class
    int k;
    for (k = classA; node[k].next != 0; k = node[k].next)
        node[k].equivClass = classB;
    node[k].equivClass = classB; // last node in chain

    // insert chain classA after first node in chain classB
    // and update new chain size
    node[classB].size += node[classA].size;
    node[k].next = node[classB].next;
    node[classB].next = classA;
}

int find(int theElement)
{// Find the class that contains theElement.
    return node[theElement].equivClass;
}

#endif // !UNION_FIND_WITH_CHAINS_
