
// Extension of array to include a method to erase by matching element field
// This class is for use by the array graph classes

#ifndef GRAPH_ARRAY_
#define GRAPH_ARRAY_

#include "arrayListWithIterator.h"

template <class T>
class graphArray : public arrayList<T>
{
public:
    T* eraseElement(int theVertex)
    {
        int i = this->indexOf(theVertex);
        
        if (i == -1)
            return nullptr;
        
        T* theElement = &this->element[i];
        this->erase(i);
        return theElement;
    }
};
#endif
