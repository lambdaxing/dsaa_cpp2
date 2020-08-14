// array adjacency list representation of a digraph

#ifndef ARRAY_DIGRAPH_
#define ARRAY_DIGRAPH_

#include <iostream>
#include <sstream>
#include "graph.h"
#include "graphArray.h"
#include "unweightedEdge.h"
#include "vertexIterator.h"
#include "myExceptions.h"

class arrayDigraph : public graph<bool>
{
protected:
    int n;                      // number of vertices
    int e;                      // number of edges
    graphArray<int>* aList;     // adjacency lists

public:
    arrayDigraph(int numberOfVertices = 0)
    {// Constructor.
        if (numberOfVertices < 0)
            throw illegalParameterValue
            ("number of vertices must be >= 0");
        n = numberOfVertices;
        e = 0;
        aList = new graphArray<int>[n + 1];
    }

    ~arrayDigraph() { delete[] aList; }

    int numberOfVertices() const { return n; }

    int numberOfEdges() const { return e; }

    bool directed() const { return true; }

    bool weighted() const { return false; }

    bool existsEdge(int i, int j) const
    {// Return true iff (i,j) is an edge.
        if (i < 1 || j < 1 || i > n || j > n
            || aList[i].indexOf(j) == -1)
            return false;
        else
            return true;
    }

    void insertEdge(edge<bool>* theEdge)
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

        if (aList[v1].indexOf(v2) == -1)
        {// new edge
            aList[v1].insert(0, v2);
            e++;
        }
    }

    void insertEdgeNoCheck(edge<bool>* theEdge)
    {// Insert an edge. No validation checks performed.
        aList[theEdge->vertex1()].insert(0, theEdge->vertex2());
        e++;
    }

    void eraseEdge(int i, int j)
    {
        if (i >= 1 && j >= 1 && i <= n && j <= n)
        {
            int* v = aList[i].eraseElement(j);
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
            if (aList[j].indexOf(theVertex) != -1)
                sum++;

        return sum;
    }

    class myIterator : public vertexIterator<bool>
    {
    public:
        myIterator(graphArray<int>& currentVertex)
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
            int nextVertex = *c;
            ++c;
            return nextVertex;
        }

        int next(bool& theWeight)
        {// Return next vertex if any. Return 0 if no next vertex.
         // Set theWeight = edge weight.
           // find next adjacent vertex
            if (c == e)
                return 0;
            int nextVertex = *c;
            theWeight = true;
            ++c;
            return nextVertex;
        }

    protected:
        typename graphArray<int>::iterator c, e;      // typename is used to tell the compiler that iterator is a type, otherwise compiler will prompt that the dependent name is not a type.
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
        aList = new graphArray<int>[n + 1];

        for (int i = 0; i < e; i++)
        {
            int v1, v2;
            in >> v1 >> v2;

            if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
            {
                std::ostringstream s;
                s << "(" << v1 << "," << v2
                    << ") is not a permissible edge";
                throw illegalParameterValue(s.str());
            }

            if (aList[v1].indexOf(v2) == -1)
            {// new edge
                aList[v1].insert(0, v2);
            }
        }
    }

    void bfs(int v, int reach[], int label)
    {
        std::queue<int> q;
        reach[v] = label;
        q.push(v);

        while (!q.empty())
        {
            int w = q.front();
            q.pop();

            for (auto u = aList[w].begin(); u != aList[w].end(); ++u)

                if (reach[*u] == 0)
                {
                    q.push(*u);
                    reach[*u] = label;
                }

        }
    }

    void dfs(int v, int reach[], int label)
    {// Depth-first search. reach[i] is set to label for all
     // vertices reachable from vertex v
        graph<bool>::reach = reach;
        graph<bool>::label = label;
        rDfs(v);
    }

protected:
    void rDfs(int v)
    {
        graph<bool>::reach[v] = graph<bool>::label;
        for (auto u = aList[v].begin(); u != aList[v].end(); ++u)
            if (graph<bool>::reach[*u] == 0)
                rDfs(*u);
    }

};

// overload <<
std::ostream& operator<<(std::ostream& out, const arrayDigraph& x)
{
    x.output(out); return out;
}
// overload >>
std::istream& operator>>(std::istream& in, arrayDigraph& x)
{
    x.input(in); return in;
}
#endif