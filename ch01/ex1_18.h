#pragma once

#include <iostream>
using std::cout; using std::cin; using std::endl;

#ifndef CURRENCY_SIGN_TYPE
#define CURRENCY_SIGN_TYPE
enum signType { plus, minus };
#endif

class Currency
{
	friend std::ostream& operator<<(std::ostream&, const Currency&);
	friend std::istream& operator>>(std::istream&, Currency&);
	friend Currency operator+(const Currency& lhs, const Currency& rhs);
	friend Currency operator-(const Currency& lhs, const Currency& rhs);
	friend Currency operator*(const Currency& lhs, const Currency& rhs);
	friend Currency operator/(const Currency& lhs, const Currency& rhs);
	friend Currency operator%(const Currency& lhs, const Currency& rhs);

public:
	Currency(signType theSign = plus, unsigned long theDollars = 0, unsigned int theCents = 0);
	~Currency() = default;

	void setValue(signType, unsigned long, unsigned int);
	void setValue(double);
	signType getSign() const { return (amount < 0 ? minus : plus); }
	unsigned long getDollars() const { return (amount < 0 ? (-amount) / 100 : amount / 100); }
	unsigned int getCents() const { return (amount < 0 ? (-amount - getDollars() * 100) : (amount - getDollars() * 100)); }

	Currency& operator+=(const Currency& x) { amount += x.amount; return *this; }
	Currency& operator-=(const Currency& x) { amount -= x.amount; return *this; }
	Currency& operator*=(const Currency& x) { amount *= x.amount; amount = static_cast<double>(amount) / 100; return *this; }
	Currency& operator/=(const Currency& x) { amount = (static_cast<double>(amount) / static_cast<double>(x.amount)*100); return *this; }
	Currency& operator%=(const Currency& x) { amount %= x.amount; return *this; }

	Currency& operator=(const Currency& x);
	Currency& operator=(double x);
	Currency& operator=(int x);

private:
	long amount;
};

int ex1_18();
