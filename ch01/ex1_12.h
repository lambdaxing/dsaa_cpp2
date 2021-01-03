#pragma once

template<typename T, size_t N>
void make2dArray(T**& x, size_t numberOfRows, const size_t(&rowSize)[N])
{
	x = new T* [ numberOfRows ];
	for (size_t i = 0; i < numberOfRows; ++i)
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

