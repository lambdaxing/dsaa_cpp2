// functions to convert fromt type K to nonnegative integer
// derived from similar classes in SGI STL

#ifndef HASH_
#define HASH_

#include <iostream>
#include <string>

template<typename T> class hash;

template<>
class hash<std::string>
{
public:
	std::size_t operator()(const std::string theKey) const
	{// Convert theKey to a nonnegative integer.
		unsigned long hashValue = 0;
		int length = static_cast<int>(theKey.length());
		for (int i = 0; i < length; ++i)
			hashValue = 5 * hashValue + theKey.at(i);

		return static_cast<std::size_t>(hashValue);
	}
};

template<>
class hash<int>
{
public:
	std::size_t operator()(const int theKey) const
	{
		return static_cast<std::size_t>(theKey);
	}
};

template<>
class hash<long>
{
public:
	std::size_t operator()(const long theKey) const
	{
		return static_cast<std::size_t>(theKey);
	}
};

#endif // 
