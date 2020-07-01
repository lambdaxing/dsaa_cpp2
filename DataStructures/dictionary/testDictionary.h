#pragma once
#include "sortedChain.h"
#include "sortedArrayList.h"
#include "skipList.h"
#include <iostream>

void testDictionary()
{
	sortedChain<std::string,std::string> dc;
	//sortedArrayList<std::string,std::string> da;
	skipList<std::string, std::string> ds("zzzzzzzzzz");
	std::string k, v;
	while (std::cin >> k >> v)
	{
		std::pair<std::string, std::string> t(k, v);
		dc.insert(t);
		//da.insert(t);
		ds.insert(t);
	}

	std::cout << dc << std::endl;
	std::cout << ds << std::endl;
}