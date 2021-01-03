// some algorithms about search

#ifndef ALGORITHMS_SEARCH_
#define ALGORITHMS_SEARCH_

#include <iostream>
#include <algorithm>
#include <iterator>

// binary search

template<typename T>
int binarySearch(T a[], int n, const T& x)
{// Search a[0] <= a[1] <= ... <= a[n-1] for x.
 // Return position if found; return -1 otherwise.
	int left = 0;                       // left end of segment
	int right = n - 1;                  // right end of segment
	while (left <= right) {
		int middle = (left + right) / 2;   // middle of segment
		if (x == a[middle]) return middle;
		if (x > a[middle]) left = middle + 1;
		else right = middle - 1;
	}
	return -1; // x not found
}
//			t(n) = Theta(logN)
int testBinarySearch()
{
	int a[7] = { 0, 2, 3, 4, 6, 7, 9 };
	// output the elements
	std::cout << "a[0:6] = ";
	std::copy(a, a + 7, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	// output the result
	std::cout << "Binary search the index of 4 in a[0:6] is: " << binarySearch(a, 7, 4) << std::endl;
	return 0;
}

#endif // !ALGORITHMS_SEARCH_
