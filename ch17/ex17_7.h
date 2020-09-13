#pragma once

#include <queue>
#include <iostream>
#include <functional>
#include <vector>

typedef std::pair<int, int> task;

struct compare
{
	bool operator()(const task& lhs, const task& rhs)
	{
		return (lhs.second - lhs.first) > (rhs.second - rhs.first);
	}
};

struct machine
{
	std::vector<task> tasks;
	int endTime = 0;

	bool check(const task& c)
	{
		for (const auto& i : tasks)
			if (c.first > i.first && c.first < i.second ||
				c.second >i.first && c.second < i.second ||
				c.first < i.first && c.second > i.second)
				return false;
		return true;
	}
};

std::priority_queue<task, std::vector<task>, compare> tasks;
machine m;

void input()
{
	std::size_t i = 0;
	while (true)
	{
		std::cout << "Please enter the start time and the end time of task " << i++ << ": ( enter Ctrl+Z to stop.)" << std::endl;
		task c;
		std::cin >> c.first;
		if (std::cin.eof())
			break;
		std::cin >> c.second;
		tasks.push(c);
	}
}

void disposal()
{
	while (!tasks.empty())
	{
		task c = tasks.top();
		tasks.pop();
		if (m.check(c))
			m.tasks.push_back(c);
	}
}

void output()
{
	for (const auto& i : m.tasks)
		std::cout << i.first << " " << i.second << std::endl;
}

void testEx17_7()
{
	input();
	disposal();
	output();
}

