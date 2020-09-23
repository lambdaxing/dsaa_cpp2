// adjacency matrix representation of an undirected graph

#ifndef adjacencyGraph_
#define adjacencyGraph_

#include <iostream>
#include <sstream>
#include <iterator>
#include "adjacencyWGraph.h"
#include "unweightedEdge.h"

class adjacencyGraph : public adjacencyWGraph<bool>
{
public:
    adjacencyGraph(int numberOfVertices = 0)
        : adjacencyWGraph<bool>(numberOfVertices, false) {}     // false denote absent edge

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
        this->a[v2][v1] = true;
    }

    int btMaxClique(int *maxClique)
    {// Solve max-clique problem using backtracking.
     // Set maxClique[] so that maxClique[i] = 1 if i is in max cluque.
     // Return size of max cluque.
        // initialize for rClique
        currentClique = new int[n + 1];
        sizeOfCurrentClique = 0;
        sizeOfMaxCliqueSoFar = 0;
        maxCliqueSoFar = maxClique;

        // find max clique
        rClique(1);
        return sizeOfMaxCliqueSoFar;
    }

    // structs used by max-profit branch-and-bound max clique
    struct bbNode
    {
        // instance data members
        std::shared_ptr<bbNode> parent;
        bool leftChild;     // true if left child of parent

        // constructors
        bbNode() {}

        bbNode(std::shared_ptr<bbNode> theParent, bool theLeftChild)
        {
            parent = theParent;
            leftChild = theLeftChild;
        }
    };

    struct heapNode
    {
        // data members
        std::shared_ptr<bbNode> liveNode;
        int upperSize;      // upper bound on clique size in this subtree
        int cliqueSize;     // size of clique at this node
        int level;

        // consturctors
        heapNode() {}

        heapNode(std::shared_ptr<bbNode> theLiveNode, int theUpperSize, int theCliqueSize, int theLevel)
            :liveNode(theLiveNode), upperSize(theUpperSize), cliqueSize(theCliqueSize), level(theLevel) {}

        bool operator<(const heapNode rhs) const
        {
            return upperSize < rhs.upperSize;
        }

        operator int() { return upperSize; }
    };

    int maxProfitBBMaxClique(int* maxClique)
    {// Max-profit branch-and-bound code to find a max clique.
     // maxClique[i] is set to 1 if i is in max clique.
     // Return size of max clique.
        // initialize for level 1 start
        std::shared_ptr<bbNode> eNode = nullptr;
        int eNodeLevel = 1;
        int sizeOfCliqueAtENode = 0;
        int sizeOfMaxCliqueSoFar = 0;

        // search subset space tree
        while (eNodeLevel != n + 1)
        {// while not at leaf
            // see if vertex eNodeLevel is connected to all vertices in the current clique
            bool connected = true;
            std::shared_ptr<bbNode> currentNode = eNode;
            for (int j = eNodeLevel - 1; j > 0; currentNode = currentNode->parent, j--)
                if (currentNode->leftChild && !a[eNodeLevel][j])
                {// j is in the clique but no edge between eNodeLevel and j 
                    connected = false;
                    break;
                }

            if(connected)
            {// left child is feasible
                if (sizeOfCliqueAtENode + 1 > sizeOfMaxCliqueSoFar)
                    sizeOfMaxCliqueSoFar = sizeOfCliqueAtENode + 1;
                addLiveNode(sizeOfCliqueAtENode + n - eNodeLevel + 1, sizeOfCliqueAtENode + 1, eNodeLevel + 1, eNode, true);
            }

            if (sizeOfCliqueAtENode + n - eNodeLevel >= sizeOfMaxCliqueSoFar)
                // right child has prospects
                addLiveNode(sizeOfCliqueAtENode + n - eNodeLevel, sizeOfCliqueAtENode, eNodeLevel + 1, eNode, false);

            // get next E-node, heap cannot be empty
            heapNode nextENode = liveNodeMaxHeap.top();
            liveNodeMaxHeap.pop();
            eNode = nextENode.liveNode;
            sizeOfCliqueAtENode = nextENode.cliqueSize;
            eNodeLevel = nextENode.level;
        }

        // construct maxClique[] by following path from eNode to the root
        for (int j = n; j > 0; j--)
        {
            maxClique[j] = (eNode->leftChild) ? 1 : 0;
            eNode = eNode->parent;
        }

        return sizeOfMaxCliqueSoFar;
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
            in >> v1 >> v2;

            if (v1 < 1 || v2 < 1 || v1 > this->n || v2 > this->n || v1 == v2)
            {
                std::ostringstream s;
                s << "(" << v1 << "," << v2
                    << ") is not a permissible edge";
                throw illegalParameterValue(s.str());
            }

            this->a[v1][v2] = true;
            this->a[v2][v1] = true;
        }
    }

    bool weighted() const { return false; }

protected:
    // recursive backtracking code to compute largest clique
    void rClique(int currentLevel)
    {// search from a node at currentLevel
        if(currentLevel > n)
        {// at leaf, found a larger clique
         // update maxCliqueSoFar and sizeOfMaxCliqueSoFar
            for (int j = 1; j <= n; j++)
                maxCliqueSoFar[j] = currentClique[j];
            sizeOfMaxCliqueSoFar = sizeOfCurrentClique;
            return;
        }

        // not at leaf; see whether vertex currentLevel is connected to others in current clique
        bool connected = true;
        for(int j = 1; j < currentLevel; j++)
            if(currentClique[j] == 1 && !a[currentLevel][j])
            {// vertex currentLevel not connected to j
                connected = false;
                break;
            }

        if(connected)
        {// try left subtree
            currentClique[currentLevel] = 1;        // add to clique
            sizeOfCurrentClique++;
            rClique(currentLevel + 1);
            sizeOfCurrentClique--;
        }

        if(sizeOfCurrentClique + n - currentLevel > sizeOfMaxCliqueSoFar)
        {// try right subtree
            currentClique[currentLevel] = 0;
            rClique(currentLevel + 1);
        }
    }

    // class data members used by backtracking max clique
    static int* currentClique;
    static int sizeOfCurrentClique;
    static int sizeOfMaxCliqueSoFar;
    static int* maxCliqueSoFar;

    // class data member used by max-profit branch-and-bound max clique
    static std::priority_queue<heapNode> liveNodeMaxHeap;

    void addLiveNode(int upperSize,int theSize,int theLevel,std::shared_ptr<bbNode> theParent,bool leftChild)
    {// Add a new live node to the max heap.
     // Also add the live node to the solution space tree.
     // theSize = size of clique at this live node.
     // theParent = parent of new node.
     // leftChild = true if new node if left child of theParent.
        // create the new node of the solution space tree
        std::shared_ptr<bbNode> b = std::make_shared<bbNode>(theParent, leftChild);

        // insert corresponding node into max heap
        liveNodeMaxHeap.push(heapNode(b, upperSize, theSize, theLevel));
    }
};

// overload <<
std::ostream& operator<<(std::ostream& out, const adjacencyGraph& x)
{
    x.output(out); return out;
}
// overload >>
std::istream& operator>>(std::istream& in, adjacencyGraph& x)
{
    x.input(in); return in;
}


int* adjacencyGraph::currentClique;
int adjacencyGraph::sizeOfCurrentClique;
int adjacencyGraph::sizeOfMaxCliqueSoFar;
int* adjacencyGraph::maxCliqueSoFar;
std::priority_queue<adjacencyGraph::heapNode> adjacencyGraph::liveNodeMaxHeap;

#endif
