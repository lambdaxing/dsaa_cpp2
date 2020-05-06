#pragma once

//		statement										s/e				frequency			total steps
template <typename T>				
void selectionSort(T a[], int n)
{
	bool sorted = false;							 //	1					1					1
	for (int size = n; !sorted && (size > 1); --size)// 1					n					2,n		
	{
		int indexOfMax = 0;							 //	1					1,n-1				1,n-1
		sorted = true;								 //	1					1,n-1				1,n-1
		for (int i = 1; i < size; ++i)				 // 1					2,n*(n-1)			2,n*(n-1)	
			if (a[indexOfMax] <= a[i]) indexOfMax = i;//1/0					n-1,(n-1)^2			n-1,0
			else sorted = false;					 // 0/1					n-1,(n-1)^2	        0,(n-1)^2
		swap(a[indexOfMax], a[size - 1]);			 // 1					1,n-1				1,n-1
	}
}
// total																						n+7,2n^2+n-2