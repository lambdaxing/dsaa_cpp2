// array adjacency list representation of a graph

#ifndef ARRAY_GRAPH_
#define ARRAY_GRAPH_

#include <iostream>
#include <sstream>
#include "arrayDigraph.h"
#include "unweightedEdge.h"

class arrayGraph : public arrayDigraph
{
public:
    arrayGraph(int numberOfVertices = 0)
        : arrayDigraph(numberOfVertices) {}

    bool directed() const { return false; }

    void insertEdge(edge<bool>* theEdge)
    {// Insert an edge.
        int oldE = this->e;
        arrayDigraph::insertEdge(theEdge);
        if (this->e > oldE)
        {// new edge
            arrayDigraph::insertEdgeNoCheck(new unweightedEdge
            (theEdge->vertex2(), theEdge->vertex1()));
            this->e--;  // compenstate for extra increment
        }
    }

    void insertEdgeNoCheck(edge<bool>* theEdge)
    {// Insert an edge. No validation checks performed.
        arrayDigraph::insertEdgeNoCheck(theEdge);
        arrayDigraph::insertEdgeNoCheck(new unweightedEdge
        (theEdge->vertex2(), theEdge->vertex1()));
        this->e--;
    }

    void eraseEdge(int i, int j)
    {
        int oldE = this->e;
        arrayDigraph::eraseEdge(i, j);
        if (oldE > this->e) // edge exists
        {
            arrayDigraph::eraseEdge(j, i);
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
        this->aList = new graphArray<int>[this->n + 1];

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
std::ostream& operator<<(std::ostream& out, const arrayGraph& x)
{
    x.output(out); return out;
}
// overload >>
std::istream& operator>>(std::istream& in, arrayGraph& x)
{
    x.input(in); return in;
}
#endif
