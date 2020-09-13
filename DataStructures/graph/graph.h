// abstract class graph
// abstract data type specification for graph data structure
// includes methods that are representation independent

#ifndef GRAPH_
#define GRAPH_

#include <queue>
#include "edge.h"
#include "vertexIterator.h"
#include "myExceptions.h"
#include "weightedEdge.h"
#include "binNode.h"
#include "fastUnionFind.h"
#include <stack>

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

    bool topologicalOrder(int *theOrder)
    {// Return false if the digraph has no topological order.
     // theOrder[0:n-1] is set to a topological order when such an order exists.
        // make sure this is a digraph
        if (!directed())
            throw undefinedMethod("graph::topologicalOrder() not define for undirected graphs");

        int n = numberOfVertices();

        // compute in-degrees
        int* inDegree = new int[n + 1];
        std::fill(inDegree + 1, inDegree + n + 1, 0);
        for(int i = 1;i <= n; i++)
        {// edges out of vertex i
            vertexIterator<T>* ii = iterator(i);
            int u;
            while ((u = ii->next()) != 0)
                // visit an adjacent vertex of i
                inDegree[u]++;
        }

        // stack vertices with zero in-degree
        std::stack<int> stack;
        for (int i = 1; i <= n; i++)
            if (inDegree[i] == 0)
                stack.push(i);

        // generate topological order
        int j = 0;  // cursor for array theOrder
        while(!stack.empty())
        {// select from stack
            int nextVertex = stack.top();
            stack.pop();
            theOrder[j++] = nextVertex;
            // update in-degrees
            vertexIterator<T>* iNextVertex = iterator(nextVertex);
            int u;
            while((u = iNextVertex->next()) != 0)
            {// visit an adjacent vertex of nextVertex
                inDegree[u]--;
                if (inDegree[u] == 0)
                    stack.push(u);
            }
        }
        return (j == n);
    }

    int bipartiteCover(int* theLabel, int* theCover)
    {// Return -1 if the bipartite graph has no cover.
     // Return cover size if there is a cover.
     // theLabel is bipartite labeling, theLabel[i] = 1 if i is in A.
     // theCover[i], i >= 0 is set to the cover ( if there is one).
        int n = numberOfVertices();

        // create structures
        int sizeOfA = 0;
        for (int i = 1; i <= n; i++)  // find size of set A
            if (theLabel[i] == 1)
                sizeOfA++;
        int sizeOfB = n - sizeOfA;
        createBins(sizeOfB, n);
        int* newVerticesCovered = new int[n + 1];
                        // vertex i covers newVerticesCovered[i] uncovered vertices of B
        bool* changed = new bool[n + 1];
                        // changed[i] is true if newVerticesCovered[i] has changed
        std::fill(changed + 1, changed + n + 1, false);
        bool* covered = new bool[n + 1];
                // covered[i] is true if vertex i is covered
        std::fill(covered + 1, covered + n + 1, false);
        std::stack<int> stack;

        // initialize
        for(int i = 1; i <= n; i++)
            if(theLabel[i] == 1)
            {// i is in A
                newVerticesCovered[i] = degree(i);  // i covers this many
                insertBins(newVerticesCovered[i], i);
            }

        // construct cover
        int numberCovered = 0;  // # of B vertices covered
        int maxBin = sizeOfB;   // max bin that may be nonempty
        int coverSize = 0;      // number of A vertices in cover
        while (maxBin > 0)       // search all bins
            if (bin[maxBin] != 0)        // bin maxBin is not empty
            {
                int v = bin[maxBin];        // first vertex
                theCover[coverSize++] = v;  // add v to cover
                // label newly covered vertices
                vertexIterator<T>* iv = iterator(v);
                int j;
                while ((j = iv->next()) != 0)
                {
                    if (!covered[j])     // j not covered yet
                    {
                        covered[j] = true;
                        numberCovered++;
                        // update new VerticesCovered
                        vertexIterator<T>* ij = iterator(j);
                        int k;
                        while ((k = ij->next()) != 0)
                        {
                            newVerticesCovered[k]--;    // j dose not count
                            if (!changed[k])
                            {
                                stack.push(k);  // stack once only
                                changed[k] = true;
                            }
                        }
                    }
                }
                // update bins
                while (!stack.empty())
                {
                    int k = stack.top();
                    stack.pop();
                    changed[k] = false;
                    moveBins(sizeOfB, newVerticesCovered[k], k);
                }
            }
            else
                maxBin--;   // go to next bin
        return (numberCovered == sizeOfB) ? coverSize : -1;
    }

    bool kruskal(weightedEdge<T>* spanningTreeEdges)
    {// Find a min cost spanning tree using Kruskal's method.
     // Return false if the weighted undirected graph is not connected.
     // spanningTreeEdges[0:n-2] has the min-cost-tree edges when done.
        if (directed() || !weighted())
            throw undefinedMethod("graph::kruskal() not defined for unweighted and directed graphs");

        int n = numberOfVertices();
        int e = numberOfEdges();
        // set up array of graph edges
        weightedEdge<T>* edge = new weightedEdge<T>[e + 1];
        int k = 0;      // cursor for edge[]
        for (int i = 1; i <= n; i++)
        {// get all edges incident to i
            vertexIterator<T>* ii = iterator(i);
            int j;
            T w;
            while ((j = ii->next(w)) != 0)
                if (i < j) // add to edge array
                    edge[++k] = weightedEdge<int>(i, j, w);
        }
        // put edges in min heap
        std::priority_queue < weightedEdge<T>, std::vector<weightedEdge<T>, std::greater<weightedEdge<T>>> heap(std::begin(edge), std::end(edge));
        
        fastUnionFind uf(n);        // union/find structrue

        // extract edges in cost order and select/reject
        k = 0;  // use as cursor for t now
        while(e > 0 && k < n - 1)
        {// spanning tree not complete & edges remain
            weightedEdge<T> x = heap.top();
            heap.pop();
            e--;
            int a = uf.find(x.vertex1());
            int b = uf.find(x.vertex2());
            if(a != b)
            {// select edge x
                spanningTreeEdges[k++] = x;
                uf.unite(a, b);
            }
        }

        delete edge;        // ?
        return (k == n - 1);
    }

    bool prim(weightedEdge<T>* spanningTreeEdges)
    {// Find a min cost spanning tree using Prim's method.
     // Return false if the weighted undirected graph is not connected.
     // spanningTreeEdges[0:n-2] has the min-cost-tree edges when done.
        if (directed() || !weighted())
            throw undefinedMethod("graph::prim() not defined for unweighted and directed graphs");

        int n = numberOfVertices();
        int e = numberOfEdges();

        bool* inSpanning = new bool[n + 1];                         // vertex set
        std::fill(inSpanning + 1, inSpanning + n + 1, false);       // false is not in spanningTreeEdges

        int k = 0;
        std::priority_queue< weightedEdge<T>, std::vector<weightedEdge<T>, std::greater<weightedEdge<T>>> heap;     // 未在spanningTreeEdges内且与spanningTreeEdges中的顶点相连的边

        // 初始化，将顶点1加入点集，顶点1的边加入小根堆
        inSpanning[1] = true;                   // put vertex 1 into spanning
        vertexIterator<T>* ii = iterator(1);
        int j;
        T w;
        while ((j = ii->next(w)) != 0)
            heap.push(weightedEdge<T>(1, j, w));        // put edges of vertex 1 into heap

        while (e > 0 && k < n - 1)
        {
            if (heap.empty())
                break;
            weightedEdge<T> x = heap.top();
            heap.pop();

            spanningTreeEdges[k++] = x;     // 从 heap 取出权最小的边入spanning
            e--;

            // 将新加入spanning的边的新顶点的其他边入heap
            auto notInSpanningVertex = x.vertex2();
            ii = iterator(notInSpanningVertex);
            while ((j = ii->next(w)) != 0)
            {
                if (!inSpanning[j])     // 判断该顶点是否在spanning中
                {
                    heap.push(weightedEdge<T>(x.vertex2(), j, w));
                    inSpanning[j] = true;
                }
            }
        }

        delete[] inSpanning;
        return (k == n - 1);
    }

 protected:
     static int* reach;
     static int* path;
     static int label;
     static int length;
     static int destination;
     static int* bin;   // pointer to first node in bin
     static binNode* node;

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

     void createBins(int b, int n)
     {// Create b empty bins and n nodes.
         bin = new int[b + 1]; 
         std::fill(bin, bin + b + 1, 0);
         node = new binNode[n + 1];
     }

     void insertBins(int b, int v)
     {// Insert v into bin b unless b is zero.
         if (b == 0)
             return;    // do not insert in bin 0

         node[v].left = b;   // add at left end of bin b
         if (bin[b] != 0)    // bin b is not empty
             node[bin[b]].left = v;
         node[v].right = bin[b];
         bin[b] = v;
     }

     void moveBins(int bMax, int toBin, int v)
     {// Move vertex v from its current bin to bin toBin.
      // bMax is rightmost nonempty bin.
         // nodes to the left and right of v
         int l = node[v].left;
         int r = node[v].right;

         // delete v from current bin
         if (r != 0) // v has a node to its left
             node[r].left = node[v].left;       // 右边有个箱子
         if (l > bMax || bin[l] != v)    // not left-most one
             node[l].right = r;                 // 左边有个箱子，左边无箱子时：k < bMax && bin[l] == v ( node[v].left == i (bin[i] == v) )
         else  // left-most in bin l
             bin[l] = r;                        // 左边没有箱子,l 为其当前箱子。

         // add to bin toBin
         insertBins(toBin, v);
     }

};

#endif // !GRAPH_
