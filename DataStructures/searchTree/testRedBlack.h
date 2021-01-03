#pragma once
#include "redBlackTree.h"
#include <map>

const int num = 1000000;

void testRedBlack()
{
	redBlackTree<int, char> avl;

	for (int i = 1; i <= 20; ++i)
	{
		std::cout << avl.size() << std::endl;
		avl.insert(std::pair<int, char>(i, static_cast<char>(i + 96)));
	}
	avl.ascend();
	std::cout << std::endl;

	for (int i = 1; i <= 10; ++i)
	{
		std::cout << avl.size() << std::endl;
		avl.erase(i);
	}
	avl.ascend();
	std::cout << std::endl;
}

void testMapTime()
{
	std::map<char, int> m;

	for (int i = 1; i < num; ++i)
	{
		m.insert(std::pair<const char, int>(i, 'a'));
	}

	for (int i = 1; i < num; ++i)
	{
		auto f = m.find(i);
		std::cout << f->first << " : " << f->second;
	}
	std::cout << std::endl;
	for (int i = 1; i < num; ++i)
	{
		m.erase(i);
	}
	for (int i = 1; i < num; ++i)
	{
		auto f = m.find(i);
		if (f != m.end())
			std::cout << f->first << " : " << f->second;
	}
	std::cout << std::endl;
}

void testRedBlackTime()
{
	redBlackTree<int, char> m;

	for (int i = 1; i < num; ++i)
	{
		m.insert(std::pair<const int, char>(i, 'a'));
	}

	for (int i = 1; i < num; ++i)
	{
		auto f = m.find(i);
		std::cout << f->first << " : " << f->second;
	}
	std::cout << std::endl;
	for (int i = 1; i < num; ++i)
	{
		m.erase(i);
	}
	for (int i = 1; i < num; ++i)
	{
		auto f = m.find(i);
		if (f != nullptr)
			std::cout << f->first << " : " << f->second;
	}
	std::cout << std::endl;
}