#pragma once

#include "Currency3.h"

int prog1_24()
{
	Currency g, h{ plus,3,50 }, i, j;

	g.setValue(minus, 2, 25);
	i.setValue(-6.45);

	j = h + g;
	cout << h << " + " << g << " = " << j << endl;

	j = i + g + h;
	cout << i << " + " << g << " + " << h << " = " << j << endl;

	cout << "Increment " << i << " by " << g << " and then add " << h << endl;
	j = (i += g) + h;
	cout << "Result is " << j << endl;
	cout << "Incremented object is " << i << endl;
	
	// test exception
	cout << "Attempting to initialize with cents = 152" << endl;
	try { i.setValue(plus, 3, 152); }
	catch (illegalParameterValue e)
	{
		cout << "Caught thrown exception" << endl;
		e.outputMessage();
	}

	return 0;
}