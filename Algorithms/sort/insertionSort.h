#pragma once			// insertion sort
#include <iostream>
#include <algorithm>	// has copy
#include <iterator>
using namespace std;

template<typename T>
void insertionSort(T a[], int n)
{
	for (int i = 1; i < n; ++i)						//		1		n		
	{												
		T t = a[i];									//		1		n-1
		int j;										//		1		n-1
		for (j = i - 1; j >= 0 && t < a[j]; --j)	//		n-1		1,
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}

template<class T>
void insert(T a[], int n, const T& x)
{// Insert x into the sorted array a[0:n-1].
	int i;
	for (i = n - 1; i >= 0 && x < a[i]; i--)
		a[i + 1] = a[i];
	a[i + 1] = x;
}

template<class T>
void insertionSort2(T a[], int n)
{// Sort a[0:n-1] using the insertion sort method.
	for (int i = 1; i < n; i++)					//		1		n		O(n)
	{
		T t = a[i];								//		1		n-1		O(n)
		insert(a, i, t);						//		2i+4	n-1		O(n^2)
	}
}
//				t(n) = Omega(n) = O(n^2)

int testInsertionSort()
{
	int a[10] = { 3, 2, 4, 1, 6, 9, 8, 7, 5, 0 };

	// output the elements
	cout << "a[0:9] = ";
	copy(a, a + 10, ostream_iterator<int>(cout, " "));
	cout << endl;

	// sort
	insertionSort(a, 10);

	// output the sorted sequence
	cout << "After the insertion sort, a[0:9] = ";
	copy(a, a + 10, ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}