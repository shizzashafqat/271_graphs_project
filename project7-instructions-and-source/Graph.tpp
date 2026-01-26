/*=================================================================================================
File: Graph.tpp
Author: Shizza Fatima Shafqat  
Last Updated:04/23/2025
Description: 
This file implements a directed graph using an adjacency list representation. It includes  
graph operations such as adding and removing edges, and checking for the existence of vertices 
and edges. It also provides implementations for Breadth-First Search (BFS) and Depth-First Search (DFS)
=================================================================================================*/
#include <stdexcept>
#include <climits>
#include <limits>
#include <queue>
#include <algorithm>
#include "Graph.hpp"

/*=================================================================================================
Constructor: Graph
Description:
    Initializes a directed graph with a specified number of vertices.
    Each vertex is represented by an index from 0 to n-1, and the adjacency list is
    initialized to hold an empty list of neighbors for each vertex.
Parameters:
    - int n: the number of vertices in the graph.
=================================================================================================*/
Graph::Graph(int n) : adjList(n) {}

/*=================================================================================================
Copy Constructor: Graph
Description:
    Creates a new graph by copying the adjacency list from another graph.
Parameters:
    - const Graph& g: the graph to copy from.
=================================================================================================*/

Graph::Graph(const Graph &g) : adjList(g.adjList) {}

/*=================================================================================================
Destructor: ~Graph
Description:
    Deallocates the memory used by the graph 
parameters: 
  - none 
=================================================================================================*/
Graph::~Graph() {}

/*=================================================================================================
Assignment Operator: operator=
Description:
    Assigns the contents of one graph to another by copying the adjacency list.
    It checks for self-assignment to prevent unnecessary copying.
Parameters:
    - const Graph& g: the graph to assign from.
Return:
    - Graph&: a reference to the updated graph object.
=================================================================================================*/
Graph& Graph::operator=(const Graph &g) {
    if (this != &g) {
        adjList = g.adjList;
    }
    return *this;
}

/*=================================================================================================
Function: vertexIn
Description:
    Checks whether a given vertex index exists in the graph.
    A vertex is considered valid if it is within the bounds of the adjacency list.
Parameters:
    - int u: the vertex index to check.
Return:
    - bool: true if vertex u is valid, false otherwise.
=================================================================================================*/
bool Graph::vertexIn(int u) {
     // If u is within the valid range of vertex indices
    if (u >= 0 && u < static_cast<int>(adjList.size())) {
        return true; // u is a valid vertex
    } else {
        return false; // u is out of range
    }
}

/*=================================================================================================
Function: edgeIn
Description:
    Checks whether a directed edge exists from vertex u to vertex v in the graph.
    First ensures both vertices are valid. Then searches u's neighbor list to see if v is present.
Parameters:
    - int u: the source vertex.
    - int v: the target vertex.
Return:
    - bool: true if an edge from u to v exists, false otherwise.
=================================================================================================*/
bool Graph::edgeIn(int u, int v) {
    if (!vertexIn(u) || !vertexIn(v)) { //checking if the two vertices exist in the graoh 
        throw std::out_of_range("edgeIn: vertex index out of range");
    }
    //iterate through the adj list of vertex u 
    for (int neighbor : adjList[u]) {
        //if list has v the vertex from u to v already exists
        if (neighbor == v)
            return true;
    }
    //it does not exist 
    return false;
}

/*=================================================================================================
Function: addEdge
Description:
    Adds a directed edge from vertex u to vertex v in the graph.
    The function first checks whether both vertices exist. If the edge does not already exist,
    it is added to u's adjacency list.
Parameters:
    - int u: the source vertex.
    - int v: the destination vertex.
Return:
    - void: this function does not return a value.
=================================================================================================*/
void Graph::addEdge(int u, int v) {
    if (!vertexIn(u) || !vertexIn(v)) { 
        throw std::out_of_range("addEdge: vertex index out of range");
    }
    //add the edge if the edge does not exist already 
    if (!edgeIn(u, v)) {
        adjList[u].push_back(v); // Add v to u's list of neighbors
    }
}
/*=================================================================================================
Function: removeEdge
Description:
    Removes a directed edge from vertex u to vertex v in the graph.
    The function first checks whether both vertices exist. Then, it searches for v in u’s
    adjacency list and removes it if found. If the edge does not exist, an exception is thrown.
Parameters:
    - int u: the source vertex.
    - int v: the destination vertex to remove from u's adjacency list.
Return:
    - void: this function does not return a value.
=================================================================================================*/
void Graph::removeEdge(int u, int v) {
    //list of neighbors for vertex u
    std::vector<int>& neighbors = adjList[u];
    if (!vertexIn(u) || !vertexIn(v)) { 
            throw std::out_of_range("addEdge: vertex index out of range");
        }

    // Tracker - so we can track whether we erased the edge  
    bool found = false;

    // Loop through each neighbor
    for (size_t i = 0; i < neighbors.size(); ++i) {
        //if we see v 
        if (neighbors[i] == v) {
            // Remove the neighbor at position i
            neighbors.erase(neighbors.begin() + i);
            found = true;
            // The loop will still continue, but we only want to remove the first match
            i = neighbors.size(); //to end the loop
        }
    }
    // If v was never found, throw an exception
    if (!found) {
        throw std::out_of_range("removeEdge: edge does not exist");
    }
}
/*=================================================================================================
Function: breadthFirstSearch
Description:
    Performs Breadth-First Search (BFS) starting from a given source vertex s.
    Tracks visited status, parent for each vertex, and the distance from the source.
Parameters:
    - int s: the source vertex to start BFS from.
Return:
    - std::vector<TraversalData>: a vector containing traversal data for each vertex,
      including visited status, parent, and distance from the source.
=================================================================================================*/      
std::vector<TraversalData> Graph::breadthFirstSearch(int s) {
    // Check if the starting vertex exists in the graph
    if (!vertexIn(s)) 
    throw std::out_of_range("BFS: source not in graph");

    // Get the number of vertices in the graph
    int n = adjList.size();

    // Create a vector to hold traversal data for each vertex
    std::vector<TraversalData> data(n);

    // Initialize all traversal data
    for (int i = 0; i < n; ++i) {
        data[i].visited = false; // Not visited yet
        data[i].parent = -1; // No parent yet
        data[i].distance = std::numeric_limits<int>::max(); // Set distance to "infinity"
    }

    // Creating a queue to manage the BFS (everytime it discovers a new vertex it will put it in this queue)
    std::queue<int> q;

    // Initialize the start vertex
    data[s].visited = true; // Mark start vertex as visited
    data[s].distance = 0; // Distance from start vertex to itself is 0
    q.push(s); // Start BFS from s

    // Main BFS loop
    while (!q.empty()) {
        int u = q.front();// Get the vertex at the front of the queue
        q.pop();// Remove it from the queue

        // Visit all neighbors of vertex u
        for (int v : adjList[u]) {
            if (!data[v].visited) { // If neighbor hasn't been visited
                data[v].visited = true; // Mark it as visited
                data[v].parent = u;  // Set parent to u
                data[v].distance = data[u].distance + 1; // add one to the Distance of u
                q.push(v); // Add v to the queue to explore its neighbors
            }
        }
    }
    // Return the BFS result for all vertices
    return data;
}
/*=================================================================================================
Function: depthFirstSearch
Description:
    Performs Depth-First Search (DFS) across the entire graph.
    Tracks visited status, parent, discovery time, finish time, and topological order
    for each vertex.
Parameters:
    - None
Return:
    - std::vector<TraversalData>: a vector containing traversal data for each vertex.
=================================================================================================*/
std::vector<TraversalData> Graph::depthFirstSearch() {
    int n = adjList.size();  // Number of vertices in the graph

    // Create a vector to store traversal data for each vertex
    std::vector<TraversalData> data(n);

    // Initialize all vertices as unvisited with no parent
    for (int i = 0; i < n; ++i) {
        data[i].visited = false;
        data[i].parent = -1;  // -1 represents NIL (no parent)
    }

    int time = 0; // Global time counter for discovery/finish times
    int order = n; // Used for topological ordering (counting down)

    // Traverse each vertex in numerical order
    for (int u = 0; u < n; ++u) {
        // If vertex u hasn't been visited yet, run DFS from it
        if (!data[u].visited) {
            dfsVisit(data, time, u, order);
        }
    }
    // Return traversal data for all vertices
    return data;
}

/*=================================================================================================
Function: dfsVisit
Description:
    A recursive helper function for DFS that visits all reachable vertices from
    the starting vertex u. Sets the discovery and finish times, parent, and order
    for each visited vertex.
Parameters:
    - std::vector<TraversalData>& data: the traversal data to populate.
    - int& time: a reference to the global DFS time counter.
    - int u: the current vertex being visited.
    - int& order: a reference to the current topological order label.
Return:
    - nothing 
=================================================================================================*/
void Graph::dfsVisit(std::vector<TraversalData> &data, int &time, int u, int &order) {
    data[u].visited = true; // Mark u as visited
    data[u].discovery = ++time; // Record discovery time 

    // Visit all neighbors of u
    for (int v : adjList[u]) {
        if (!data[v].visited) {  // If neighbor v hasn't been visited
            data[v].parent = u; // Set u as v's parent
            dfsVisit(data, time, v, order);  // Recursively visit v
        }
    }

    data[u].finish = ++time; // Record finish time after all children are visited
    data[u].order = order--;  // Assign topological order, then decrement
}

/*=================================================================================================
Function: readFromSTDIN
Description:
    Constructs a graph based on data read from a txt file 
Return:
    - Graph: a graph object constructed from the input data.
=================================================================================================*/
Graph Graph::readFromSTDIN() {
    // for readinf in the txt file 
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        std::cout << "Reading edge: " << u << " -> " << v << std::endl;
        g.addEdge(u, v);
    }
    return g;
}

