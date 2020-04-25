#pragma once

#include <iostream>
using std::cout; using std::endl;
#include "illegalParameterValue.h"

enum signType { plus, minus };

class Currency
{
public:
	Currency(signType theSign = plus, unsigned long theDollars = 0, unsigned int theCents = 0);
	~Currency() = default;

	void setValue(signType, unsigned long, unsigned int);
	void setValue(double);
	signType getSign() const { return (amount < 0 ? minus : plus); }
	unsigned long getDollars() const { return (amount < 0 ? (-amount) / 100 : amount / 100); }
	unsigned int getCents() const { return (amount < 0 ? (-amount - getDollars() * 100) : (amount - getDollars() * 100)); }
	Currency add(const Currency&) const;
	Currency& increment(const Currency& x) { amount += x.amount; return *this; }
	void output() const;

private:
	long amount;
};

