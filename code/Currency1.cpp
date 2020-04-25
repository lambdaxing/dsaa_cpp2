#include "Currency1.h"

void Currency::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	if (theCents > 99)
		throw illegalParameterValue("Cents should be < 100");

	sign = theSign;
	dollars = theDollars;
	cents = theCents;
}

void Currency::setValue(double theAmount)
{
	if (theAmount < 0) { sign = minus; theAmount = -theAmount; }
	else sign = plus;
	dollars = static_cast<unsigned long>(theAmount);
	cents = static_cast<unsigned int>((theAmount + 0.001 - dollars) * 100);
}

Currency Currency::add(const Currency& x) const 
{
	long a1, a2, a3;
	Currency result;

	a1 = dollars * 100 + cents;
	if (sign == minus) a1 = -a1;

	a2 = x.dollars * 100 + x.cents;
	if (x.sign == minus) a2 = -a2;

	a3 = a1 + a2;

	if (a3 < 0) { result.sign = minus; a3 = -a3; }
	else result.sign = plus;

	result.dollars = a3 / 100;
	result.cents = a3 - result.dollars * 100;
	
	return result;
}

Currency& Currency::increment(const Currency& x)
{
	*this = add(x);
	return *this;
}

void Currency::output() const 
{
	if (sign == minus) cout << '-';
	cout << '$' << dollars << '.';
	if (cents < 10) cout << '0';
	cout << cents;
}