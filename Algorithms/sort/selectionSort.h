#pragma  once			// early terminating selection sort
#include <iostream>
#include <algorithm>	// has copy
#include <iterator>
using namespace std;

//		statement										s/e				frequency			total steps
template <typename T>				
void selectionSort(T a[], int n)
{// Early-terminating version of selection sort.
	bool sorted = false;							 //	1					1					
	for (int size = n; !sorted && (size > 1); --size)// 1					2,n					Omega(1),O(n)		
	{
		int indexOfMax = 0;							 //	1					1,n-1				Omega(1),O(n)
		sorted = true;								 //	1					1,n-1				Omega(1),O(n)
		for (int i = 1; i < size; ++i)				 // 1					n,(n-1)n/2			Omega(n),O(n^2)	
			if (a[indexOfMax] <= a[i]) indexOfMax = i;//1					n-1,(n-1)n/2		Omega(n),O(n^2)
			else sorted = false;					 // 1					0,(n-1)n/2	        Omega(0),O(n^2)
		swap(a[indexOfMax], a[size - 1]);			 // 1					1,n-1				Omega(1),O(n)
	}
}
// total																						Omega(n),O(n^2)
//				t(n) = Omega(n) = O(n^2)

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