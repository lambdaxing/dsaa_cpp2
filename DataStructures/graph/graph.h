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
    virtual void output(ostream&) const = 0;

    // implementation independent methods
    virtual void bfs(int v, int reach[], int label)
    {// Breadth-first search. reach[i] is set to label for
     // all vertices reachable from vertex v.
        arrayQueue<int> q(10);
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

    void dfs(int v, int reach[], int label)
    {// Depth-first search. reach[i] is set to label for all
     // vertices reachable from vertex v
        graph<T>::reach = reach;
        graph<T>::label = label;
        rDfs(v);
    }

    int* findPath(int theSource, int theDestination)
    {// Find a path from theSource to theDestination. Return the
     // path in an array using positions 1 on up. path[0] is
     // path length. Return NULL if there is no path.
       // initialize for recursive path finder
        int n = numberOfVertices();
        path = new int[n + 1];
        path[1] = theSource;      // first vertex is always s
        length = 1;               // current path length + 1
        destination = theDestination;
        reach = new int[n + 1];
        for (int i = 1; i <= n; i++)
            reach[i] = 0;

        // search for path
        if (theSource == theDestination || rFindPath(theSource))
            // a path was found
            path[0] = length - 1;
        else
        {
            delete[] path;
            path = nullptr;
        }

        delete[] reach;
        return path;
    }

    bool connected()
    {// Return true iff graph is connected.
       // make sure this is an undirected graph
        if (directed())
            throw undefinedMethod
            ("graph::connected() not defined for directed graphs");

        int n = numberOfVertices();

        reach = new int[n + 1];  // by default reach[i] = 0

        // mark vertices reachable from vertex 1
        dfs(1, reach, 1);

        // check if all vertices marked
        for (int i = 1; i <= n; i++)
            if (reach[i] == 0)
                return false;
        return true;
    }

    int labelComponents(int c[])
    {// Label the components of an undirected graph. 
     // Return the number of components.
     // Set c[i] to be the component number of vertex i.
       // make sure this is an undirected graph
        if (directed())
            throw undefinedMethod
            ("graph::labelComponents() not defined for directed graphs");

        int n = numberOfVertices();

        // assign all vertices to no component
        for (int i = 1; i <= n; i++)
            c[i] = 0;

        label = 0;  // ID of last component
        // identify components
        for (int i = 1; i <= n; i++)
            if (c[i] == 0)  // vertex i is unreached
            {// vertex i is in a new component
                label++;
                bfs(i, c, label); // mark new component
            }

        return label;
    }
 protected:
     static int* reach;
     static int* path;
     static int label;
     static int length;
     static int destination;
     //static int* bin;   // pointer to first node in bin
     //static binNode* node;

     void rDfs(int v)
     {// Recursive dfs method.
         reach[v] = label;
         vertexIterator<T>* iv = iterator(v);
         int u;
         while ((u = iv->next()) != 0)
             // visit an adjacent vertex of v
             if (reach[u] == 0)
                 rDfs(u);  // u is an unreached vertex
         delete iv;
     }

     bool rFindPath(int s)
     {// Real path finder, performs a depth-first search from s.
      // s should not equal the destination.
      // Return true iff a path to destination is found.
         reach[s] = 1;
         vertexIterator<T>* is = iterator(s);
         int u;
         while ((u = is->next()) != 0)
         {// visit an adjacent vertex of s
             if (reach[u] == 0)   // u is an unreached vertex
             {// move to vertex u
                 path[++length] = u; // add u to path
                 if (u == destination || rFindPath(u))
                     return true;
                 // no path from u to destination
                 length--;    // remove u from path
             }
         }
         delete is;
         return false;
     }
};

#endif // !GRAPH_
