#pragma once
#include "linkedMatrix.h"

void testEx7_51()
{
	linkedMatrix<int> m1;
	std::cin >> m1;
	linkedMatrix<int> m2 = m1;
	std::cout << m1;
	for (int i = 1; i <= 4; ++i)
	{
		for (int j = 1; j <= 4; ++j)
		{
			std::cout << m1.get(i, j) << " ";
			m2.set(i, j, i * 10 + j);
		}
		std::cout << std::endl;
	}
	std::cout << m2;
	m2.print();
	linkedMatrix<int> m = m1 + m2;
	std::cout << m;
	m.print();
	m = m2 - m1;
	std::cout << m;
	std::cout << "m = m2 - m1:" << std::endl;
	m.print();
	m = m1 * m2;
	std::cout << m;
	std::cout << "m = m1 * m2:" << std::endl;
	m.print();
}
