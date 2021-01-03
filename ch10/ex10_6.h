// sorted chain, implements dictionary

#ifndef sortedChain_
#define sortedChain_

#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

template<typename K, typename E>
class sortedChainWithHeaderAndTrail :public dictionary<K, E>
{
public:
	sortedChainWithHeaderAndTrail()
	{
		header = new pairNode<K, E>();
		trailer = new pairNode<K, E>();
		header->next = trailer;
		trailer->next = nullptr;
		dSize = 0;
	}
	~sortedChainWithHeaderAndTrail();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	std::pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const std::pair<const K, E>&);
	void output(std::ostream& out) const;

protected:
	pairNode<K, E>* header;		// pointer to header node in chain
	pairNode<K, E>* trailer;	// pointer to trail node in chain
	int dSize;					// number of elemetns in dictionary
};

template<typename K, typename E>
sortedChainWithHeaderAndTrail<K, E>::~sortedChainWithHeaderAndTrail()
{// Destructor. Delete all nodes
	while (header != nullptr)
	{// delete firstNode
		pairNode<K, E>* nextNode = header->next;
		delete header;
		header = nextNode;
	}
}

template<typename K, typename E>
std::pair<const K, E>* sortedChainWithHeaderAndTrail<K, E>::find(const K& theKey) const
{// Return pointer to matching pair.
 // Return nullptr if no matching pair.
	trailer->element.first = theKey;
	pairNode<K, E>* currentNode = header->next;

	// search for match with theKey
	while (currentNode->element.first != theKey)
		currentNode = currentNode->next;

	// verify match
	if (currentNode != trailer)
		// yes, found match
		return &currentNode->element;

	// no match
	return nullptr;
}

template<typename K, typename E>
void sortedChainWithHeaderAndTrail<K, E>::insert(const std::pair<const K, E>& thePair)
{// Insert thePair into the dictionary. Overwrite exising pair, if any, with same key.
	trailer->element.first = thePair.first;
	pairNode<K, E>* p = header->next,
		* tp = header;		// tp trails p

	// move tp so that thePair can be inserted after tp
	while (p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}

	// check if there is a matching pair
	if (p->element.first == thePair.first)
	{// replace old value
		p->element.second = thePair.second;
		if (p == trailer)
		{
			trailer->next = new pairNode<K, E>();
			trailer = trailer->next;
			dSize++;
		}
		return;
	}

	// no match, set up node for thePair
	pairNode<K, E>* newNode = new pairNode<K, E>(thePair, p);

	tp->next = newNode;

	++dSize;
	return;
}

template<typename K, typename E>
void sortedChainWithHeaderAndTrail<K, E>::erase(const K& theKey)
{// Delete the pair, if any, whose key equals theKey.
	trailer->element.first = theKey;
	pairNode<K, E>* p = header->next,
		* tp = header;		// tp trails p

	// search for match with theKey
	while (p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}

	// verify match
	if (p != trailer)
	{// found a match
		// remove p from the chain
		tp->next = p->next;
		delete p;
		--dSize;
	}
}

template<typename K, typename E>
void sortedChainWithHeaderAndTrail<K, E>::output(std::ostream& out) const
{// Insert the chain elements into the stream out.
	for (pairNode<K, E>* currentNode = header->next; currentNode != trailer; currentNode = currentNode->next)
		out << currentNode->element.first << " " << currentNode->element.second << " ";
}

template<typename K, typename E>
std::ostream& operator<<(std::ostream& out, const sortedChainWithHeaderAndTrail<K, E>& x)
{
	x.output(out);
	return out;
}
#endif