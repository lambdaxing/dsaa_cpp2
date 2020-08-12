// abstract class graph
// abstract data type specification for graph data structure
// includes methods that are representation independent

#ifndef GRAPH_
#define GRAPH_

#include <queue>
#include "edge.h"
#include "vertexIterator.h"

template<typename T>
class graph
{
public:
    virtual ~graph() {}
    virtual int numberOfVertices() const = 0;
    virtual int numberOfEdges() const = 0;
    virtual bool existsEdge(int, int) const = 0;
    virtual void insertEdge(edge<T>*) = 0;
    virtual void eraseEdge(int, int) = 0;
    virtual int degree(int) const = 0;
    virtual int inDegree(int) const = 0;
    virtual int outDegree(int) const = 0;
    virtual bool directed() const = 0;
    virtual bool weighted() const = 0;
    virtual vertexIterator<T>* iterator(int) = 0;
    virtual void output(std::ostream&) const = 0;

    // implementation independent methods
    virtual void bfs(int v, int reach[], int label)
    {// Breadth-first search. reach[i] is set to label for
     // all vertices reachable from vertex v.
        std::queue<int> q;
        reach[v] = label;
        q.push(v);
        while (!q.empty())
        {
            // remove a labeled vertex from the queue
            int w = q.front();
            q.pop();

            // mark all unreached vertices adjacent from w
            vertexIterator<T>* iw = iterator(w);
            int u;
            while ((u = iw->next()) != 0)
                // visit an adjacent vertex of w
                if (reach[u] == 0)
                {// u is an unreached vertex
                    q.push(u);
                    reach[u] = label; // mark reached
                }
            delete iw;
        }
    }
};
#endif // !GRAPH_
