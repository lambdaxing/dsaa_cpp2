#pragma once

#include "extendedDerivedArrayStack.h"
#include "extendedArrayStack.h"
#include "stackWithArrayList.h"
#include "twoStacks.h"
#include "extendedLinkedStack.h"

void testExtendedDerivedArrayStack()
{
	extendedDerivedArrayStack<int> s1;
	std::cin >> s1;
	std::cout << s1 << std::endl;
	extendedDerivedArrayStack<int> s2, s3;
	s1.split(s2, s3);
	std::cout << s2 << std::endl;
	std::cout << s3 << std::endl;
	s2.append(s3);
	std::cout << s2 << std::endl;
}

void testExtendedArrayStack()
{
	extendedArrayStack<int> s1;
	std::cin >> s1;
	std::cout << s1 << std::endl;
	extendedArrayStack<int> s2, s3;
	s1.split(s2, s3);
	std::cout << s2 << std::endl;
	std::cout << s3 << std::endl;
	s2.append(s3);
	std::cout << s2 << std::endl;
}

void testStackWithArrayList()
{
	stackWithArrayList<int> s1;
	for (int i = 1; i <= 5; ++i)
		s1.push(i);
	for (int i = 1; i <= 5; ++i, s1.pop())
		std::cout << s1.top() << " ";

}

void testTwoStacks()
{
	twoStacks<int> s;
	for (int i = 0; i <= 11; ++i)
	{
		s.push1(i);
		s.push2(i);
	}

	if(!s.empty1())
		s.output1(std::cout);
	std::cout << std::endl;
	if(!s.empty2())
		s.output2(std::cout);
}

void testExtendedLinkedStack()
{
	extendedLinkedStack<int> s1;
	std::cin >> s1;
	std::cout << s1 << std::endl;
}