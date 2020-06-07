
#include "arrayStack.h"

void printMatchedPairs(std::string expr)
{
	arrayStack<int> s;
	auto length = expr.size();

	for (size_t i = 0; i < length; ++i)
		if (expr.at(i) == '(')
			s.push(i);
		else
			if(expr.at(i) == ')')
				try {
				std::cout << s.top() << ' ' << i << std::endl;
				s.pop();
			}
	catch (stackEmpty) {
		std::cout << "No match for left parenthesis at " << s.top() << std::endl;
		s.pop();
	}
}

void testPrintMatchedPairs()
{
	std::string s1("(a*(b+c)+d)");
	printMatchedPairs(s1);
}