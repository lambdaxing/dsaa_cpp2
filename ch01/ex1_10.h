#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

int abc1_10(int a, int b, int c)
{
	if (a < 0 && b < 0 && c < 0)
		throw std::runtime_error("1");
	if (a == 0 && b == 0 && c == 0)
		throw std::runtime_error("2");

	return a + b * c;
}

int ex1_10()
{
	int a, b, c;
	a = b = c = 0;

	try { abc1_10(a, b, c); }
	catch (std::runtime_error e)
	{
		std::cout << e.what();
		return std::stoi(e.what());
	}
	return 0;
}