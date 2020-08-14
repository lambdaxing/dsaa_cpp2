
// Extension of chain to include a method to erase by matching element field
// This class is for use by the linked graph classes

#ifndef graphChain_
#define graphChain_

#include "chainWithIterator.h"
#include "chainNode.h"

template <class T>
class graphChain : public chain<T>
{
public:
    T* eraseElement(int theVertex)
    {// Delete node with element == theVertex. Return pointer to
     // deleted element. Return nullptr if no matching element.
        chainNode<T>* current = this->firstNode,
            * trail = nullptr; // one behind current

// search for match
        while (current != nullptr && current->element != theVertex)
        {
            trail = current;
            current = current->next;
        }

        if (current == nullptr) // no match
            return nullptr;

        // match found in node current
        T* theElement = &current->element; // save matching element (it's ok ?)

        // remove current from chain
        if (trail != nullptr)
            trail->next = current->next;
        else
            this->firstNode = current->next; // current is first node

        delete current;
        this->listSize--;
        return theElement;
    }
};
#endif
