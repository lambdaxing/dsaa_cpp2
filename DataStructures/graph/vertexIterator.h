// abstract class for graph vertex iterator

#ifndef VERTEX_ITERATOR_
#define VERTEX_ITERATOR_

template<typename T>
class vertexIterator
{
public:
	virtual ~vertexIterator() {}
	virtual int next() = 0;
	virtual int next(T&) = 0;
};
#endif // !VERTEX_ITERATOR_
