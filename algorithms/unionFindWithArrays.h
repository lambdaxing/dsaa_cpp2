// simple unite/find using 1D array

#ifndef UNION_FIND_WITH_ARRAYS_
#define UNION_FIND_WITH_ARRAYS_

#include <iostream>

int* equivClass,   // equivalence class array
n;             // number of elements

void initialize(int numberOfElements)
{// Initialize numberOfElements classes with one element each.
    n = numberOfElements;
    equivClass = new int[n + 1];
    for (int e = 1; e <= n; e++)
        equivClass[e] = e;          // The index(e) represents the element, 
                                    // and the value(equivClass[e]) represents the equivalence class to which the element belongs
}

void unite(int classA, int classB)
{// Unite the classes classA and classB.
 // Assume classA != classB
    for (int k = 1; k <= n; k++)
        if (equivClass[k] == classB)
            equivClass[k] = classA;
}

int find(int theElement)
{// Find the class that contains theElement.
    return equivClass[theElement];
}

#endif // !UNION_FIND_WITH_ARRAYS_
