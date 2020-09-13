// task struct used in machine shop sumulation

#ifndef task_
#define task_

//
struct task
{
	int machine;	// machine that performs the process
	int time;		// the time required to complete the process

	task(int theMachine = 0, int theTime = 0)
	{
		machine = theMachine;
		time = theTime;
	}
};

#endif // !task_
