#pragma once
#include <iostream>

// 1-1
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c1/e9.htm
int abc(int a, int b, int c)
{
	return a + b * c;
}

float abc(float a, float b, float c)
{
	return a + b * c;
}

int ex1_9()
{
	// 1) ok (int,int,int)
	//std::cout << abc(1, 2, 3)				<< std::endl;

	// 2) ok (float,float,float)
	//std::cout << abc(1.0F, 2.0F, 3.0F)	<< std::endl;

	// 3) int converse to float or float converse to int ?
	//std::cout << abc(1, 2, 3.0F)			<< std::endl;

	// 4) double converse to int or float ?
	//std::cout << abc(1.0, 2.0, 3.0)		<< std::endl;

	return 0;
}