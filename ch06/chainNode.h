// chain node

#ifndef chainNode_
#define chainNode_

template <typename T>
struct chainNode
{
	// data members
	T element;
	chainNode<T>* next;

	// methods
	chainNode() = default;
	chainNode(const T& element)
	{
		this->element = element;
		this->next = nullptr;
	}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};

#endif