// abstract class for graph edges

#ifndef EDGE_
#define EDGE_

template <typename T>
class edge
{
public:
	virtual ~edge() {}
	virtual int vertex1() const = 0;
	virtual int vertex2() const = 0;
	virtual T weight() const = 0;
};

#endif // !EDGE_
