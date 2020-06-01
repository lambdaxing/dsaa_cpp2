
#ifndef STUDENT_RECORD
#define STUDENT_RECORD

#include <string>
#include <iostream>
#include "chain.h"

struct studentRecord
{
	int score;
	std::string* name;

	bool operator!=(const studentRecord& x) const { return score != x.score; }
	operator int() const { return score; }
};

std::ostream& operator<<(std::ostream& out, const studentRecord& x)
{
	out << x.score << ' ' << *x.name;
	return out;
}

void binSort(chain<studentRecord>& theChain, int range)
{
	chain<studentRecord>* bin;
	bin = new chain<studentRecord>[range + 1];

	int numberOfElements = theChain.size();
	for (int i = 1; i <= numberOfElements; ++i)
	{
		studentRecord x = theChain.get(0);
		theChain.erase(0);
		bin[x.score].insert(0, x);
	}

	for (int j = range; j >= 0; --j)
	{
		while (!bin[j].empty())
		{
			studentRecord x = bin[j].get(0);
			bin[j].erase(0);
			theChain.insert(0, x);
		}
	}
}
#endif
