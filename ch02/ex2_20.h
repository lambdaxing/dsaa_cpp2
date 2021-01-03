#pragma  once			// rank sort without additional array
#include <iostream>
#include <algorithm>	// has copy
#include <iterator>

int elementSwap = 0;
int rankSwap = 0;

template<class T>
void rearrange(T a[], int n, int r[])
{// In-place rearrangement into sorted order.
	for (int i = 0; i < n; ++i)
		// get proper element to a[i]
		while (r[i] != i)
		{
			using std::swap;
			int t = r[i];
			swap(a[i], a[t]);
			++elementSwap;
			swap(r[i], r[t]);
			++rankSwap;
		}
}

template<class T>
void rank1(T a[], int n, int r[])
{// Rank the n elements a[0:n-1].
 // Element ranks returned in r[0:n-1]
	for (int i = 0; i < n; ++i)
		r[i] = 0;  // initialize

	 // compare all element pairs
	for (int i = 1; i < n; ++i)
		for (int j = 0; j < i; ++j)
			if (a[j] <= a[i]) ++r[i];
			else ++r[j];
}

using namespace std;

int ex2_20()
{
	int a[6] = { 2, 6, 1, 3, 4, 5 };
	int r[6];

	// output the elements
	cout << "a[0:5] = ";
	copy(a, a + 6, ostream_iterator<int>(cout, " "));
	cout << endl;

	// sort
	rank1(a, 6, r);
	rearrange(a, 6, r);

	// output the sorted sequence
	cout << "After the rank sort, a[0:5] = ";
	copy(a, a + 6, ostream_iterator<int>(cout, " "));
	cout << endl;
	cout << " n - 1 = 6 -1 = 5" << endl;
	cout << "The num of element swap = " << elementSwap << endl;
	cout << "The num of rank swap = " << rankSwap << endl;

	return 0;
}