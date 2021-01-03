// divide and conquer function to find the index/location of the minimum and maximum elements in array a
#pragma once

#include <iostream>
#include <iterator>

template<typename T>
bool minmax(T a[], int n, int& indexOfMin, int& indexOfMax)
{// Locate min and max elements in a[0:n-1].
 // Return false if less than one element.
	if (n < 1) return false;

	if (n == 1)
	{
		indexOfMax = indexOfMin = 0;
		return true;
	}

	// n > 1
	int s = 1;		// start point for loop
	if (n % 2 == 1)	// n is odd
		indexOfMin = indexOfMax = 0;
	else
	{// n is even, compare first pair
		if (a[0] > a[1])
		{
			indexOfMin = 1;
			indexOfMax = 0;
		}
		else
		{
			indexOfMin = 0;
			indexOfMax = 1;
		}
		s = 2;
	}

	// compare remaining pairs
	for (int i = s; i < n; i += 2)
	{
		// find larger of a[i] and a[i+1],then compare larger one
		// with a[p.second] and smaller one with a[p.first]
		if (a[i] > a[i + 1])
		{
			if (a[i] > a[indexOfMax])
				indexOfMax = i;
			if (a[i + 1] < a[indexOfMin])
				indexOfMin = i + 1;
		}
		else
		{
			if (a[i + 1] > a[indexOfMax])
				indexOfMax = i + 1;
			if (a[i] < a[indexOfMin])
				indexOfMin = i;
		}
	}

	return true;
}

void testMinMax()
{
	int a[] = { 3,2,4,1,6,9,8,7,5,0 };
	int n = 10, theMin, theMax;

	// output the array elements
	std::cout << "a[0:9] = ";
	std::copy(a, a + n, std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	// locate min and max
	minmax(a, n, theMin, theMax);

	// output locations and values
	std::cout << "The min element is at " << theMin << std::endl << "Its value is " << a[theMin] << std::endl;
	std::cout << "The max element is at " << theMax << std::endl << "Its value is " << a[theMax] << std::endl;

}
