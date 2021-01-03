// output LPT schedules

#include <iostream>
#include "minHeap.h"
#include "heapSort.h"
#include "lptNodes.h"

void makeSchedule(jobNode a[], int n, int m)
{// Output an m machine LPT schedule for the jobs a[1:n].
	if (n <= m)
	{
		std::cout << "Schedule each job on a different machine." << std::endl;
		return;
	}

	heapSort(a, n);		// in ascending order

	// initialize m machinese and the min heap
	minHeap<machineNode> machineHeap(m);
	for (int i = 1; i <= m; ++i)
		machineHeap.push(machineNode(i, 0));

	// construct schedule
	for (int i = n; i >= 1; --i)
	{// schedule job i on first free machine
		machineNode x = machineHeap.top();
		machineHeap.pop();
		std::cout << "Schedule job " << a[i].id << " on machine " << x.id << " from " << x.avail << " to " << (x.avail + a[i].time) << std::endl;
		x.avail += a[i].time;	// new available time for this machine
		machineHeap.push(x);
	}
}