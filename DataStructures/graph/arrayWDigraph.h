// array adjacency list representation of a weighted digraph

#ifndef ARRAY_WDI_GRAPH_
#define ARRAY_WDI_GRAPH_

#include <iostream>
#include <sstream>
#include "graph.h"
#include "weightedEdge.h"
#include "vertexIterator.h"
#include "myExceptions.h"
#include "graphArray.h"

//**************************************************************************
// struct used for element type in graph chain
template <class T>
struct wEdge
{// vertex and weight pair
    int vertex;
    T weight;
    wEdge(int theVertex = 0, T theWeight = 0)
    {
        vertex = theVertex; weight = theWeight;
    }
    operator int() const { return vertex; }
};

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const wEdge<T>& x)
{
    out << x.vertex << " " << x.weight << " "; return out;
}
//**************************************************************************

// T is data type of edge weight
template <class T>
class arrayWDigraph : public graph<T>
{
protected:
    int n;                         // number of vertices
    int e;                         // number of edges
    graphArray<wEdge<T> >* aList;  // adjacency lists

public:
    arrayWDigraph(int numberOfVertices = 0)
    {// Constructor.
        if (numberOfVertices < 0)
            throw illegalParameterValue
            ("number of vertices must be >= 0");
        n = numberOfVertices;
        e = 0;
        aList = new graphArray<wEdge<T> >[n + 1];
    }

    ~arrayWDigraph() { delete[] aList; }

    int numberOfVertices() const { return n; }

    int numberOfEdges() const { return e; }

    bool directed() const { return true; }

    bool weighted() const { return true; }

    bool existsEdge(int i, int j) const
    {// Return true iff (i,j) is an edge.
        if (i < 1 || j < 1 || i > n || j > n
            || aList[i].indexOf(wEdge<T>(j)) == -1)
            return false;
        else
            return true;
    }

    void insertEdge(edge<T>* theEdge)
    {// Insert an edge.
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
        {
            std::ostringstream s;
            s << "(" << v1 << "," << v2
                << ") is not a permissible edge";
            throw illegalParameterValue(s.str());
        }

        if (aList[v1].indexOf(wEdge<T>(v2)) == -1)
        {// new edge
            aList[v1].insert(0, wEdge<T>(v2, theEdge->weight()));
            e++;
        }
    }

    void insertEdgeNoCheck(edge<T>* theEdge)
    {// Insert an edge. No validation checks performed.
        aList[theEdge->vertex1()].insert(0,
            wEdge<T>(theEdge->vertex2(), theEdge->weight()));
        e++;
    }


    void eraseEdge(int i, int j)
    {
        if (i >= 1 && j >= 1 && i <= n && j <= n)
        {
            wEdge<T>* v = aList[i].eraseElement(j);             // j 这里在 eraseElement内部与 element 进行比较时，element的type: wEdge<T> 会隐式转换为 int
            if (v != nullptr)  // edge (i,j) did exist
                e--;
        }
    }

    void checkVertex(int theVertex) const
    {// Verify that i is a valid vertex.
        if (theVertex < 1 || theVertex > n)
        {
            std::ostringstream s;
            s << "no vertex " << theVertex;
            throw illegalParameterValue(s.str());
        }
    }

    int degree(int theVertex) const
    {
        throw undefinedMethod("degree() undefined");
    }

    int outDegree(int theVertex) const
    {// Return out-degree of vertex theVertex.
        checkVertex(theVertex);
        return aList[theVertex].size();
    }

    int inDegree(int theVertex) const
    {
        checkVertex(theVertex);

        // count in-edges at vertex theVertex
        int sum = 0;
        for (int j = 1; j <= n; j++)
            if (aList[j].indexOf(wEdge<T>(theVertex)) != -1)
                sum++;

        return sum;
    }

    class myIterator : public vertexIterator<int>
    {
    public:
        myIterator(graphArray<wEdge<T> >& currentVertex)
        {
            c = currentVertex.begin();
            e = currentVertex.end();
        }

        ~myIterator() {}

        int next()
        {// Return next vertex if any. Return 0 if no next vertex.
           // find next adjacent vertex
            if (c == e)
                return 0;
            int nextVertex = c->vertex;
            ++c;
            return nextVertex;
        }

        int next(T& theWeight)
        {// Return next vertex if any. Return 0 if no next vertex.
         // Set theWeight = edge weight.
           // find next adjacent vertex
            if (c == e)
                return 0;
            int nextVertex = c->vertex;
            theWeight = c->weight;
            ++c;
            return nextVertex;
        }

    protected:
        typename graphArray<wEdge<T>>::iterator c, e;      // typename is used to tell the compiler that iterator is a type, otherwise compiler will prompt that the dependent name is not a type.
    };

    myIterator* iterator(int theVertex)
    {// Return iterator for vertex theVertex.
        checkVertex(theVertex);
        return new myIterator(aList[theVertex]);
    }


    void output(std::ostream& out) const
    {// Output the adjacency matrix.
        for (int i = 1; i <= n; i++)
            out << aList[i] << std::endl;
    }

    void input(std::istream& in)
    {
        in >> n >> e;
        delete[] aList;
        aList = new graphArray<wEdge<T> >[n + 1];

        for (int i = 0; i < e; i++)
        {
            int v1, v2;
            T w;
            in >> v1 >> v2 >> w;

            if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
            {
                std::ostringstream s;
                s << "(" << v1 << "," << v2
                    << ") is not a permissible edge";
                throw illegalParameterValue(s.str());
            }

            if (aList[v1].indexOf(wEdge<T>(v2)) == -1)
            {// new edge
                aList[v1].insert(0, wEdge<T>(v2, w));
            }
        }
    }

};

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const arrayWDigraph<T>& x)
{
    x.output(out); return out;
}
// overload >>
template<typename T>
std::istream& operator>>(std::istream& in, arrayWDigraph<T>& x)
{
    x.input(in); return in;
}

#endif