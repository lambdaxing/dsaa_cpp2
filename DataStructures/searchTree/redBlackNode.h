//

#ifndef RED_BLACK_NODE_
#define RED_BLACK_NODE_

typedef enum class ColorType { Red, Black } ColorType;

template<typename T>
struct redBlackNode
{	
	T element;
	redBlackNode* leftChild, * rightChild;
	ColorType color;

	redBlackNode(const T& theElement, redBlackNode* theLeftNode = nullptr, redBlackNode* theRightNode = nullptr, ColorType theColor = Red)
		:element(theElement), leftChild(theLeftNode), rightChild(theRightNode), color(theColor) {}
};

#endif // !RED_BLACK_NODE_
