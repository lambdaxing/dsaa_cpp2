// linked adjacency list representation of a weighted graph

#ifndef linkedWGraph_
#define linkedWGraph_

#include <iostream>
#include <sstream>
#include "linkedWDigraph.h"
#include "weightedEdge.h"

template <class T>
class linkedWGraph : public linkedWDigraph<T>
{
public:
    linkedWGraph(int numberOfVertices = 0)
        : linkedWDigraph<T>(numberOfVertices) {}

    bool directed() const { return false; }

    void insertEdge(edge<T>* theEdge)
    {// Insert an edge.
        int oldE = this->e;
        linkedWDigraph<T>::insertEdge(theEdge);     // add (i,j)
        if (this->e > oldE)
        {// new edge
            linkedWDigraph<T>::insertEdgeNoCheck(new weightedEdge<T>
                (theEdge->vertex2(),
                    theEdge->vertex1(),
                    theEdge->weight()));            // add (j,i)
            this->e--;  // compenstate for extra increment
        }
    }

    void insertEdgeNoCheck(edge<T>* theEdge)
    {// Insert an edge. No validation checks performed.
        linkedWDigraph<T>::insertEdgeNoCheck(theEdge);  // add (i,j)
        linkedWDigraph<T>::insertEdgeNoCheck(new weightedEdge<T>
            (theEdge->vertex2(),
                theEdge->vertex1(),
                theEdge->weight()));                    // add (j,i)
        this->e--;
    }

    void eraseEdge(int i, int j)
    {
        int oldE = this->e;
        linkedWDigraph<T>::eraseEdge(i, j);
        if (oldE > this->e) // edge exists
        {
            linkedWDigraph<T>::eraseEdge(j, i);
            this->e++;
        }
    }

    int degree(int theVertex) const
    {
        this->checkVertex(theVertex);
        return this->aList[theVertex].size();
    }

    int outDegree(int theVertex) const { return degree(theVertex); }

    int inDegree(int theVertex) const { return degree(theVertex); }

    void input(std::istream& in)
    {
        in >> this->n >> this->e;
        delete[] this->aList;
        this->aList = new graphChain<wEdge<T> >[this->n + 1];

        for (int i = 0; i < this->e; i++)
        {
            int v1, v2;
            T w;
            in >> v1 >> v2 >> w;

            if (v1 < 1 || v2 < 1 || v1 > this->n || v2 > this->n || v1 == v2)
            {
                std::ostringstream s;
                s << "(" << v1 << "," << v2
                    << ") is not a permissible edge";
                throw illegalParameterValue(s.str());
            }

            if (this->aList[v1].indexOf(wEdge<T>(v2)) == -1)
            {// new edge
                this->aList[v1].insert(0, wEdge<T>(v2, w));
            }
            if (this->aList[v2].indexOf(wEdge<T>(v1)) == -1)
            {// new edge
                this->aList[v2].insert(0, wEdge<T>(v1, w));
            }
        }
    }
};

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const linkedWGraph<T>& x)
{
    x.output(out); return out;
}
// overload >>
template<typename T>
std::istream& operator>>(std::istream& in, linkedWGraph<T>& x)
{
    x.input(in); return in;
}
#endif
