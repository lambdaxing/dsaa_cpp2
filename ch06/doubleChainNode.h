// double chain node

#ifndef DOUBLE_CHAIN_NODE
#define DOUBLE_CHAIN_NODE

template <typename T>
struct doubleChainNode
{
	// data members
	T element;
	doubleChainNode<T>* next;
	doubleChainNode<T>* previous;

	// methods
	doubleChainNode() = default;
	//doubleChainNode(const T& element)
	//{
	//	this->element = element;
	//	this->next = nullptr;
	//	this->previous = nullptr;
	//}
	doubleChainNode(const T& element, doubleChainNode<T>* previous = nullptr, doubleChainNode<T>* next = nullptr)
	{
		this->element = element;
		this->next = next;
		this->previous = previous;
	}
};

#endif