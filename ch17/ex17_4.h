#pragma once

#include <queue>
#include <iostream>
#include <functional>
#include <vector>

int price;
int payment;
int balance;

std::priority_queue<int> q;
std::vector<int> faceValue{ 10000, 2000, 1000, 500, 100, 25, 10, 5, 1 };
std::vector<int> result(9, 0);

bool input()
{
	std::cout << "Please enter the price and the payment:" << std::endl;
	std::cin >> price >> payment;
	if (payment < price)
	{
		std::cout << "The payment must be >= price." << std::endl;
		return false;
	}
	return true;
}

void init()
{
	q = std::priority_queue<int>(faceValue.cbegin(), faceValue.cend());
	balance = payment - price;
}

void dispose()
{
	std::size_t i = 0;

	while (balance > 0)
	{
		if (q.top() <= balance)
		{
			balance -= q.top();
			++result[i];
		}
		else
		{
			q.pop();
			++i;
		}
	}
}

void output()
{
	for (int i = 0; i < 9; i++)
		std::cout << faceValue[i] << " : " << result[i] << std::endl;
}

void testEx17_4()
{
	if (!input())
		return;
	init();
	dispose();
	output();
}