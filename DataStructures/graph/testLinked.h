// test linked graph

#include "linkedWDigraph.h"
#include "linkedDigraph.h"
#include "linkedWGraph.h"
#include "linkedGraph.h"

template <typename T>
void testBase(linkedWDigraph<T>& g)
{
	std::cin >> g;
	std::cout << g;
}

void testBase(linkedDigraph& g)
{
	std::cin >> g;
	std::cout << g;
}

void testWDG()
{
	linkedWDigraph<int> wdg;
	testBase(wdg);
}

void testWG()
{
	linkedWGraph<int> wg;
	testBase(wg);
}

void testDG()
{
	linkedDigraph dg;
	testBase(dg);
}

void testG()
{
	linkedGraph g;
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

2 8
3 3
5 7   4 2
3 6
4 5

4 5
2 1 4
3 1 7
3 2 2
4 1 8
4 3 6

4 8   3 7   2 4
3 2   1 4
4 6   2 2   1 7
3 6   1 8

5 6
1 2
2 3
3 4
3 5
4 3
5 4

2
3
5  4
3
4

4 5
2 1
3 1
3 2
4 1
4 3

4  3  2
3  1
4  2  1
3  1

*/