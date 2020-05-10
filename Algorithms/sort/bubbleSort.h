#pragma  once			// early terminating bubble sort
#include <iostream>
#include <algorithm>	// has copy
#include <iterator>

using namespace std;

template<typename T>
bool bubble(T a[], int n)
{// Bubble largest element in a[0:n-1] to right.
	bool swapped = false;
	for (int i = 0; i < n - 1; ++i) 
		if (a[i] > a[i + 1]) 
		{
			swap(a[i], a[i + 1]);
			swapped = true;		// swap
		}
	return swapped;
}

template<class T>
void bubbleSort(T a[], int n)			
{// Sort a[0:n - 1] using bubble sort.
	for (int i = n; i > 1 && bubble(a, i); i--);				//	1,n-1		Omega(n),O(n)	Omega(n),O(n^2)	
}
//		t(n) = Omega(n) = O(n^2)

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