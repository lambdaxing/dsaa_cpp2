#pragma once
#include <iostream>
#include <stdexcept>
#include <string>

int abc1_10(int a, int b, int c)
{
	if (a < 0 && b < 0 && c < 0)
		throw 1;
	if (a == 0 && b == 0 && c == 0)
		throw 2;

	return a + b * c;
}

int ex1_10()
{
	int a, b, c;
	a = b = c = 0;

	try { abc1_10(a, b, c); }
	catch (int e)
	{
		std::cout << e;
		return e;
	}
	return 0;
}