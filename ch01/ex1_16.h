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

class Currency1_16
{
public:
	Currency1_16(signType theSign = signType::plus, unsigned long theDollars = 0, unsigned int theCents = 0)
	{
		setValue(theSign, theDollars, theCents);
	}
	~Currency1_16() = default;

	void setValue(signType, unsigned long, unsigned int);
	void setValue(double);
	signType getSign() const { return sign; }
	unsigned long getDollars() const { return dollars; }
	unsigned int getCents() const { return cents; }

	Currency1_16 add(const Currency1_16&) const;

	long getLong() const
	{
		long a1 = dollars * 100 + cents;
		if (sign == signType::minus) a1 = -a1;
		return a1;
	}

	double getDouble() const 
	{ 
		double theAmount = dollars + static_cast<double>(cents) / 100; 
		return (sign == signType::plus ? theAmount : -theAmount);
	}
	void input();								// 1)
	Currency1_16 subtract(const Currency1_16&) const;	// 2)
	Currency1_16 precent(double) const;				// 3)
	Currency1_16 multiply(double) const;			// 4)
	Currency1_16 divide(double) const;				// 5)

	Currency1_16& increment(const Currency1_16&);

	void output() const;

private:
	signType sign;				// 对象的符号
	unsigned long dollars;		// 美元的数量
	unsigned int cents;			// 美分的数量
};

int ex1_16();
