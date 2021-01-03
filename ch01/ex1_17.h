#pragma once

#include <iostream>
using std::cout; using std::cin; using std::endl;
#include <functional>
using std::function; using std::modulus; using std::multiplies; using std::divides;
// using std::minus; // Name Collision

#ifndef CURRENCY_SIGN_TYPE
#define CURRENCY_SIGN_TYPE
enum class signType { plus, minus };
#endif

class Currency1_17
{
public:
	Currency1_17(signType theSign = signType::plus, unsigned long theDollars = 0, unsigned int theCents = 0);
	~Currency1_17() = default;

	void setValue(signType, unsigned long, unsigned int);
	void setValue(double);
	signType getSign() const { return (amount < 0 ? signType::minus : signType::plus); }
	unsigned long getDollars() const { return (amount < 0 ? (-amount) / 100 : amount / 100); }
	unsigned int getCents() const { return (amount < 0 ? (-amount - getDollars() * 100) : (amount - getDollars() * 100)); }
	Currency1_17 add(const Currency1_17&) const;
	Currency1_17& increment(const Currency1_17& x) { amount += x.amount; return *this; }
	void output() const;
	
	void input();								// 1)
	Currency1_17 subtract(const Currency1_17&) const;	// 2)
	Currency1_17 precent(double) const;				// 3)
	Currency1_17 multiply(double) const;			// 4)
	Currency1_17 divide(double) const;				// 5)

private:
	long amount;
};

int ex1_17();
