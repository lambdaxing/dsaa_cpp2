#pragma once

#include <functional>
#include <iostream>
#include <time.h>

template<typename T>
void execute(std::function<void(T[], int)> f, T a[], int n, double clocksPerMillis);

template<typename T>
void compareTOf2F(std::function<void(T[], int)> f1, std::function<void(T[], int)> f2)
{
	int a[1000], step = 10;
	double clocksPerMillis = static_cast<double>(CLOCKS_PER_SEC) / 1000;

	std::cout << "\tf1           \tf2" << std::endl;
	std::cout << "n\tTime per Sort\tTime per Sort" << std::endl;

	for (int n = 0; n <= 1000; n += step)
	{
		
		execute(f1, a, n, clocksPerMillis);
		execute(f2, a, n, clocksPerMillis);
		std::cout << std::endl;
		if (n == 100) step = 100;
	}
}

template<typename T>
void execute(std::function<void(T[], int)> f, T a[], int n, double clocksPerMillis)
{
	long numberOfRepetitions = 0;
	clock_t startTime = clock();
	do
	{
		numberOfRepetitions++;

		for (int i = 0; i < n; i++)
			a[i] = n - i;

		f(a, n);
	} while (clock() - startTime < 1000);

	double elapsedMillis = (static_cast<double>(clock()) - startTime) / clocksPerMillis;
	std::cout << n << '\t' << elapsedMillis / numberOfRepetitions;
}