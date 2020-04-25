#include "Currency3.h"

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

Currency operator+(const Currency& lhs,const Currency& rhs)
{
	Currency t(lhs);
	t += rhs;
	return t;
}

std::ostream& operator<<(std::ostream& out,const Currency& x)
{
	long theAmount = x.amount;
	if (theAmount < 0) { out << '-'; theAmount = -theAmount; }
	long dollars = theAmount / 100;
	out << '$' << dollars << '.';
	int cents = theAmount - dollars * 100;
	if (cents < 10) out << '0';
	out << cents;
	return out;
}
