#pragma once

#include "sparseMatrix.h"

void testEx7_41()
{
	sparseMatrix<int> m1;
	std::cin >> m1;
	std::cout << m1;
	sparseMatrix<int> m2(m1);
	std::cout << m2;
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 4; ++j)
		{
			std::cout << m1.get(i, j) << " ";
			m2.set(i, j, i * 10 + j);
		}
		std::cout << std::endl;
	}
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 4; ++j)
			std::cout << m2.get(i, j) << " ";
		std::cout << std::endl;
	}
	
}