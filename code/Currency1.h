#pragma once

#include <iostream>
using std::cout; using std::endl;
#include "illegalParameterValue.h"

enum signType { plus, minus };

class Currency
{
public:
	Currency(signType theSign = plus, unsigned long theDollars = 0, unsigned int theCents = 0) :
		sign(theSign), dollars(theDollars), cents(theCents) {}
	~Currency() = default;

	void setValue(signType, unsigned long, unsigned int);
	void setValue(double);
	signType getSign() const { return sign; }
	unsigned long getDollars() const { return dollars; }
	unsigned int getCents() const { return cents; }
	Currency add(const Currency&) const;
	Currency& increment(const Currency&);
	void output() const;
private:
	signType sign;				// 对象的符号
	unsigned long dollars;		// 美元的数量
	unsigned int cents;			// 美分的数量
};

