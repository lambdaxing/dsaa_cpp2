// test linked graph

#include "arrayWDigraph.h"
#include "arrayWGraph.h"
#include "arrayDigraph.h"
#include "arrayGraph.h"

template <typename T>
void testBase(arrayWDigraph<T>& g)
{
	std::cin >> g;
	std::cout << g;
}

void testBase(arrayDigraph& g)
{
	std::cin >> g;
	std::cout << g;

}
void testWDG()
{
	arrayWDigraph<int> wdg;
	testBase(wdg);
}

void testWG()
{
	arrayWGraph<int> wg;
	testBase(wg);
}

void testDG()
{
	arrayDigraph dg;
	testBase(dg);
}

void testG()
{
	arrayGraph g;
	testBase(g);
}

void test()
{
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