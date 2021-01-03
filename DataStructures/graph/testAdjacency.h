// test adjacency graph

#include "adjacencyWDigraph.h"
#include "adjacencyWGraph.h"
#include "adjacencyDigraph.h"
#include "adjacencyGraph.h"

template <typename T>
void testBase(adjacencyWDigraph<T>& g)
{
	std::cin >> g;
	std::cout << g;
}

void testWDG()
{
	adjacencyWDigraph<int> wdg;
	testBase(wdg);
}

void testWG()
{
	adjacencyWGraph<int> wg;
	testBase(wg);
}

void testDG()
{
	adjacencyDigraph dg;
	testBase(dg);
}

void testG()
{
	adjacencyGraph g;
	testBase(g);
}

void test()
{
	testWDG();
	testWG();
	testDG();
	testG();
}

/*
5 6
1 2 8
2 3 3
3 4 2
3 5 7
4 3 6
5 4 5
0  8  0  0  0
0  0  3  0  0
0  0  0  2  7
0  0  6  0  0
0  0  0  5  0
4 5
2 1 4
3 1 7
3 2 2
4 1 8
4 3 6
0  4  7  8
4  0  2  0
7  2  0  6
8  0  6  0
5 6
1 2
2 3
3 4
3 5
4 3
5 4
0  1  0  0  0
0  0  1  0  0
0  0  0  1  1
0  0  1  0  0
0  0  0  1  0
4 5
2 1
3 1
3 2
4 1
4 3
0  1  1  1
1  0  1  0
1  1  0  1
1  0  1  0
*/