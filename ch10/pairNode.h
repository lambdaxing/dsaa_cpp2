
// node with a next and element field; element is a pair<const K,E>

#ifndef pairNode_
#define pairNode_

#include <utility>

template <class K, class E>
struct pairNode
{
    typedef std::pair<const K, E> pairType;
    pairType element;
    pairNode<K, E>* next;

    pairNode(const pairType& thePair) :element(thePair) {}
    pairNode(const pairType& thePair, pairNode<K, E>* theNext)
        :element(thePair) {
        next = theNext;
    }
};

#endif
