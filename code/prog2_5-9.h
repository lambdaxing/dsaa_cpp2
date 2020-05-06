#pragma once
#include "prog1_37.h"

template <typename T>
void rank(T a[], int n, int r[])
{// 给数组 a[0:n-1] 的 n 个元素排名次
 // 结果在 r[0:n-1] 中返回
	for (int i = 0; i < n; ++i)
		r[i] = 0;			// init

	// 比较所有元素对
	for (int i = 1; i < n; ++i)
		for (int j = 0; j < i; ++j)
			if (a[j] <= a[i]) ++r[i];
			else ++r[j];
}

// The Times of comparing: (n-1)n/2
// The Times of moving: 2n
template <typename T>
void rearrange(T a[],int n, int r[])
{// 使用一个附加数组 u ，将元素排序
	T* u = new T[n];

	// 把 a 中的元素移到 u 中正确的位置
	for (int i = 0; i < n; ++i)
		u[r[i]] = a[i];

	// 移回 a
	for (int i = 0; i < n; ++i)
		a[i] = u[i];

	delete[] u;
}

// The Times of comparing: n-1 + n-2 + ... + 1 = (n-1)n/2
// The Times of moving: 3(n-1)
template <typename T>
void selectionSort(T a[],int n)
{
	for (int size = n; size > 1; --size)
	{
		int j = indexOfMax(a, size);
		swap(a[j], a[size - 1]);
	}
}

template<typename T>
void bubble(T a[], int n)
{
	for (int i = 0; i < n - 1; ++i)
		if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
}

// The times of comparing: (n-1)n/2
// The times of moving:
template<typename T>
void bubbleSort(T a[], int n)
{
	for (int i = n; i > 1; --i)
		bubble(a, i);
}
