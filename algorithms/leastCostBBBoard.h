// least-cost branch-and-bound method to find best board arrangement

#include <iostream>
#include <queue>
#include "make2dArrayNoCatch.h"
#include "delete2dArray.h"

struct heapNode
{
	// data members
	int partialDensity;		// density of partial arrangement
	int* boardsInPartialWithNet;
	int sizeOfPartial;		// partial arrangement is partial[1:sizeOfPartial]
	int* partial;			// partial[sizeOfPartial+1:numberOfBoards] gives remainning boards to be added to partial[1:sizeOfPartial]

	// constructors
	heapNode() {}

	heapNode(int thePartialDensity, int* theBoardsInPartialWithNet, int theSizeOfPartial, int* thePartial)
		:partialDensity(thePartialDensity), boardsInPartialWithNet(theBoardsInPartialWithNet), sizeOfPartial(theSizeOfPartial), partial(thePartial) {}

	operator int() { return partialDensity; }

	bool operator<(const heapNode rhs) const
	{
		return partialDensity > rhs.partialDensity;
	}
};

int leastCostBBBoards(int** board, int numberOfBoards, int numberOfNets, int* bestPermutation)
{// Least-cost branch-and-bound code.
 // Return density of best arrangement.
	std::priority_queue<heapNode> liveNodeMinHeap;

	// initialize first E-node (partialDensity,boardsInPartialWithNet,sizeOfPartial,partial)
	heapNode eNode(0, new int[numberOfNets + 1], 0, new int[numberOfBoards + 1]);

	// set eNode.boardsInPartialWithNet[i] = number of boards in partial[1:s] with net i
	// set eNode.partial[i] = i,initial permutation
	// set eNode.boardsWithNet[i] = number of boards with net i
	int* boardsWithNet = new int[numberOfNets + 1];
	std::fill(boardsWithNet + 1, boardsWithNet + numberOfNets + 1, 0);
	std::fill(eNode.boardsInPartialWithNet, eNode.boardsInPartialWithNet + numberOfNets + 1, 0);
	for (int i = 1; i <= numberOfBoards; i++)
	{
		eNode.partial[i] = i;
		for (int j = 1; j <= numberOfNets; j++)
			boardsWithNet[j] += board[i][j];
	}

	int leastDensitySoFar = numberOfNets + 1;
	int* bestPermutationSoFar = nullptr;

	do {// expand E-node
		if (eNode.sizeOfPartial == numberOfBoards - 1)
		{// one child only
			int localDensityAtLastBoard = 0;
			for (int j = 1; j <= numberOfNets; j++)
				localDensityAtLastBoard += board[eNode.partial[numberOfBoards]][j];
			if (localDensityAtLastBoard < leastDensitySoFar)			// why there is better permutation ?
			{// better permutation
				bestPermutationSoFar = eNode.partial;
				eNode.partial = nullptr;
				leastDensitySoFar = std::max(localDensityAtLastBoard, eNode.partialDensity);
			}
		}
		else
		{// generate children of E-node
			for (int i = eNode.sizeOfPartial + 1; i <= numberOfBoards; i++)
			{
				heapNode hNode(0, new int[numberOfNets + 1], 0, new int[numberOfBoards + 1]);
				for (int j = 1; j <= numberOfNets; j++)
					// account for nets in new board
					hNode.boardsInPartialWithNet[j] = eNode.boardsInPartialWithNet[j] + board[eNode.partial[i]][j];
				int localDensityAtNewBoard = 0;
				for (int j = 1; j <= numberOfNets; j++)
					if (hNode.boardsInPartialWithNet[j] > 0 && boardsWithNet[j] != hNode.boardsInPartialWithNet[j])
						localDensityAtNewBoard++;
				hNode.partialDensity = std::max(localDensityAtNewBoard, eNode.partialDensity);

				if (hNode.partialDensity < leastDensitySoFar)
				{// may lead to better leaf
					hNode.sizeOfPartial = eNode.sizeOfPartial + 1;
					for (int j = 1; j <= numberOfBoards; j++)
						hNode.partial[j] = eNode.partial[j];
					hNode.partial[hNode.sizeOfPartial] = eNode.partial[i];
					hNode.partial[i] = eNode.partial[hNode.sizeOfPartial];
					liveNodeMinHeap.push(hNode);
				}
			}
		}

		// next E-node
		delete[] eNode.partial;
		delete[] eNode.boardsInPartialWithNet;
		if (liveNodeMinHeap.empty()) break;
		eNode = liveNodeMinHeap.top();
		liveNodeMinHeap.pop();
	} while (eNode.partialDensity < leastDensitySoFar);

	for (int i = 1; i <= numberOfBoards; i++)
		bestPermutation[i] = bestPermutationSoFar[i];
	return leastDensitySoFar;
}

void testLeastCostBBBoard()
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

	std::cout << "\nMinimum density is " << leastCostBBBoards(board, n, m, p) << std::endl;
	std::cout << "Optimal arrangement is ";
	std::copy(p + 1, p + n + 1, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	delete[] p; delete2dArray(board, n + 1);
}

/* output 

Enter number of boardsand number of nets
8 5
Enter net matrix
0 0 1 0 0
0 1 0 0 0
0 1 1 1 0
1 0 0 0 0
1 0 0 0 0
1 0 0 1 0
0 0 0 0 1
0 0 0 0 1

Minimum density is 2
Optimal arrangement is 8 7 5 4 6 1 3 2

*/