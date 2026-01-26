#include <iostream>
#include <cassert>
#include <limits>
#include "Graph.hpp"


// test cases for graphs

// Test construction and addEdge/edgeIn
void testAddAndEdgeIn() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    assert(g.edgeIn(0, 1));
    assert(g.edgeIn(1, 2));
    assert(g.edgeIn(3, 4));
    assert(!g.edgeIn(0, 4));

    std::cout << "AddEdge and EdgeIn tests passed.\n";
}

// Test removeEdge
void testRemoveEdge() {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);

    g.removeEdge(0, 1);
    assert(!g.edgeIn(0, 1));

    try {
        g.removeEdge(0, 1);
        assert(false); // should throw
    } catch (const std::out_of_range&) {
        std::cout << "RemoveEdge throws on nonexistent edge - passed.\n";
    }
}

// Test vertexIn
void testVertexIn() {
    Graph g(4);
    assert(g.vertexIn(0));
    assert(g.vertexIn(3));
    assert(!g.vertexIn(4));

    std::cout << "VertexIn test passed.\n";
}

// Test copy constructor
void testCopyConstructor() {
    Graph g(3);
    g.addEdge(0, 1);
    Graph copy(g);

    assert(copy.edgeIn(0, 1));
    copy.addEdge(1, 2);
    assert(!g.edgeIn(1, 2));

    std::cout << "Copy constructor test passed.\n";
}

// Test assignment operator
void testAssignmentOperator() {
    Graph g1(2);
    g1.addEdge(0, 1);

    Graph g2(2);
    g2 = g1;

    assert(g2.edgeIn(0, 1));
    g2.addEdge(1, 0);
    assert(!g1.edgeIn(1, 0)); 

    std::cout << "Assignment operator test passed.\n";
}

// Test BFS
void testBFS() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(4, 5);

    auto bfs = g.breadthFirstSearch(0);
    assert(bfs[0].distance == 0);
    assert(bfs[1].distance == 1);
    assert(bfs[3].distance == 2);
    assert(bfs[5].distance == 3);

    std::cout << "Breadth-First Search test passed.\n";
}

// Test DFS and topological order
void testDFS() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    auto dfs = g.depthFirstSearch();

    // All nodes should have order > 0, no duplicates
    std::vector<int> seenOrders(7, 0);
    for (const auto& d : dfs) {
        assert(d.order > 0);
        seenOrders[d.order]++;
    }
    for (int i = 1; i <= 6; ++i) {
        assert(seenOrders[i] == 1); // each order should be unique
    }

    std::cout << "Depth-First Search and Topological Ordering test passed.\n";
    
}

// void testReadFromSTDIN(Graph& g) {
//     std::cout << "Running readFromSTDIN() test...\n";

//     assert(g.edgeIn(0, 1));
//     assert(g.edgeIn(0, 2));
//     assert(g.edgeIn(1, 3));
//     assert(g.edgeIn(1, 4));

//     assert(!g.edgeIn(3, 4));
//     assert(!g.edgeIn(2, 1));

//     std::cout << "readFromSTDIN() test passed.\n";
// }

// void testReadAndRunBFSFromSTDIN(Graph& g) {
//     assert(g.edgeIn(0, 2));
//     assert(g.edgeIn(0, 1));
//     assert(g.edgeIn(1, 3));
//     assert(g.edgeIn(1, 4));
//     assert(!g.edgeIn(2, 4));

//     std::vector<TraversalData> bfsData = g.breadthFirstSearch(0);

//     std::cout << "testReadAndRunBFSFromSTDIN() passed.\n";
// }

int main() {
    // Graph A(0);
    // Graph g = A.readFromSTDIN();

    // std::cout << "========== Running tests using stdin ==========\n";
    // testReadFromSTDIN(g);
    // testReadAndRunBFSFromSTDIN(g);  
    std::cout << "========== Running All Graph Tests ==========\n";
    testAddAndEdgeIn();
    testRemoveEdge();
    testVertexIn();
    testCopyConstructor();
    testAssignmentOperator();
    testBFS();
    testDFS();

    std::cout << "=======  All Graph Tests Passed Successfully!  ========\n";
    return 0;
}
