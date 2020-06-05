#pragma once

#include "sparseMatrix.h"

void testEx7_41()
{
	sparseMatrix<int> m1;
	std::cin >> m1;
	std::cout << std::endl << "<< m1:" << std::endl;
	std::cout << m1 << std::endl;

	sparseMatrix<int> m2(m1);
	std::cout << std::endl << "<< m2:" << std::endl;
	std::cout << m2 << std::endl;

	std::cout << "print m1:" << std::endl; 
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 4; ++j)
		{
			std::cout << m1.get(i, j) << " ";
			m2.set(i, j, i * 10 + j);
		}
		std::cout << std::endl;
	}

	std::cout << "print m2:" << std::endl;
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 4; ++j)
			std::cout << m2.get(i, j) << " ";
		std::cout << std::endl;
	}

	sparseMatrix<int> m = m1 * m2;
	std::cout << m;
	std::cout << "print m:" << std::endl;
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 4; ++j)
			std::cout << m.get(i, j) << " ";
		std::cout << std::endl;
	}
}