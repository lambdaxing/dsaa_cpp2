// nodes used in union/find trees

#ifndef UNION_FIND_NODE_
#define UNION_FIND_NODE_

struct  unionFindNode
{
	int parent;		// if true then tree weight otherwise pointer to parent in tree

	bool root;		// true if root

	unionFindNode() :parent(1), root(true) {}
};
#endif // !UNION_FIND_NODE_
