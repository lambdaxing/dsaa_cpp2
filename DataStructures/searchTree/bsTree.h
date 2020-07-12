// abstract class bsTree
// abstract data type specification for binary search trees
// all methods are pure virtual functions
// K is key type and E is value type

#ifndef BSTREE_
#define BSTREE_

#include "dictionary.h"

template<typename K,typename E>
class bsTree :public dictionary<K, E>
{
public:
	virtual void ascend() = 0;
				// output in ascending order of key
};
#endif // !BSTREE_
