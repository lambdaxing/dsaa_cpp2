#include "Currency2.h"

Currency::Currency(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	setValue(theSign, theDollars, theCents);
}

void Currency::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	if (theCents > 99)
		throw illegalParameterValue("Cents should be < 100");

	amount = theDollars * 100 + theCents;
	if (theSign == minus) amount = -amount;
}

void Currency::setValue(double theAmount)
{
	// -> 0 £¿
	amount = theAmount < 0 ? static_cast<long>((theAmount - 0.001) * 100) : static_cast<long>((theAmount + 0.001) * 100);
}

Currency Currency::add(const Currency& x) const
{
	Currency y;
	y.amount = amount + x.amount;
	return y;
}

void Currency::output() const
{
	long theAmount = amount;
	if (theAmount < 0) { cout << '-'; theAmount = -theAmount; }
	long dollars = theAmount / 100;
	cout << '$' << dollars << '.';
	int cents = theAmount - dollars * 100;
	if (cents < 10) cout << '0';
	cout << cents;
}