#pragma once

#include "arrayStack.h"

void towersOfHanoi(int n, int x, int y, int z)
{
	if (n > 0)
	{
		towersOfHanoi(n - 1, x, z, y);
		std::cout << "Move top disk from tower " << x << " to top of tower " << y << std::endl;
		towersOfHanoi(n - 1, z, y, x);
	}
}

arrayStack<int> tower[4];

void moveAndShow(int, int, int, int);

void towersOfHanoi(int n)
{
	for (int d = n; d > 0; --d)
		tower[1].push(d);

	moveAndShow(n, 1, 2, 3);
}

void showState()
{
	
}

void moveAndShow(int n, int x, int y, int z)
{
	if (n > 0)
	{
		moveAndShow(n - 1, x, z, y);
		int d = tower[x].top();
		tower[x].pop();
		tower[y].push(d);
		showState();
		moveAndShow(n - 1, z, y, x);
	}
}
