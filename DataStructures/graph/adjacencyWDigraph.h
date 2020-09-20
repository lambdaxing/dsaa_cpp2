// adjacency matrix representation of a weighted directed graph

#ifndef ADJACENCY_WDI_GRAPH_
#define ADJACENCY_WDI_GRAPH_

#include <iostream>
#include <sstream>
#include <iterator>
#include "make2dArrayNoCatch.h"
#include "delete2dArray.h"
#include "myExceptions.h"
#include "weightedEdge.h"
#include "graph.h"

template<typename T>
class adjacencyWDigraph :public graph<T>
{
protected:
    int n;           // number of vertices
    int e;           // number of edges
    T** a;           // adjacency array
    T noEdge;        // denotes absent edge

public:
    adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0)
    {// Constructor.
       // validate number of vertices
        if (numberOfVertices < 0)
            throw illegalParameterValue("number of vertices must be >= 0");
        n = numberOfVertices;
        e = 0;
        noEdge = theNoEdge;
        make2dArray(a, n + 1, n + 1);
        for (int i = 1; i <= n; i++)
            // initialize adjacency matrix
            std::fill(a[i], a[i] + n + 1, noEdge);
    }

    // ex33
    adjacencyWDigraph(const adjacencyWDigraph& x)
    {
        n = x.n;
        e = x.e;
        noEdge = x.noEdge;
        make2dArray(a, n + 1, n + 1);
        for (int i; i <= n; i++)
            std::copy(x.a[i], x.a[i] + x.n + 1, a[i]);
    }

    ~adjacencyWDigraph() { delete2dArray(a, n + 1); }

    int numberOfVertices() const { return n; }

    int numberOfEdges() const { return e; }

    bool directed() const { return true; }

    bool weighted() const { return true; }

    bool existsEdge(int i, int j) const
    {// Return true iff (i,j) is an edge of the graph. 
        if (i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge)
            return false;
        else
            return true;
    }

    void insertEdge(edge<T>* theEdge)
    {// Insert edge theEdge into the digraph; if the edge is already
     // there, update its weight to theEdge.weight().
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2)
        {
            std::ostringstream s;
            s << "(" << v1 << "," << v2
                << ") is not a permissible edge";
            throw illegalParameterValue(s.str());
        }

        if (a[v1][v2] == noEdge)  // new edge
            e++;
        a[v1][v2] = theEdge->weight();
    }

    void eraseEdge(int i, int j)
    {// Delete the edge (i,j).
        if (i >= 1 && j >= 1 && i <= n && j <= n && a[i][j] != noEdge)
        {
            a[i][j] = noEdge;
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

        // count out edges from vertex theVertex
        int sum = 0;
        for (int j = 1; j <= n; j++)
            if (a[theVertex][j] != noEdge)
                sum++;

        return sum;
    }

    int inDegree(int theVertex) const
    {// Return in-degree of vertex theVertex.
        checkVertex(theVertex);

        // count in edges at vertex theVertex
        int sum = 0;
        for (int j = 1; j <= n; j++)
            if (a[j][theVertex] != noEdge)
                sum++;

        return sum;
    }

    class myIterator : public vertexIterator<T>
    {
    public:
        myIterator(T* theRow, T theNoEdge, int numberOfVertices)
        {
            row = theRow;
            noEdge = theNoEdge;
            n = numberOfVertices;
            currentVertex = 1;
        }

        ~myIterator() {}

        int next()
        {// Return next vertex if any. Return 0 if no next vertex.
           // find next adjacent vertex
            for (int j = currentVertex; j <= n; j++)
                if (row[j] != noEdge)
                {
                    currentVertex = j + 1;
                    return j;
                }
            // no next adjacent vertex
            currentVertex = n + 1;
            return 0;
        }

        int next(T& theWeight)
        {// Return next vertex if any. Return 0 if no next vertex.
         // Set theWeight = edge weight.
           // find next adjacent vertex
            for (int j = currentVertex; j <= n; j++)
                if (row[j] != noEdge)
                {
                    currentVertex = j + 1;
                    theWeight = row[j];
                    return j;
                }
            // no next adjacent vertex
            currentVertex = n + 1;
            return 0;
        }

    protected:
        T* row;           // row of adjacency matrix
        T noEdge;         // theRow[i] == noEdge iff no edge to i
        int n;            // number of vertices
        int currentVertex;
    };

    myIterator* iterator(int theVertex)
    {// Return iterator for vertex theVertex.
        checkVertex(theVertex);
        return new myIterator(a[theVertex], noEdge, n);
    }

    void output(std::ostream& out) const
    {// Output the adjacency matrix.
        for (int i = 1; i <= n; i++)
        {
            std::copy(a[i] + 1, a[i] + n + 1, std::ostream_iterator<T>(out, "  "));
            out << std::endl;
        }
    }

    void input(std::istream& in)
    {
        // destructor
        delete2dArray(a, n + 1);

        in >> n >> e;
        make2dArray(a, n + 1, n + 1);
        for (int i = 1; i <= n; i++)
            // initialize adjacency matrix
            std::fill(a[i], a[i] + n + 1, noEdge);

        // input e edges
        for (int i = 0; i < e; ++i)
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

            a[v1][v2] = w;
        }
    }

    void bfs(int v, int reach[], int label)
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
            for (int u = 1; u <= n; u++)
                // visit an adjacent vertex of w
                if (a[w][u] != noEdge && reach[u] == 0)
                {// u is an unreached vertex
                    q.push(u);
                    reach[u] = label; // mark reached
                }
        }
    }

    void dfs(int v, int reach[], int label)
    {// Depth-first search. reach[i] is set to label for all
     // vertices reachable from vertex v
        graph<T>::reach = reach;
        graph<T>::label = label;
        rDfs(v);
    }

    void shortestPaths(int sourceVertex, T* distanceFromSource, int* predecessor)
    {// Find shortest paths from sourceVertex.
     // Return shortest distances in distanceFromSource.
     // Return predecessor information in predecessor.
        if (sourceVertex < 1 || sourceVertex > n)
            throw illegalParameterValue("Invalid source vertex");

        if (!weighted())
            throw undefinedMethod("adjacencyWDigraph::shortestPaths() not defined for unweighted graphs");

        graphChain<int> newReachableWertices;

        // initialize
        for (int i = 1; i <= n; i++)
        {
            distanceFromSource[i] = a[sourceVertex][i];
            if (distanceFromSource[i] == noEdge)
                predecessor[i] = -1;
            else
            {
                predecessor[i] = sourceVertex;
                newReachableVertices.insert(0, i);
            }
        }
        distanceFromSource[sourceVertex] = 0;
        predecessor[sourceVertex] = 0;      // source vertex has no predecessor

        // update distanceFromSource and predecessor
        while(!newReachableVertices.empty())
        {// more paths exist
            // find unreached vertex v with least distanceFromSource
            auto iNewReachableVertices = newReachableVertices.begin();
            auto theEnd = newReachableVertices.end();
            int v = *iNewReachableVertices;
            iNewReachableVertices++;
            while (iNewReachableVertices != theEnd)
            {
                int w = *iNewReachableVertices;
                iNewReachableVertices++;
                if (distanceFromSource[w] < distanceFromSource[v])
                    v = w;
            }

            // next shortest path is to vertex v, delete v from newReachableVertices and update distanceFromSource
            newReachableVertices.eraseElement(v);
            for (int j = 1; j <= n; j++)
            {
                if (a[v][j] != noEdge && (predecessor[j] == -1 || distanceFromSource[j] > distanceFromSource[v] + a[v][j]))
                {
                    // distanceFromSource[j] decreases
                    distanceFromSource[j] = distanceFromSource[v] + a[v][j];
                    // add j to newReachableVertices
                    if (predecessor[j] == -1)
                        // not reached before
                        newReachableVertices.insert(0, j);
                    predecessor[j] = v;
                }
            }
        }
    }

    void allPairs(T** c, int** kay)
    {// Dynamic programming all pairs shortest paths algorithm.
     // Compute c[i][j] and kay[i][j] for all i and j.
        if (!weighted())
            throw undefinedMethod("adjacencyWDigraph::allPairs() not defined for unweighted graphs");

        // initialize c[i][j] = c(i,j,0)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                c[i][j] = 0;
                kay[i][j] = 0;
            }
        for (int i = 1; i <= n; i++)
            c[i][i] = 0;

        // compute c[i][j] = c(i,j,k)
        for(int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++) 
                for (int j = 1; j <= n; j++)
                    if(c[i][k] != noEdge && c[k][j] != noEdge && (c[i][j] == noEdge || c[i][j] > c[i][k]+c[k][j]))
                    {// smaller value for c[i][j] found.
                        c[i][j] = c[i][k] + c[k][j];
                        kay[i][j] = k;
                    }

    }

    void outputPath(T** c, int** kay, T noEdge, int i, int j)
    {// output shortest path from i to j
        if (c[i][j] == noEdge)
            std::cout << "There is no path from " << i << " to " << j << std::endl;
        else
        {
            std::cout << "The path is " << i << " ";
            outputPath(kay, i, j);
            std::cout << std::endl;
        }
    }

    void outputPath(int **kay,int i,int j)
    {// really code to output paht
        if (i == j)
            return;
        if (kay[i][j] == 0)      // There is no middle vertex in the path
            cout << j << " ";
        else
        {// kay[i][j] is a middle vertex in the path
            outputPath(kay, i, kay[i][j]);
            outputPath(kay, kay[i][j], j);
        }
    }

    T btSalesperson(int* bestTour)
    {// Traveling salesperson by backtracking.
     // bestTour[1:n] is set to best tour.
     // Return cost of best tour.
        if (!weighted())
            throw undefinedMethod("adjacencyWDigraph::btSalesperson() not defined for unweighted graphs");

        // set partialTour to identity permutation
        partialTour = new int[n + 1];
        for (int i = 1; i <= n; i++)
            partialTour[i] = 1;

        costOfBestTourSoFar = noEdge;
        bestTourSoFar = bestTour;
        costOfPartialTour = 0;

        // search permutations of partialTour[2:n]
        rTSP(2);

        return costOfBestTourSoFar;
    }

protected:
    void rTSP(int currentLevel)
    {// Recursive backtracking code for traveling salesperson.
     // Search the permutation tree for best tour. Start at a node at currentLevel.
        if(currentLevel == n)
        {// at parent of a leaf
            // complete tour by adding last two edges
            if(a[partialTour[n-1]][partialTour[n]] != noEdge && a[partialTour[n]][1] != noEdge && 
                (costOfBestTourSoFar == noEdge || 
                    costOfPartialTour + a[partialTour[n-1]][partialTour[n]] + a[partialTour[n]][1] < costOfBestTourSoFar))
            {// better tour found
                std::copy(partialTour + 1, partialTour + n + 1, bestTourSoFar + 1);
                costOfBestTourSoFar = costOfPartialTour + a[partialTour[n - 1]][partialTour[n]] + a[partialTour[n]][1];
            }
        }
        else
        {// try out subtrees
            for(int j = currentLevel; j <= n; j++)
                // is move to subtree labeled partialTour[j] possible ?
                if(a[partialTour[currentLevel - 1]][partialTour[j]] != noEdge && 
                    (costOfBestTourSoFar == noEdge || 
                        costOfPartialTour + a[partialTour[currentLevel - 1]][partialTour[j]] < costOfBestTourSoFar))
                {// search this subtree
                    swap(partialTour[currentLevel], partialTour[j]);
                    costOfPartialTour += a[partialTour[currentLevel - 1]][partialTour[currentLevel]];
                    rTSP(currentLevel + 1);
                    costOfPartialTour -= a[partialTour[currentLevel - 1]][partialTour[currentLevel]];
                    swap(partialTour[currentLevel], partialTour[j]);
                }
        }
    }
    void rDfs(int v)
    {
        graph<T>::reach[v] = graph<T>::label;
        for (int u = 1; u <= n; u++)
            if (a[v][u] != noEdge && graph<T>::reach[u] == 0)
                rDfs(u);
    }

    // class data members used by btSalesperson
    static int* partialTour;
    static int* bestTourSoFar;
    static T costOfBestTourSoFar;
    static T costOfPartialTour;
};

// overload <<
template<typename T>
std::ostream& operator<<(std::ostream& out, const adjacencyWDigraph<T>& x)
{
    x.output(out); return out;
}

// overload >>
template<typename T>
std::istream& operator>>(std::istream& in, adjacencyWDigraph<T>& x)
{
    x.input(in); return in;
}
#endif // !ADJACENCY_WDI_GRAPH_
