#pragma once

#include <iostream>
#include <time.h>
#include "compareTOf2F.h"

template<class T>
void insertionSort(T a[], int n)
{// Sort a[0:n-1] using the insertion sort method.
	for (int i = 1; i < n; i++)
	{// insert a[i] into a[0:i-1]
		T t = a[i];
		int j;
		for (j = i - 1; j >= 0 && t < a[j]; j--)
			a[j + 1] = a[j];
		a[j + 1] = t;           // The reason why there's "j+1" is that there is "j--" in the last loop of for 
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
	for (int i = 1; i < n; i++)
	{
		T t = a[i];
		insert(a, i, t);
	}
}


void ex4_2()
{
	compareTOf2F<int>(insertionSort<int>, insertionSort2<int>);
}