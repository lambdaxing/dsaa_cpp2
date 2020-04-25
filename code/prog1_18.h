#pragma once

#include "Currency1.h"

int prog1_18()
{
	Currency g, h{ plus,3,50 }, i, j;

	g.setValue(minus, 2, 25);
	i.setValue(-6.45);

	j = h.add(g);
	h.output();
	cout << " + ";
	g.output();
	cout << " = ";
	j.output(); cout << endl;

	j = i.add(g).add(h);

	j = i.increment(g).add(h);

	cout << "Attempting to initialize with cents = 152" << endl;
	try { i.setValue(plus, 3, 152); }
	catch (illegalParameterValue e)
	{
		cout << "Caught thrown exception" << endl;
		e.outputMessage();
	}
	return 0;
}