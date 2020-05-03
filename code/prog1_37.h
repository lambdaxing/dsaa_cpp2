#pragma once
#include "illegalParameterValue.h"

template<typename T>
int indexOfMax(T a[], int n)
{// research the max in a[0:n-1]
	if (n <= 0) throw illegalParameterValue("n must be > 0");

	int indexOfMax = 0;
	for (int i = 1; i < n; ++i)
		if (a[indexOfMax] < a[i])
			indexOfMax = i;
	return indexOfMax;	// return the index
}