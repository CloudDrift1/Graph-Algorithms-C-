#ifndef __DIJKSTRA_SHORTEST_PATHS_H_
#define __DIJKSTRA_SHORTEST_PATHS_H_

#include <unordered_map>
#include <optional>
#include <tuple>
#include <limits>
#include <functional>
#include <queue>
#include "graph.hpp" 

/* Given a vertex `v`, `dijkstra_shortest_path` is:
 * - `nullopt` if `v` is not reacheble from `src`.
 * - {`u`, `d`} where `u` is the predecessor of `v` and `d` is the distance
 *   from `src`
 */

struct Compare {
    bool operator()(const std::tuple<edge_weight_t, vertex_t>& a,
                    const std::tuple<edge_weight_t, vertex_t>& b) const {
        return std::get<0>(a) > std::get<0>(b); //min-heap based on weight
    }
};

std::unordered_map<vertex_t,
    std::optional<std::tuple<vertex_t, edge_weight_t>>>
dijkstra_shortest_path(Graph& g, vertex_t src) {

    size_t num_vertices = g.get_adj_list_size(); 
    std::unordered_map<vertex_t, edge_weight_t> dist;  
    std::unordered_map<vertex_t, vertex_t> pred;  
    std::unordered_map<vertex_t, bool> visited;  
    using pq_elem_t = std::tuple<edge_weight_t, vertex_t>;
    std::priority_queue<pq_elem_t, std::vector<pq_elem_t>, Compare> min_heap; //Min-heap priority queue

    // Initialize distances
    for (vertex_t v = 0; v < num_vertices; ++v) {
        dist[v] = std::numeric_limits<edge_weight_t>::infinity();  //distances initialized to infinity
        visited[v] = false;  //initially unvisited
    }
    dist[src] = 0;
    min_heap.push({0, src});  //source vertex

    while (!min_heap.empty()) {
        vertex_t u;
        edge_weight_t d;
        std::tie(d, u) = min_heap.top();
        min_heap.pop();

        //skip visited nodes
        if (visited[u]) continue;
        visited[u] = true;

        //relax all neighbors of u
        for (const auto& neighbor : g.out_edges(u)) {
            vertex_t v = neighbor.first;
            edge_weight_t weight = neighbor.second;

            //update if shorter distance is found
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                min_heap.push({dist[v], v});
            }
        }
    }

    //get result map
    std::unordered_map<vertex_t, std::optional<std::tuple<vertex_t, edge_weight_t>>> result;
    for (vertex_t v = 0; v < num_vertices; ++v) {
        if (visited[v] && v != src) {
            result[v] = std::make_tuple(pred[v], dist[v]);
        } 

        else if(v == src){  // placeholder for source node
            result[v] = std::make_tuple(-1, dist[v]);
        }
        
        else {
            result[v] = std::nullopt;
        }
    }
    return result;
}

#endif // __DIJKSTRA_SHORTEST_PATHS_H_