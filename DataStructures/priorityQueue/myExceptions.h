// exception classes for various error types

#ifndef myExceptions_
#define myExceptions_
#include <string>
#include <iostream>

// illegal parameter value
class illegalParameterValue
{
public:
	illegalParameterValue(std::string theMessage = "Illegal parameter value")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// illegal input data
class illegalInputData
{
public:
	illegalInputData(std::string theMessage = "Illegal data input")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// illegal index
class illegalIndex
{
public:
	illegalIndex(std::string theMessage = "Illegal index")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// matrix index out of bounds
class matrixIndexOutOfBounds
{
public:
	matrixIndexOutOfBounds
	(std::string theMessage = "Matrix index out of bounds")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// matrix size mismatch
class matrixSizeMismatch
{
public:
	matrixSizeMismatch(std::string theMessage =
		"The size of the two matrics doesn't match")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// stack is empty
class stackEmpty
{
public:
	stackEmpty(std::string theMessage =
		"Invalid operation on empty stack")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// queue is empty
class queueEmpty
{
public:
	queueEmpty(std::string theMessage =
		"Invalid operation on empty queue")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// hash table is full
class hashTableFull
{
public:
	hashTableFull(std::string theMessage =
		"The hash table is full")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// edge weight undefined
class undefinedEdgeWeight
{
public:
	undefinedEdgeWeight(std::string theMessage =
		"No edge weights defined")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// method undefined
class undefinedMethod
{
public:
	undefinedMethod(std::string theMessage =
		"This method is undefined")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

// empty tree
class emptyTree
{
public:
	emptyTree(std::string theMessage = "This tree is empty")
	{
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

#endif