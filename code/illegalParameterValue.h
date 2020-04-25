#pragma once
#include <iostream>
#include <string>

class illegalParameterValue
{
public:
	illegalParameterValue() :message("Illegal parameter value") {}
	illegalParameterValue(char* theMessage) { message = theMessage; }
	void outputMessage() { std::cout << message << std::endl; }
private:
	std::string message;
};

