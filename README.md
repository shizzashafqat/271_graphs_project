Graph Algorithms in C++

Project 7: Graphs: Everything Everywhere All at Once

Overview

This project implements a directed graph data structure using an adjacency list representation, along with several fundamental graph algorithms:
- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Topological Sorting

The goal of the project is to deepen understanding of graph representations, traversal strategies, and how algorithmic metadata (distance, discovery time, finish time, order, etc.) can be stored and managed efficiently in C++.
All graph logic is implemented in Graph.tpp, and correctness is validated using a custom test suite in studentTests.cpp.

Features: 
- Directed graph with adjacency list representation
- BFS with distance tracking from a source vertex
- DFS with discovery time, finish time, and topological order labeling
- Ability to construct a graph from standard input
- Clean, well-documented code following project specifications


Graph Input Format

Graphs can be created using standard input with the following format:

n m
u1 v1
u2 v2
...
um vm


Where:

n = number of vertices

m = number of edges

Each ui vi pair represents a directed edge from ui to vi

Example:

4 4
0 1
0 2
1 2
2 3

Compilation

Use a C++17-compatible compiler such as g++:

g++ -std=c++17 studentTests.cpp -o studentTests

Running Tests

To run the test suite:

./studentTests


To provide graph input via a file:

./studentTests < myGraph.txt
