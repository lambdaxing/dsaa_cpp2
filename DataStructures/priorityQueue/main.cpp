#include "lptSchedule.h"

int main()
{
	jobNode a[11];
	int n = 10;
	for (int i = 1; i <= n; ++i)
	{
		a[i].id = i;
		a[i].time = 2 * i * i;
	}
	makeSchedule(a, 10, 3);
}