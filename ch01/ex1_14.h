#pragma once
#include <iostream>
#include "ex1_12.h"

template<typename T,size_t N,size_t M>
void changeLength2D(T**& x,size_t numberOfRows, const size_t (&rowSize)[M], size_t newNumberOfRows, const size_t (&newRowSize)[N])
{
	auto p = new T* [ newNumberOfRows ];
	for (size_t i = 0; i < newNumberOfRows; ++i)
		p[i] = new T[newRowSize[i]];

	for (size_t i = 0; i < newNumberOfRows; ++i)
	{
		if (i < numberOfRows)
		{
			*p[i] = *x[i];
			for (size_t j = 0; j < newRowSize[i]; ++j)
			{
				if (j < rowSize[i]) p[i][j] = x[i][j];
				else p[i][j] = {};
			}
		}
		else
		{
			*p[i] = {};
			for (size_t j = 0; j < newRowSize[i]; ++j)
				p[i][j] = {};
		}
	}
	delete2dArray(x, numberOfRows);
	x = p;
}

int ex1te_14()
{
	auto p = new double*;
	size_t size[5]{ 1,2,3,4,5 };
	size_t newsize[6]{ 6,5,4,3,2,1 };
	make2dArray(p, 5, size);

	std::cout << "original: \n";
	for (size_t i = 0; i < 5; ++i)
	{
		for (size_t j = 0; j < size[i]; ++j)
		{
			p[i][j] = static_cast<double>(i) + static_cast<double>(j) / 10;
			std::cout << p[i][j] << " ";
		}
		std::cout << std::endl;
	}
		
	changeLength2D(p, 5, size, 6, newsize);
	std::cout << "changed: \n";
	for (size_t i = 0; i < 6; ++i)
	{
		for (size_t j = 0; j < newsize[i]; ++j)
			std::cout << p[i][j] << " ";
		std::cout << std::endl;
	}
	delete p;
	return 0;
}
