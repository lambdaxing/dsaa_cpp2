// adjacency matrix representation of a weighted undirected graph

#ifndef adjacencyWGraph_
#define adjacencyWGraph_

#include "adjacencyWDigraph.h"

template <class T>
class adjacencyWGraph : public adjacencyWDigraph<T>
{
public:
    adjacencyWGraph(int numberOfVertices = 0, T theNoEdge = 0)
        : adjacencyWDigraph<T>(numberOfVertices, theNoEdge) {}
    void insertEdge(edge<T>* theEdge)
    {// Insert edge theEdge into the graph; if the edge is already
     // there, update its weight to theEdge.weight().
        int v1 = theEdge->vertex1();
        int v2 = theEdge->vertex2();
        if (v1 < 1 || v2 < 1 || v1 > this->n || v2 > this->n || v1 == v2)
        {
            std::ostringstream s;
            s << "(" << v1 << "," << v2
                << ") is not a permissible edge";
            throw illegalParameterValue(s.str());
        }

        if (this->a[v1][v2] == this->noEdge)  // new edge
            this->e++;
        this->a[v1][v2] = theEdge->weight();
        this->a[v2][v1] = theEdge->weight();
    }

    bool directed() const { return false; }

    void eraseEdge(int i, int j)
    {// Delete the edge (i,j).
        if (i >= 1 && j >= 1 && i <= this->n && j <= this->n && this->a[i][j] != this->noEdge)
        {
            this->a[i][j] = this->noEdge;
            this->a[j][i] = this->noEdge;
            this->e--;
        }
    }

    int degree(int theVertex) const
    {// Return degree of vertex theVertex.
        this->checkVertex(theVertex);

        // count out edges from vertex theVertex
        int sum = 0;
        for (int j = 1; j <= this->n; j++)
            if (this->a[theVertex][j] != this->noEdge)
                sum++;

        return sum;
    }

    int outDegree(int theVertex) const
    {// Return out-degree of vertex theVertex.
        return degree(theVertex);
    }

    int inDegree(int theVertex) const
    {// Return in-degree of vertex theVertex.
        return degree(theVertex);
    }

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
            T w;
            in >> v1 >> v2 >> w;

            if (v1 < 1 || v2 < 1 || v1 > this->n || v2 > this->n || v1 == v2)
            {
                std::ostringstream s;
                s << "(" << v1 << "," << v2
                    << ") is not a permissible edge";
                throw illegalParameterValue(s.str());
            }

            this->a[v1][v2] = w;
            this->a[v2][v1] = w;
        }
    }

};

// overload <<
template<typename T>
std::ostream& operator<<(std::ostream& out, const adjacencyWGraph<T>& x)
{
    x.output(out); return out;
}

// overload >>
template<typename T>
std::istream& operator>>(std::istream& in, adjacencyWGraph<T>& x)
{
    x.input(in); return in;
}
#endif
