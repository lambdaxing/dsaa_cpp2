// abstract class indexedBSTree 
// abstract data type specification for indexed binary search trees
// all methods are pure virtual functions
// K is key type and E is value type

#ifndef INDEXED_BS_TREE_
#define INDEXED_BS_TREE_

#include "bsTree.h"

template<typename K,typename E>
class indexedBSTree :public bsTree<K, E>
{
public:
	virtual std::pair<const K, E>* get(int) const = 0;
					// return pointer to pair with given index
	virtual void delete(int) = 0;
					// delete pair with given index
};
#endif // !INDEXED_BS_TREE_
