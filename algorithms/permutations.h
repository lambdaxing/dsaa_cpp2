// some algorithms about permutataions

#ifndef ALGORITHMS_PERMUTATIONS_
#define ALGORITHMS_PERMUTATIONS_

#include <iostream>
#include <algorithm>
#include <iterator>

// output all permutations of n elements
template<typename T>
void permutations(T list[], int k, int m)
{// Generate all permutations of list[k:m].
 // Assume k <= m.
	if (k == m) {
		// list[k:m] has one permutation. output it
		std::copy(list, list + m + 1, std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	}
	else // list[k,m] has more than one permutation
		 // generate these recursively
		for (int i = k; i <= m; i++)	// generate ei.perm(Ei) in E{ei, ... , en} recursively
		{
			using std::swap();
			swap(list[k], list[i]);
			permutations(list, k + 1, m);
			swap(list[k], list[i]);
		}
}

// use stl
template<typename T>
void permutations2(T list[], int k, int m)
{
	std::sort(list, list + m + 1);
	do {
		std::copy(list, list + m + 1, std::ostream_iterator<T>(std::cout, ""));
		std::cout << std::endl;
	} while (std::next_permutation(list, list + m + 1));

}

template<typename T>
void n_permutations(T* list, int k, int m)
{
	do {
		copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
		cout << endl;
	} while (next_permutation(list, list + m + 1));
}

template<typename T>
void p_permutations(T* list, int k, int m)
{
	while (prev_permutation(list, list + m + 1))
	{
		copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
		cout << endl;
	}
}

template<typename T>
void permutations3(T* list, int k, int m)
{
	auto p = new T[m + 1];
	copy(list + k, list + m + 1, p + k);
	n_permutations(list, k, m);
	p_permutations(p, k, m);
	delete[]p;
}

template<typename T>
void permutations4(T list[], int k, int m)
{
	while (prev_permutation(list, list + m + 1));
	do {
		copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
		cout << endl;
	} while (next_permutation(list, list + m + 1));
}

#endif // !ALGORITHMS_PERMUTATIONS_
