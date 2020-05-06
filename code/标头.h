#pragma once

template <typename T>
void insert(T a[], int& n, const T& x)
{// 把 x 插入到有序数组 a[0:n-1]
 // 假设数组 a 的容量大于 n 
	int i;
	for (i = n - 1; i >= 0 && x < a[i]; --i)
		a[i + 1] = a[i];
	a[i + 1] = x;
	++n;	// 数组 a 多了一个元素
}

// swap: 2(n-1)
template <typename T>
void rearrange(T a[], int n, int r[])
{
	for (int i = 0; i < n; ++i)
		while (r[i] != i)
		{
			int t = r[i];
			swap(a[i], a[t]);
			swap(r[i], r[t]);
		}
}

template <typename T>
void selectionSort(T a[], int n)
{// 及时终止的选择排序
	bool sorted = false;
	for (int size = n; !sorted && (size > 1); --size)
	{
		int indexOfMax = 0;
		sorted = true;
		for (int i = 1; i < size; ++i)
			if (a[indexOfMax] <= a[i]) indexOfMax = i;
			else sorted = false;
		swap(a[indexOfMax], a[size - 1]);
	}
}

template <typename T>
bool bubble(T a[], int n)
{
	bool swapped = false;
	for(int i =0; i< n -1;++i)
		if (a[i] > a[i + 1])
		{
			swap(a[i], a[i + 1]);
			swapped = true;
		}
	return swapped;
}

template <typename T>
void bubbleSort(T a[], int n)
{
	for (int i = n; i > 1 && bubble(a, i); --i);
}

template<typename T>
void insert(T a[], int n, const T& x)
{
	int i;
	for (i = n - 1; i >= 0 && x < a[i]; --i)
		a[i + 1] = a[i];
	a[i + 1] = x;
}

template <typename T>
void insertSort(T a[], int n)
{
	for (int i = 1; i < n; ++i)
	{
		T t = a[i];
		insert(a, i, t);
	}
}

template <typename T>
void insertionSort(T a[], int n)
{
	for (int i = 1; i < n; ++i)
	{
		T t = a[i];
		int j;
		for (j = i - 1; j >= 0 && t < a[j]; --j)
			a[j + 1] = a[j];
		a[j + 1] = t;
	}
}
