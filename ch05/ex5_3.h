// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c5/e3.htm

#pragma once
#include <iostream>

template<typename T>
void changeLength2D(T **&x,int oldRow,int oldColum,int newRow, int newColum)
{
	/*if (newRow < 0 || newColum < 0)
		  throw illegalParameterValue("new length must be >= 0");*/

	T** temp = new T*[newRow];
	for (int i = 0; i < newRow; ++i)
	{
		temp[i] = new T[newColum];
		for (int j = 0; j < newColum; ++j)
			if (i < oldRow && j < oldColum) temp[i][j] = x[i][j];
			else temp[i][j] = {};
	}
	for (int i = 0; i < oldRow; ++i) delete[] x[i];
	delete[] x;
	x = temp;
}

int ex5_3()
{
	double** p = new double* [2];
	for (int i = 0; i < 2; ++i) {
		p[i] = new double[3];
		for (int j = 0; j < 3; ++j)
			p[i][j] = i + j;
	}
	std::cout << "original: \n";
	for (size_t i = 0; i < 2; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
			std::cout << p[i][j] << " ";
		std::cout << std::endl;
	}

	changeLength2D(p, 2, 3, 5, 6);
	std::cout << "changed: \n";
	for (size_t i = 0; i < 5; ++i)
	{
		for (size_t j = 0; j < 6; ++j)
			std::cout << p[i][j] << " ";
		std::cout << std::endl;
	}
	return 0;
}
