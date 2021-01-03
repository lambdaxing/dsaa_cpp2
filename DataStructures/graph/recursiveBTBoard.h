// backtracking method to find best board arrangement

#include <iostream>
#include <iterator>
#include "make2dArrayNoCatch.h"
#include "delete2dArray.h"

using std::swap;

// global variables
int numberOfBoards;
int numberOfNets;
int* partial;		// partial board permutation
int* bestPermutationSoFar;
int* boardsWithNet;
int* boardsInPartialWithNet;
int leastDensitySoFar;
int** board;		// 2D board array

void rBoard(int, int);

int arrangeBoards(int **theBoard,int theNumberOfBoards,int theNumberOfNets,int *bestPermutation)
{// Preprocessor for recursive backtracking function.
 // Return density of best arrangement.
	// initialize global variables
	numberOfBoards = theNumberOfBoards;
	numberOfNets = theNumberOfNets;
	partial = new int[numberOfBoards + 1];
	bestPermutationSoFar = bestPermutation;
	boardsWithNet = new int[numberOfNets + 1];
	std::fill(boardsWithNet + 1, boardsWithNet + numberOfNets + 1, 0);
	boardsInPartialWithNet = new int[numberOfNets + 1];
	std::fill(boardsInPartialWithNet + 1, boardsInPartialWithNet + numberOfNets + 1, 0);
	leastDensitySoFar = numberOfNets + 1;
	board = theBoard;

	// initialze partial to identity permutation
	// and compute boardsWithNet[]
	for (int i = 1; i < numberOfBoards; i++)
	{
		partial[i] = i;
		for (int j = 1; j <= numberOfNets; j++)
			boardsWithNet[j] += board[i][j];
	}

	// find best arrangement
	rBoard(1, 0);

	delete[] partial; delete[]boardsWithNet; delete[] boardsInPartialWithNet;

	return leastDensitySoFar;
}

// recursive backtracking search of permutation tree
void rBoard(int currentLevel, int densityOfPartial)
{// search from a node at level currentLevel
	if (currentLevel == numberOfBoards)
	{// all boards placed, we are at a better permutation
		for (int j = 1; j <= numberOfBoards; j++)
			bestPermutationSoFar[j] = partial[j];
		leastDensitySoFar = densityOfPartial;
	}
	else  // try out subtrees
		for (int j = currentLevel; j <= numberOfBoards; j++)
		{// try child with board partial[j] as next one

			// update boardsInPartialWithNet[]
			// and compute density at last slot
			int density = 0;
			for (int k = 1; k <= numberOfNets; k++)
			{
				boardsInPartialWithNet[k] += board[partial[j]][k];
				if (boardsInPartialWithNet[k] > 0 && boardsWithNet[k] != boardsInPartialWithNet[k])
					density++;// 在当前partial外还有元组k的电路板，这些电路板需要连接，从左（partial里)向右（partial外）需要一条线路连接
			}

			// update density to be overall density of partial arrangement
			if (densityOfPartial > density)
				density = densityOfPartial;

			// search subtree only if it may contain a beteer arrangement
			if (density < leastDensitySoFar)		// 这儿进行了判断，因此更新bestPermutation就无需判断，已是best了
			{// move to child
				swap(partial[currentLevel], partial[j]);
				rBoard(currentLevel + 1, density);
				swap(partial[currentLevel], partial[j]);
			}

			// reset boardsInPartialWithNet[]
			for (int k = 1; k <= numberOfNets; k++)
				boardsInPartialWithNet[k] -= board[partial[j]][k];
		}
}

void testRecursiveBTBoard()
{
	// input number of boards and nets
	std::cout << "Enter number of boards and number of nets" << std::endl;
	int n, m;
	std::cin >> n >> m;

	// define and input board array
	int** board;
	make2dArray(board, n + 1, m + 1);
	std::cout << "Enter net matrix" << std::endl;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			std::cin >> board[i][j];

	// define array for best board arrangement
	int* p = new int[n + 1];
	std::cout << "\nMinimum density is " << arrangeBoards(board, n, m, p) << std::endl;
	std::cout << "Optimal arrangement is ";
	std::copy(p + 1, p + n + 1, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	// destructor
	delete2dArray(board, n + 1);
	delete[] p;
}