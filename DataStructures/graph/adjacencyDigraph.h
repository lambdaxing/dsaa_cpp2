// adjacency matrix representation of a directed graph

#ifndef adjacencyDigraph_
#define adjacencyDigraph_

#include <iostream>
#include <sstream>
#include <iterator>
#include "adjacencyWDigraph.h"
#include "unweightedEdge.h"

class adjacencyDigraph : public adjacencyWDigraph<bool>
{
public:
    adjacencyDigraph(int numberOfVertices = 0)
        : adjacencyWDigraph<bool>(numberOfVertices, false) {}

    void insertEdge(edge<bool>* theEdge)
    {// Insert an edge.
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v2 < 1 || v1 > this->n || v2 > this->n || v1 == v2)
        {
            std::ostringstream s;
            s << "(" << v1 << "," << v2
                << ") is not a permissible edge";
            throw illegalParameterValue(s.str());
        }

        if (!this->a[v1][v2])  // new edge
            this->e++;
        this->a[v1][v2] = true;
    }

    bool weighted() const { return false; }

    void input(std::istream& in)
    {
        // destructor
        delete2dArray(this->a, this->n + 1);

        in >> this->n >> this->e;
        make2dArray(this->a, this->n + 1, this->n + 1);
        for (int i = 1; i <= this->n; i++)
            // initialize adjacency matrix
            std::fill(this->a[i], this->a[i] + this->n + 1, this->noEdge);

        // input e edges
        for (int i = 0; i < this->e; ++i)
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

            this->a[v1][v2] = true;
        }
    }
};

// overload <<
std::ostream& operator<<(std::ostream& out, const adjacencyDigraph& x)
{
    x.output(out); return out;
}
// overload >>
std::istream& operator>>(std::istream& in, adjacencyDigraph& x)
{
    x.input(in); return in;
}
#endif
