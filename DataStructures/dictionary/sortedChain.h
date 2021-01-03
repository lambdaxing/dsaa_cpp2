// sorted chain, implements dictionary

#ifndef sortedChain_
#define sortedChain_

#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

template<typename K,typename E>
class sortedChain :public dictionary<K, E>
{
public:
	sortedChain() { firstNode = nullptr; dSize = 0; }
	~sortedChain();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	std::pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const std::pair<const K, E>&);
	void output(std::ostream& out) const;

protected:
	pairNode<K, E>* firstNode;	// pointer to first node in chain
	int dSize;					// number of elemetns in dictionary
};

template<typename K,typename E>
sortedChain<K, E>::~sortedChain()
{// Destructor. Delete all nodes
	while (firstNode != nullptr)
	{// delete firstNode
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<typename K,typename E>
std::pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{// Return pointer to matching pair.
 // Return nullptr if no matching pair.
	pairNode<K, E>* currentNode = firstNode;

	// search for match with theKey
	while (currentNode != nullptr && currentNode->element.first != theKey)
		currentNode = currentNode->next;

	// verify match
	if (currentNode != nullptr && currentNode->element.first == theKey)
		// yes, found match
		return &currentNode->element;

	// no match
	return nullptr;
}

template<typename K,typename E>
void sortedChain<K, E>::insert(const std::pair<const K, E>& thePair)
{// Insert thePair into the dictionary. Overwrite exising pair, if any, with same key.
	pairNode<K, E>* p = firstNode,
		* tp = nullptr;		// tp trails p

	// move tp so that thePair can be inserted after tp
	while (p != nullptr && p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}

	// check if there is a matching pair
	if (p != nullptr && p->element.first == thePair.first)
	{// replace old value
		p->element.second = thePair.second;
		return;
	}

	// no match, set up node for thePair
	pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);

	// insert newNode just after tp
	if (tp == nullptr) firstNode = newNode;
	else tp->next = newNode;

	++dSize;
	return;
}

template<typename K,typename E>
void sortedChain<K, E>::erase(const K& theKey)
{// Delete the pair, if any, whose key equals theKey.
	pairNode<K, E>* p = firstNode,
		* tp = nullptr;		// tp trails p

	// search for match with theKey
	while (p != nullptr && p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}

	// verify match
	if(p != nullptr && p->element.first == theKey)
	{// found a match
		// remove p from the chain
		if (tp == nullptr) firstNode = p->next;	// p is first node
		else tp->next = p->next;

		delete p;
		--dSize;
	}
}

template<typename K,typename E>
void sortedChain<K, E>::output(std::ostream& out) const
{// Insert the chain elements into the stream out.
	for (pairNode<K, E>* currentNode = firstNode; currentNode != nullptr; currentNode = currentNode->next)
		out << currentNode->element.first << " " << currentNode->element.second << " ";
}

template<typename K,typename E>
std::ostream& operator<<(std::ostream& out, const sortedChain<K, E>& x)
{
	x.output(out);
	return out;
}
#endif