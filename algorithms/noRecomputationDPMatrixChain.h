// Second version of recursive dynamic programming solution for
// the maxtrix multiplication chains problem, this version computes each c(i,j) at most once

#include <iostream>
#include "make2dArrayNoCatch.h"
#include "delete2dArray.h"

// global variables
int* r;		// r[i] is number of row in matrix i
int** kay;	// recurrence selector
int** theC;

int c(int i, int j)
{// Return c(i,j) and compute kay[i][j] = kay(i,j).
	// check if alreay computed
	if (theC[i][j] > 0)  // c(i,j) was computed earlier
		return theC[i][j];

	// c(i,j) not computed before, compute it now
	if (i == j)
		return 0;		// one matrix
	if(i == j - 1)
	{// two matrices
		kay[i][i + 1] = i;
		theC[i][j] = r[i] * r[i + 1] * r[i + 2];
		return theC[i][j];
	}

	// more than two matrices
	// set u to min term for k = i
	int u = c(i, i) + c(i + 1, j) + r[i] * r[i + 1] * r[j + 1];
	kay[i][j] = i;

	// compute remaining min terms and update u
	for (int k = i + 1; k < j; k++)
	{
		int t = c(i, k) + c(k + 1, j) + r[i] * r[k + 1] * r[j + 1];
		if(t < u)
		{// smaller min term found, update u and kay[i][j]
			u = t;
			kay[i][j] = k;
		}
	}

	theC[i][j] = u;
	return theC[i][j];
}

void trackback(int i, int j)
{// Output best way to compute Mij.
	if (i == j) // only one matrix
		return;
	trackback(i, kay[i][j]);
	trackback(kay[i][j] + 1, j);
	std::cout << "Multiply M " << i << ", " << kay[i][j] << " and M " << (kay[i][j] + 1) << ", " << j << std::endl;
}

void testRecursiveDPMatrixChain()
{
	// initialize
	std::cout << "Enter number of matrices" << std::endl;
	int q;
	std::cin >> q;
	r = new int[q + 2];
	make2dArray(kay, q + 1, q + 1);

	// input matrix data
	for (int i = 1; i <= q; i++)
	{
		std::cout << "Enter number of rows in matrix" << i << std::endl;
		std::cin >> r[i];
	}
	std::cout << "Enter number of columns in matrix " << q << std::endl;
	cin >> r[q + 1];

	// compute cost of best way to multiply
	std::cout << "Minimum cost is " << c(1, q) << std::endl;

	// output optimal mutiplication sequence
	trackback(1, q);

	delete2dArray(kay, q + 1);
}
