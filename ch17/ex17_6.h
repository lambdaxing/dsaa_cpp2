#pragma once

#include <queue>
#include <iostream>
#include <functional>
#include <vector>

typedef std::pair<int, int> task;		// first is start time and second is end time

struct machine
{
	std::vector<task> tasks;
	int endTime = 0;
};

struct compare
{
	bool operator()(const machine& lhs, const machine& rhs)
	{
		return lhs.endTime > rhs.endTime;
	}
};

std::priority_queue<task, std::vector<task>, std::greater<task>> tasks;
std::priority_queue<machine, std::vector<machine>, compare> machines;

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
	machine m;
	machines.push(m);

	while (!tasks.empty())
	{
		task c = tasks.top();
		tasks.pop();

		m = machines.top();
		if (c.first >= m.endTime)
		{
			m.tasks.push_back(c);
			m.endTime = c.second;
			machines.pop();
			machines.push(m);
		}
		else
		{
			machine newM;
			newM.tasks.push_back(c);
			newM.endTime = c.second;
			machines.push(newM);
		}
	}
}

void output()
{
	std::size_t i = 1;
	while (!machines.empty())
	{
		machine m = machines.top();
		machines.pop();
		std::cout << "machine " << i++ << ": " << std::endl;
		for (const auto& t : m.tasks)
		{
			std::cout << t.first << " " << t.second << std::endl;
		}
	}
}

void testEx17_6()
{
	input();
	disposal();
	output();
}
