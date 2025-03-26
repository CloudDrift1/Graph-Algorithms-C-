#ifndef __TOPOLOGICAL_SORT_H_
#define __TOPOLOGICAL_SORT_H_

#include <vector>
#include <queue>
#include <algorithm>
#include "graph.hpp"


/* Return _a_ valid topologically sorted sequence of vertex descriptors */
std::vector<vertex_t> topological_sort(Graph& g) {

	size_t num_vertices = g.get_adj_list_size(); 
    std::vector<int> in_degree(num_vertices, 0); 
    std::queue<vertex_t> q;
    std::vector<vertex_t> topo_order;

    //indegree claculation
    for (vertex_t u = 0; u < num_vertices; ++u) {
        for (const auto& neighbor : g.out_edges(u)) {
            vertex_t v = neighbor.first;
            in_degree[v]++;
        }
    }

    //enqueue 0 indegree nodes
    for (vertex_t u = 0; u < num_vertices; ++u) {
        if (in_degree[u] == 0) {
            q.push(u);
        }
    }

    //loop while queue isn't empty
    while (!q.empty()) {
        vertex_t u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (const auto& neighbor : g.out_edges(u)) {
            vertex_t v = neighbor.first;
            if (--in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    //cycle check
    if (topo_order.size() != num_vertices) {
        return {}; //cycle detected
    }

    return topo_order;
}

#endif // __TOPOLOGICAL_SORT_H_
