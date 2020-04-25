#include "ex1_17.h"

Currency1_17::Currency1_17(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	setValue(theSign, theDollars, theCents);
}

void Currency1_17::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	if (theCents > 99)
		/*throw illegalParameterValue("Cents should be < 100");*/
		throw std::runtime_error("Cents should be < 100");


	amount = theDollars * 100 + theCents;
	if (theSign == signType::minus) amount = -amount;
}

void Currency1_17::setValue(double theAmount)
{
	// -> 0 £¿
	amount = theAmount < 0 ? static_cast<long>((theAmount - 0.001) * 100) : static_cast<long>((theAmount + 0.001) * 100);
}

Currency1_17 Currency1_17::add(const Currency1_17& x) const
{
	Currency1_17 y;
	y.amount = amount + x.amount;
	return y;
}

void Currency1_17::output() const
{
	long theAmount = amount;
	if (theAmount < 0) { cout << '-'; theAmount = -theAmount; }
	long dollars = theAmount / 100;
	cout << '$' << dollars << '.';
	int cents = theAmount - dollars * 100;
	if (cents < 10) cout << '0';
	cout << cents;
}


// 1)
void Currency1_17::input()
{
	double theAmout;
	cin >> theAmout;
	setValue(theAmout);
}

// 2)
Currency1_17 Currency1_17::subtract(const Currency1_17& x) const
{
	Currency1_17 y;
	y.amount = amount - x.amount;
	return y;
}

// 3)
Currency1_17 Currency1_17::precent(double theAmount) const
{
	Currency1_17 result;
	result.amount = modulus<long>()(amount, static_cast<long>(theAmount * 100));
	return result;
}

// 4)
Currency1_17 Currency1_17::multiply(double theAmount) const
{
	Currency1_17 result;
	result.amount = multiplies<double>()(amount, theAmount);
	return result;
}

// 5)
Currency1_17 Currency1_17::divide(double theAmount) const
{
	Currency1_17 result;
	result.amount = divides<double>()(amount, theAmount);
	return result;
}

// test
int ex1_17()
{
	double x, y;
	cin >> x >> y;
	Currency1_17 c1, c2, c3;
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