#pragma once
#include <iostream>
#include <string>

template<typename T,size_t N>
bool find(const T (&t)[N],size_t b,size_t e,const T& v)
{
	if (b >= e || b >= N || e > N) return false;
	if (t[b] == v) return true;
	else return find(t, ++b, e, v);
}

int ex1_24()
{
	std::string s[3]{ "hello",",","world!" };
	std::cout << find(s, 1, 3, std::string(",")) << std::endl;
	std::cout << find(s, 0, 3, std::string("xiaoxing30")) << std::endl;
	return 0;
}