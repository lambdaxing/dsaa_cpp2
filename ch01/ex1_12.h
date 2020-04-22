#pragma once

template<typename T, size_t N>
void make2dArray(T**& x, int numberOfRows, const T(&rowSize)[N])
{
	x = new T* { numberOfRows };
	for (int i = 0; i < numberOfRows; ++i)
		x[i] = new T[rowSize[i]];
}

template<typename T>
void delete2dArray(T**& x, int numberOfRows)
{
	for (int i = 0; i < numberOfRows; ++i)
		delete[]x[i];

	delete[]x;
	x = nullptr;
}

