// linked adjacency list representation of a graph

#ifndef linkedGraph_
#define linkedGraph_

#include <iostream>
#include <sstream>
#include "linkedDigraph.h"
#include "unweightedEdge.h"

class linkedGraph : public linkedDigraph
{
public:
    linkedGraph(int numberOfVertices = 0)
        : linkedDigraph(numberOfVertices) {}

    bool directed() const { return false; }

    void insertEdge(edge<bool>* theEdge)
    {// Insert an edge.
        int oldE = this->e;
        linkedDigraph::insertEdge(theEdge);
        if (this->e > oldE)
        {// new edge
            linkedDigraph::insertEdgeNoCheck(new unweightedEdge
            (theEdge->vertex2(), theEdge->vertex1()));
            this->e--;  // compenstate for extra increment
        }
    }

    void insertEdgeNoCheck(edge<bool>* theEdge)
    {// Insert an edge. No validation checks performed.
        linkedDigraph::insertEdgeNoCheck(theEdge);
        linkedDigraph::insertEdgeNoCheck(new unweightedEdge
        (theEdge->vertex2(), theEdge->vertex1()));
        this->e--;
    }

    void eraseEdge(int i, int j)
    {
        int oldE = this->e;
        linkedDigraph::eraseEdge(i, j);
        if (oldE > this->e) // edge exists
        {
            linkedDigraph::eraseEdge(j, i);
            this->e++;
        }
    }

    int degree(int theVertex) const
    {
        checkVertex(theVertex);
        return this->aList[theVertex].size();
    }

    int outDegree(int theVertex) const { return degree(theVertex); }

    int inDegree(int theVertex) const { return degree(theVertex); }

    void input(std::istream& in)
    {
        in >> this->n >> this->e;
        delete[] this->aList;
        this->aList = new graphChain<int>[this->n + 1];

        for (int i = 0; i < this->e; i++)
        {
            int v1, v2;
            in >> v1 >> v2;

            if (v1 < 1 || v2 < 1 || v1 > this->n || v2 > this->n || v1 == v2)
            {
                std::ostringstream s;
                s << "(" << v1 << "," << v2
                    << ") is not a permissible edge";
                throw illegalParameterValue(s.str());
            }

            if (this->aList[v1].indexOf(v2) == -1)
            {// new edge
                this->aList[v1].insert(0, v2);
            }
            if (this->aList[v2].indexOf(v1) == -1)
            {
                this->aList[v2].insert(0, v1);
            }
        }
    }
};

// overload <<
std::ostream& operator<<(std::ostream& out, const linkedGraph& x)
{
    x.output(out); return out;
}
// overload >>
std::istream& operator>>(std::istream& in, linkedGraph& x)
{
    x.input(in); return in;
}
#endif
