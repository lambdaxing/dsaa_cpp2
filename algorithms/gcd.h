// some algorithms about Greatest Common Divisor,GCD

#ifndef ALGORITHMS_GCD_
#define ALGORITHMS_GCD_

// Eurclid's Algorithm
//
//				{ x				,	y = 0
//	gcd(x,y) =	{
//				{ gcd(y,x mod y),	y > 0
//
unsigned eurclidGCD(unsigned x, unsigned y)
{
	if (y == 0)
		return x;
	else return eurclidGCD(y, x % y);
}

#endif // !ALGORITHMS_GCD_
