#pragma once
#include <math.h>
#include <iostream>
using namespace std;

// Compute and output the roots of the quadratic equation
void outputRoots(const double& a, const double& b, const double& c)
{
	double d = b * b - 4 * a * c;		// b^2 - 4ac
	if (d > 0) {		// two real roots
		double sqrtd = sqrt(d);
		cout << "There are two real roots "
			<< (-b + sqrtd) / (2 * a) << " and "
			<< (-b - sqrtd) / (2 * a)
			<< endl;
	}
	else if (d == 0)	// two same roots
		cout << "There is only one distinct root "
		<< -b / (2 * a)
		<< endl;
	else				// complex conjugate root
		cout << "The roots are complex"
		<< endl
		<< "The real part is "
		<< -b / (2 * a) << endl
		<< "The imaginary part is "
		<< sqrt(-d) / (2 * a) << endl;
}