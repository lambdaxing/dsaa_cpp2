// FIFO branch-and-bound loading code to find best loading and its value

#include <iostream>
#include <iterator>
#include <queue>

struct qNode
{
	// data members
	qNode* parent;			// pointer to parent node
	bool leftChild;			// true if left child of parent
	int weight;				// weight of partial solution defined by path to this node

	// constructor
	qNode(qNode* theParent, bool theLeftChild, int theWeight)
	{
		parent = theParent;
		leftChild = theLeftChild;
		weight = theWeight;
	}
};

// global variables
int numberOfContainers;
int maxWeightSoFar;
std::queue<qNode*> liveNodeQueue;
qNode* bestENodeSoFar;
int* bestLoading;

void addLiveNode(int, int, qNode*, bool);

int maxLoading(int *weight,int theNumberOfContainers,int capacity,int *theBestLoading)
{// FIFO branch-and-bound search of solution space.
 // weight[1:theNumberOfContainers] = container weights
 // capacity = ship capacity
 // theBestLoading[1:theNumberOfContainers] is set to best loading.
 // Return weight of best loading.
	// initialize globals
	numberOfContainers = theNumberOfContainers;
	maxWeightSoFar = 0;
	liveNodeQueue.push(nullptr);			// end-of-level marker
	qNode* eNode = nullptr;
	bestENodeSoFar = nullptr;
	bestLoading = theBestLoading;

	// initialize for level 1 E-node
	int eNodeLevel = 1;
	int eNodeWeight = 0;
	int remainingWeight = 0;
	for (int j = 2; j <= numberOfContainers; j++)
		remainingWeight += weight[j];

	// search subset space tree
	while (true)
	{
		// check left child of E-node
		int leftChildWeight = eNodeWeight + weight[eNodeLevel];
		if(leftChildWeight <= capacity)
		{// feasible left child
			if (leftChildWeight > maxWeightSoFar)
				maxWeightSoFar = leftChildWeight;
			addLiveNode(leftChildWeight, eNodeLevel, eNode, true);
		}

		// check right child 
		if (eNodeWeight + remainingWeight > maxWeightSoFar)
			addLiveNode(eNodeWeight, eNodeLevel, eNode, false);

		eNode = liveNodeQueue.front();
		liveNodeQueue.pop();
		if(eNode == nullptr)
		{// end of level
			if (liveNodeQueue.empty()) break;		// no more live nodes
			liveNodeQueue.push(nullptr);			// end-of-level pointer
			eNode = liveNodeQueue.front();
			liveNodeQueue.pop();
			eNodeLevel++;
			remainingWeight -= weight[eNodeLevel];
		}

		eNodeWeight = eNode->weight;
	}

	// construct bestLoading[] by following path from bestENodeSoFar to root,
	// bestLoaing[numberOfContainers] is set by addLiveNode
	for (int j = numberOfContainers - 1; j > 0; j--)
	{
		bestLoading[j] = (bestENodeSoFar->leftChild) ? 1 : 0;
		bestENodeSoFar = bestENodeSoFar->parent;
	}

	return maxWeightSoFar;
}

void addLiveNode(int theWeight, int theLevel, qNode* theParent, bool leftChild)
{// Add a live node at level theLevel and having weight theWeight
 // to liveNodeQueue if not a leaf. If feasible leaf, set 
 // bestLoading[numberOfContainers] = 1 if leftChild is true.
 // theParent = parent of nre node.
 // leftChild is true if new node if left child if theParent.
	if (theLevel == numberOfContainers)
	{// feasible leaf
		if (theWeight == maxWeightSoFar)
		{// best leaf so far
			bestENodeSoFar = theParent;
			bestLoading[numberOfContainers] = (leftChild) ? 1 : 0;
		}
		return;
	}
	// not a leaf, add to queue
	qNode* b = new qNode(theParent, leftChild, theWeight);
	liveNodeQueue.push(b);
}

void testFifoBBLoading3()
{
	int w[] = { 0,2,2,6,5,5 };
	int c = 16;
	int n = 5;
	int* x = new int[n + 1];
	std::cout << "Value of max loading is " << maxLoading(w, n, c, x) << std::endl;
	std::cout << "Loading vector is ";
	std::copy(x + 1, x + n + 1, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	delete[] x;
}
