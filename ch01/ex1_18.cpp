#include "ex1_18.h"

Currency::Currency(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	setValue(theSign, theDollars, theCents);
}

void Currency::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	if (theCents > 99)
		/*throw illegalParameterValue("Cents should be < 100");*/
		throw std::runtime_error("Cents should be < 100");

	amount = theDollars * 100 + theCents;
	if (theSign == signType::minus) amount = -amount;
}

void Currency::setValue(double theAmount)
{
	// -> 0 £¿
	amount = theAmount < 0 ? static_cast<long>((theAmount - 0.001) * 100) : static_cast<long>((theAmount + 0.001) * 100);
}

Currency& Currency::operator=(const Currency& x)
{
	amount = x.amount;
	return *this;
}

Currency& Currency::operator=(double theAmount)
{
	amount = theAmount < 0 ? static_cast<long>((theAmount - 0.001) * 100) : static_cast<long>((theAmount + 0.001) * 100);
	return *this;
}

Currency& Currency::operator=(int theAmount)
{
	amount = theAmount;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const Currency& x)
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

std::istream& operator>>(std::istream& in, Currency& x)
{
	double t;
	in >> t;
	x = t;
	return in;
}

Currency operator+(const Currency& lhs, const Currency& rhs)
{
	Currency t(lhs);
	t += rhs;
	return t;
}

Currency operator-(const Currency& lhs, const Currency& rhs)
{
	Currency t(lhs);
	t -= rhs;
	return t;
}

Currency operator*(const Currency& lhs, const Currency& rhs)
{
	Currency t(lhs);
	t *= rhs;
	return t;
}

Currency operator/(const Currency& lhs, const Currency& rhs)
{
	Currency t(lhs);
	t /= rhs;
	return t;
}

Currency operator%(const Currency& lhs, const Currency& rhs)
{
	Currency t(lhs);
	t %= rhs;
	return t;
}

// test
int ex1_18()
{
	Currency c1, c2;
	cin >> c1 >> c2;

	cout << "c1 + c2 = " << c1 + c2 << endl;
	cout << "c1 - c2 = " << c1 - c2 << endl;
	cout << "c1 * c2 = " << c1 * c2 << endl;
	cout << "c1 / c2 = " << c1 / c2 << endl;
	cout << "c1 % c2 = " << c1 % c2 << endl;
	
	return 0;
}