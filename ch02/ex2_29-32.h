#pragma once
#include <iostream>

// 29)
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c2/e29.htm

int stepCount = 0;
// 29-1)
void d(int x[], int n)
{
	for (int i = 0; i < n; i += 2)
	{
		++stepCount;	// the comparing in the for
		x[i] += 2;
		++stepCount;	// x[i] += 2;
	}
	++stepCount;		// last comparing in the for
	int i = 1;
	++stepCount;		// int i = 1;
	while (i <= n / 2)
	{
		++stepCount;	// the comparing in the while
		x[i] += x[i + 1];
		++stepCount;	// x[i] += x[i+1];
		++i;
		++stepCount;	// ++i;
	}
	++stepCount;		// last comparing in the while
}
// 29-2)
void dd(int x[], int n)
{
	for (int i = 0; i < n; i += 2)
		stepCount += 2;
	int i = 1;
	while (i++ <= n / 2)
		stepCount += 3;
	stepCount += 3;
}

int ex2_29_2()
{
	int a[5]{ 1,2,3,4,5 };
	d(a, 5);
	std::cout << stepCount << std::endl;
	stepCount = 0;
	dd(a, 5);
	std::cout << stepCount << std::endl;
	return 0;
}

// 29-3)
// ((n+1)/2)*2 + (n/2)*3 + 3
int ex2_29_3()
{
	int a[5]{ 1,2,3,4,5 };
	stepCount = 0;
	dd(a, 5);
	std::cout << stepCount << std::endl;
	std::cout << ((5 + 1) / 2) * 2 + (5 / 2) * 3 + 3 << std::endl;
	std::cout << 5 + 4 + 5 / 2 + 5 / 2 + 5 / 2 << std::endl;
	return 0;
}

// 29-4)
//		statement						s/e				frequency			total steps
void ddd(int x[], int n)			//	 0					0					0
{									//	 0					0					0	
	for (int i = 0; i < n; i += 2)	//	 1				(n+1)/2 +1			(n+1)/2 +1			
		x[i] += 2;					//   1				(n+1)/2				(n+1)/2
	int i = 1;						//	 1					1					1
	while (i <= n / 2)				//   1				 n/2 + 1			 n/2 + 1
	{								//	 0					0					0
		x[i] += x[i + 1];			//	 1					n/2					n/2
		++i;						//	 1					n/2					n/2
	}								//	 0					0					0
}									//	 0					0					0
//		total															   n + 4 + n/2 + n/2 + n/2											

// 30)
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c2/e30.htm

// 31)
// https://www.cise.ufl.edu/~sahni/dsaac/public/exer/c2/e31.htm

// 32)
// 32-1)
// n+3
// 32-2)
// (n+9)/2
// 32-3) 
// n+3