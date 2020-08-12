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
        int oldE = e;
        linkedWDigraph<T>::insertEdge(theEdge);     // add (i,j)
        if (e > oldE)
        {// new edge
            linkedWDigraph<T>::insertEdgeNoCheck(new weightedEdge<T>
                (theEdge->vertex2(),
                    theEdge->vertex1(),
                    theEdge->weight()));            // add (j,i)
            e--;  // compenstate for extra increment
        }
    }

    void insertEdgeNoCheck(edge<T>* theEdge)
    {// Insert an edge. No validation checks performed.
        linkedWDigraph<T>::insertEdgeNoCheck(theEdge);  // add (i,j)
        linkedWDigraph<T>::insertEdgeNoCheck(new weightedEdge<T>
            (theEdge->vertex2(),
                theEdge->vertex1(),
                theEdge->weight()));                    // add (j,i)
        e--;
    }

    void eraseEdge(int i, int j)
    {
        int oldE = e;
        linkedWDigraph<T>::eraseEdge(i, j);
        if (oldE > e) // edge exists
        {
            linkedWDigraph<T>::eraseEdge(j, i);
            e++;
        }
    }

    int degree(int theVertex) const
    {
        checkVertex(theVertex);
        return aList[theVertex].size();
    }

    int outDegree(int theVertex) const { return degree(theVertex); }

    int inDegree(int theVertex) const { return degree(theVertex); }
};
#endif
