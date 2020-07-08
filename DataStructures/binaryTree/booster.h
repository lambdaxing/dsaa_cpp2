#ifndef BOOSTER_
#define BOOSTER_

#include <iostream>

struct booster
{
	int degradeToLeaf;		// degradation to leaf
	int degradeFromParent;	// degradation from parent
	bool boosterHere;		// true if booster here

	void output(std::ostream& out) const
	{
		out << boosterHere << ' ' << degradeToLeaf << ' ' << degradeFromParent << ' ';
	}
};

// overload <<
std::ostream& operator<<(std::ostream& out, booster x)
{
	x.output(out);
	return out;
}
#endif // !BOOSTER_
