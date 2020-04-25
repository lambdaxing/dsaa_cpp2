#pragma once

template<typename T>
void permutations(T list[], int k, int m)
{
	if (k == m) {
		copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
		cout << endl;
	}
	else {
		for (int i = k; i <= m; ++i)
		{
			swap(list[k], list[i]);
			permutations(list, k + 1, m);
			swap(list[k], list[i]);
		}
	}
}