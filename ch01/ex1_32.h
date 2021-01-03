#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
using namespace std;

template<typename T>
void permutations(T list[], int k, int m)
{
	while (prev_permutation(list, list + m + 1));
	do {
		copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
		cout << endl;
	} while (next_permutation(list, list + m + 1));
}

int ex1_32()
{
	char ch1[3]{ 'a','b','c' };
	cout << "ch1:\n";
	permutations(ch1, 0, 2);
	cout << endl;
	char ch2[3]{ 'c','b','a' };
	cout << "ch2:\n";
	permutations(ch2, 0, 2);
	cout << endl;
	char ch3[3]{ 'a','c','b' };
	cout << "ch3:\n";
	permutations(ch3, 0, 2);
	cout << endl;
	return 0;
}