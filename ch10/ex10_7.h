#pragma once
#include <cstdlib>

float p;

int level()
{
	int l = 0;
	float r = std::rand();
	while (r > RAND_MAX * p)
	{
		p *= p;
		l++;
	}
}