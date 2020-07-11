// class used for first-fit packing

#ifndef BIN_TYPE_
#define BIN_TYPE_

struct binType
{
	int unusedCapacity;
	bool operator <=(const binType& right) const
	{
		return (unusedCapacity >= right.unusedCapacity) ? true : false;
	}
};
#endif // !BIN_TYPE_
