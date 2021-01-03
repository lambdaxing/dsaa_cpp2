// iterative dynamic programming knapsack

#include <iostream>
#include <iterator>
#include <math.h>
#include "make2dArrayNoCatch.h"
#include "delete2dArray.h"

void knapsack(int* profit, int* weight, int numberOfObjects, int knapsackCapacity, int** f)
{// Iterative method to solove dynamic programming recurrence.
 // Computes f[1][knapsackCapacity] and f[i][y],
 // 2 <= i <= numberOfObjects, 0 <= y <= knapsackCapacity.
 // profit[1:numberOfObjects] gives object profits.
 // weight[1:numberOfObjects] gives object weights.

	// initialize f[numberOfObjects][]
	int yMax = std::min(weight[numberOfObjects] - 1, knapsackCapacity);
	for (int y = 0; y <= yMax; y++)
		f[numberOfObjects][y] = 0;
	for (int y = weight[numberOfObjects]; y <= knapsackCapacity; y++)
		f[numberOfObjects][y] = profit[numberOfObjects];

	// compute f[i][y], 1 < i < numberOfObjects
	for (int i = numberOfObjects - 1; i > 1; i--)
	{
		yMax = std::min(weight[i] - 1, knapsackCapacity);
		for (int y = 0; y <= yMax; y++)
			f[i][y] = f[i + 1][y];
		for (int y = weight[i]; y <= knapsackCapacity; y++)
			f[i][y] = std::max(f[i + 1][y], f[i + 1][y - weight[i]] + profit[i]);
	}

	// compute f[1][knapsackCapacity]
	f[1][knapsackCapacity] = f[2][knapsackCapacity];
	if (knapsackCapacity >= weight[1])
		f[1][knapsackCapacity] = std::max(f[1][knapsackCapacity], f[2][knapsackCapacity - weight[1]] + profit[1]);
}

void trackback(int** f, int* weight, int numberOfObjects, int knapsackCapacity, int* x)
{// Compute solution vector x.
	for (int i = 1; i < numberOfObjects; i++)
		if (f[i][knapsackCapacity] == f[i + 1][knapsackCapacity])
			// do not include object i
			x[i] = 0;
		else
		{// include object i
			x[i] = 1;
			knapsackCapacity -= weight[i];
		}
	x[numberOfObjects] = (f[numberOfObjects][knapsackCapacity] > 0) ? 1 : 0;
}

