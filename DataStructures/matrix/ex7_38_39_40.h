#include "sparseMatrix.h"

void testEx7_38()
{
	sparseMatrix<int> m1, m2, m3;
	std::cin >> m1;
	m1.transpose(m2);
	m1.add(m2, m3);
	std::cout << m1 << std::endl << m2 << std::endl << m3;
}

// ex7_39
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c7/e39.htm
// ex7_40
// 