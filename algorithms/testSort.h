#pragma once

#include <iterator>
#include "sort.h"

using namespace std;

int testBubbleSort()
{
	int a[10] = { 10,7,8,9,4, 2, 3, 6, 5,1 };

	// output the elements
	cout << "a[0:9] = ";
	copy(a, a + 10, ostream_iterator<int>(cout, " "));
	cout << endl;

	// sort
	bubbleSort(a, 10);

	// output the sorted sequence
	cout << "After the bubble sort, a[0:9] = ";
	copy(a, a + 10, ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}

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

int testRankSort()
{
	int a[6] = { 2, 6, 4, 3, 1, 5 };
	int r[6];

	// output the elements
	cout << "a[0:5] = ";
	copy(a, a + 6, ostream_iterator<int>(cout, " "));
	cout << endl;

	// sort
	rankOfSort(a, 6, r);
	rearrange(a, 6, r);

	// output the sorted sequence
	cout << "After the rank sort, a[0:5] = ";
	copy(a, a + 6, ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}

int testSelectionSort()
{
	int a[10] = { 3, 2, 4, 1, 6, 9, 8, 7, 5, 0 };

	// output the elements
	cout << "a[0:9] = ";
	copy(a, a + 10, ostream_iterator<int>(cout, " "));
	cout << endl;

	// sort
	selectionSort(a, 10);

	// output the sorted sequence
	cout << "After the selection sort, a[0:9] = ";
	copy(a, a + 10, ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;
}

void testSort()
{
	testBubbleSort();
	testInsertionSort();
	testRankSort();
	testSelectionSort();

}