#include "ex1_16.h"

void Currency1_16::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	if (theCents > 99)
		/*throw illegalParameterValue("Cents should be < 100");*/
		throw std::runtime_error("Cents should be < 100");

	sign = theSign;
	dollars = theDollars;
	cents = theCents;
}

void Currency1_16::setValue(double theAmount)
{
	if (theAmount < 0) { sign = signType::minus; theAmount = -theAmount; }
	else sign = signType::plus;
	dollars = static_cast<unsigned long>(theAmount);
	cents = static_cast<unsigned int>((theAmount + 0.001 - dollars) * 100);
}

Currency1_16 Currency1_16::add(const Currency1_16& x) const
{
	long a1, a2, a3;
	Currency1_16 result;

	a1 = dollars * 100 + cents;
	if (sign == signType::minus) a1 = -a1;

	a2 = x.dollars * 100 + x.cents;
	if (x.sign == signType::minus) a2 = -a2;

	a3 = a1 + a2;

	if (a3 < 0) { result.sign = signType::minus; a3 = -a3; }
	else result.sign = signType::plus;

	result.dollars = a3 / 100;
	result.cents = a3 - result.dollars * 100;

	return result;
}

Currency1_16& Currency1_16::increment(const Currency1_16& x)
{
	*this = add(x);
	return *this;
}

void Currency1_16::output() const
{
	if (sign == signType::minus) cout << '-';
	cout << '$' << dollars << '.';
	if (cents < 10) cout << '0';
	cout << cents;
}

// 1)
void Currency1_16::input() 
{
	double theAmout;
	cin >> theAmout;
	setValue(theAmout);
}

// 2)
Currency1_16 Currency1_16::subtract(const Currency1_16& x) const
{
	double theAmount = x.dollars + static_cast<double>(x.cents) / 100;
	Currency1_16 result;
	result.setValue(std::minus<double>()(getDouble(), theAmount));
	return result;
}

// 3)
Currency1_16 Currency1_16::precent(double theAmount) const
{
	Currency1_16 result;
	long t = modulus<long>()(getLong(), static_cast<long>(theAmount * 100));
	result.dollars = t / 100;
	result.cents = t - result.dollars * 100;
	return result;
}

// 4)
Currency1_16 Currency1_16::multiply(double theAmount) const
{
	Currency1_16 result;
	result.setValue(multiplies<double>()(getDouble(), theAmount));
	return result;
}

// 5)
Currency1_16 Currency1_16::divide(double theAmount) const 
{
	Currency1_16 result;
	result.setValue(divides<double>()(getDouble(), theAmount));
	return result;
}

// test
int ex1_16()
{
	double x, y;
	cin >> x >> y;
	Currency1_16 c1, c2, c3;
	c1.setValue(x);
	c2.setValue(y);

	cout << "c1 - c2 = ";
	c3 = c1.subtract(c2);
	c3.output();
	cout << endl;

	cout << "c1 % y = ";
	c3 = c1.precent(y);
	c3.output();
	cout << endl;

	cout << "c1 * y = ";
	c3 = c1.multiply(y);
	c3.output();
	cout << endl;

	cout << "c1 / y = ";
	c3 = c1.divide(y);
	c3.output();
	cout << endl;

	return 0;
}