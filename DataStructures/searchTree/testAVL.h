#pragma once
#include "avlTree.h"

void test()
{
	avlTree<int, char> avl;

	for (int i = 1; i <= 20; ++i)
		avl.insert(std::pair<int, char>(i, static_cast<char>(i + 96)));
	avl.ascend();
	std::cout << std::endl;

	for (int i = 1; i <= 10; ++i)
		avl.erase(i);
	avl.ascend();
	std::cout << std::endl;
}