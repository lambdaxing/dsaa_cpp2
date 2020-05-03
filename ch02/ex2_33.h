#pragma once
#include <iostream>

int stepCount = 0;
// 33-1-1)
template<typename T>
void matrixMultiply(T** a, T** b, T** c, int m, int n, int p)
{
	for (int i = 0; i < m; ++i){
		++stepCount;						// the comparing in the for
		for (int j = 0; j < p; ++j)
		{
			++stepCount;					// the comparing in the for
			T sum = 0;
			++stepCount;					// T sum = 0;
			for (int k = 0; k < n; ++k) {
				++stepCount;				// the comparing in the for
				sum += a[i][k] * b[k][j];
				stepCount += 2;				// sum += a[i][k] * b[k][j]
			}
			++stepCount;					// last comparing in the for
			c[i][j] = sum;
			++stepCount;					// c[i][j] = sum
		}
		++stepCount;						// last comparing in the for
	}
	++stepCount;							// last comparing in the for
}
// 33-1-2)
template<typename T>
void matrixMultiplyd(T** a, T** b, T** c, int m, int n, int p)
{
	for (int i = 0; i < m; ++i) {
		stepCount += 2;					
		for (int j = 0; j < p; ++j)
		{
			stepCount += 4;
			for (int k = 0; k < n; ++k) {
				stepCount += 3;
			}
		}
	}
	++stepCount;							
}

int ex2_33_2()
{
	int a[5][4]{ { 1,2,3,4 },{ 1,2,3,4 },{ 1,2,3,4 },{ 1,2,3,4 },{ 1,2,3,4 } };
	int b[4][3]{ { 1,2,3 },{ 1,2,3 },{ 1,2,3 },{ 1,2,3 } };
	int c[5][3]{};

	int* ppa[5];
	for (int i = 0; i < 5; ++i)
		ppa[i] = a[i];
	int* ppb[4];
	for (int i = 0; i < 4; ++i)
		ppb[i] = b[i];
	int* ppc[5];
	for (int i = 0; i < 5; ++i)
		ppc[i] = c[i];

	matrixMultiply(ppa, ppb, ppc, 5, 4, 3);
	std::cout << stepCount << std::endl;
	stepCount = 0;
	matrixMultiplyd(ppa, ppb, ppc, 5, 4, 3);
	std::cout << stepCount << std::endl;
	return 0;
}

// 33-1-3)
// 2m+4mp+3mpn+1
int ex2_33_3()
{
	int a[5][4]{ { 1,2,3,4 },{ 1,2,3,4 },{ 1,2,3,4 },{ 1,2,3,4 },{ 1,2,3,4 } };
	int b[4][3]{ { 1,2,3 },{ 1,2,3 },{ 1,2,3 },{ 1,2,3 } };
	int c[5][3]{};

	int* ppa[5];
	for (int i = 0; i < 5; ++i)
		ppa[i] = a[i];
	int* ppb[4];
	for (int i = 0; i < 4; ++i)
		ppb[i] = b[i];
	int* ppc[5];
	for (int i = 0; i < 5; ++i)
		ppc[i] = c[i];

	matrixMultiply(ppa, ppb, ppc, 5, 4, 3);
	std::cout << stepCount << std::endl;
	std::cout << 2 * 5 + 4 * 5 * 3 + 3 * 5 * 3 * 4 + 1 << std::endl;
	int m = 5, n = 4, p = 3;
	std::cout << (3 * p * (n + 1) + p + 2) * m + 1 << std::endl;
	return 0;
}
										
// 33-1-4)
//			statement									s/e				frequency			total steps
template<typename T>
void matrixMultiplydd(T** a, T** b, T** c, int m, int n, int p)
{												//		 0					0					0
	for (int i = 0; i < m; ++i)					//		 1					m+1					m+1	
		for (int j = 0; j < p; ++j)				//		 1					m(p+1)				m(p+1)
		{										//		 0					0					0
			T sum = 0;							//		 1					m*p					m*p		
			for (int k = 0; k < n; ++k)			//		 1					m*p(n+1)			m*p(n+1)
				sum += a[i][k] * b[k][j];		//		 2					m*p*n				2mpn
			c[i][j] = sum;						//		 1					m*p					m*p
		}										//		 0					0					0
}												//		 0					0					0
//	total																					(3p(n+1)+p+2)m+1


// (33-2
// m = p ?