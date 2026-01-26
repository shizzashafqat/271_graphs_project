#pragma once

#include <iostream>
#include <vector>
#include <deque>

struct TraversalData {
    bool visited;
    int parent;
    union {
        struct {
            int discovery;
            int finish;
            int order;
        };
        struct {
            int distance;
        };
    };
};

class Graph {
    private:
    // assume vertices are 0...n-1;
    std::vector<std::vector<int> > adjList; // adjacency list

    // order is a variable used to keep track of the position of the last element placed in the topological ordering
    void dfsVisit(std::vector<TraversalData> &data, int &time, int u, int &order);

    public:
    Graph(int n);

    Graph(const Graph &g);

    ~Graph(void);

    Graph& operator=(const Graph &g);

    // return true if u is in the graph, false otherwise
    bool vertexIn(int u);

    // throw an std::out_of_range exception if u or v is not in the graph
    bool edgeIn(int u, int v);

    // throw an std::out_of_range exception if u or v is not in the graph
    void addEdge(int u, int v);

    // throw an std::out_of_range exception if u or v is not in the graph
    // throw an std::out_of_range exception if (u, v) is not an edge of the graph
    void removeEdge(int u, int v);

    // assume vertices are traversed in numerical order
    // implement this without use the "colors" approach
    // throw an std::out_of_range exception if s is not in graph
    // use -1 as NIL
    // use INT_MAX as infinity
    std::vector<TraversalData> breadthFirstSearch(int s);

    // assume vertices are traversed in numerical order
    // implement this without use the "colors" approach
    std::vector<TraversalData> depthFirstSearch(void);

    static Graph readFromSTDIN();
};

#include "Graph.tpp"