# Graph Algorithms: Dijkstra, Prim's MST, Topological Sort

This repository contains the template based implementation of three fundamental graph algorithms in C++:

1. **Dijkstra's Shortest Path**
2. **Prim's Minimum Spanning Tree (MST)**
3. **Topological Sort**

C++17 is required to run the program.

## Table of Contents

- [Graph Algorithms](#graph-algorithms)
- [Graph ADT](#graph-adt)
  - [Dijkstra's Algorithm](#Dijkstra's-Shortest-Path)
  - [Prim's MST](#Prim's-Minimum-Spanning-Tree-(MST))
  - [Topological Sort](#Topological-Sort)
- [Compilation and Testing](#compilation-and-testing)


## Graph Algorithms


### Graph ADT
The Graph class is based on an adjacency list, with the following key types:

* vertex_t: Type for vertices (std::size_t).

* edge_t: Tuple (vertex_t, vertex_t, edge_weight_t) representing edges.

* edges_t: Vector of edge_t for storing graph edges.

* GraphType: Enum for directed or undirected graph.

### Dijkstra's Shortest Path
Finds the shortest path from a source vertex to all other vertices.

```cpp
std::unordered_map<vertex_t, std::optional<std::tuple<vertex_t, edge_weight_t>>> 
dijkstra_shortest_path(Graph& g, vertex_t src);
```
### Prim's Minimum Spanning Tree (MST)
Finds the minimum spanning tree of a graph.

```cpp
std::optional<edges_t> prim_minimum_spanning_tree(Graph& g, vertex_t src);
```
### Topological Sort
Returns a topologically sorted order of vertices in a directed acyclic graph.

```cpp
std::vector<vertex_t> topological_sort(Graph& g);
```
## Compilation and Testing
To compile and test the implementation:

Clone the repository.

Create a build directory and compile:

```bash
mkdir build
cd build
cmake ..
make
```
Run the test:

```bash
./tests/graph_test
```
You can add your own unit tests using Catch2.

