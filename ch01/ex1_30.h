#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

template<typename T>
void permutations(T list[], int k, int m)
{
	sort(list, list + m + 1);
	do {
		copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
		cout << endl;
	} while (next_permutation(list, list + m + 1));

}

int ex1_30()
{
	char ch1[5]{ 'a','b','c','d','e' };
	cout << "ch1:\n";
	permutations(ch1, 0, 4);
	char ch2[5]{ 'e','d','c','b','a' };
	cout << "ch2:\n";
	permutations(ch2, 0, 4);
	return 0;
}