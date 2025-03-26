#ifndef __PRIM_MINIMUM_SPANNING_TREE_H_
#define __PRIM_MINIMUM_SPANNING_TREE_H_

#include <optional>
#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>
#include <queue>
#include <limits>

/* Returns the vector of edges in the MST, or std::nullopt if MST does
 * not exist */

std::optional<edges_t>
prim_minimum_spanning_tree(Graph& g, vertex_t src) {

	size_t num_vertices = g.get_adj_list_size();
    std::vector<bool> in_mst(num_vertices, false);  
    std::vector<edge_weight_t> min_edge_weights(num_vertices, std::numeric_limits<edge_weight_t>::infinity());
    std::vector<vertex_t> parent(num_vertices, -1); 
    std::priority_queue<std::tuple<edge_weight_t, vertex_t>,
                        std::vector<std::tuple<edge_weight_t, vertex_t>>,
                        std::greater<>> min_heap; 

    min_edge_weights[src] = 0;  
    min_heap.push({0, src});  

    edges_t mst_edges;  

    while (!min_heap.empty()) {
        vertex_t u;
        edge_weight_t weight;
        std::tie(weight, u) = min_heap.top();
        min_heap.pop();

        //if vertex is already in the MST, skip it
        if (in_mst[u]) continue;

        in_mst[u] = true;

        //add the edge to the MST
        if (parent[u] != -1) {
            mst_edges.push_back({parent[u], u, weight});
        }

        for (const auto& neighbor : g.out_edges(u)) {
            vertex_t v = neighbor.first;
            edge_weight_t edge_weight = neighbor.second;

            if (!in_mst[v] && edge_weight < min_edge_weights[v]) {
                min_edge_weights[v] = edge_weight;
                parent[v] = u;
                min_heap.push({edge_weight, v});
            }
        }
    }

    //disconnected graph test
    for (bool in_tree : in_mst) {
        if (!in_tree) {
            return std::nullopt;  //disconnected graph
        }
    }

    return mst_edges;  
}
#endif // __PRIM_MINIMUM_SPANNING_TREE_H_