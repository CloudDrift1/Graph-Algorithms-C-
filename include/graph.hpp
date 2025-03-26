#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>
#include <limits>
#include <functional>

/* A vertex is typed as `vertex_t`. An edge is typed as `edge_t`,
which is associated with a source vertex, a destination vertex, and
its weight. A list of edges is typed as `edges_t`, which is a
vector of `edge_t`. */

using vertex_t = std::size_t;
using edge_weight_t = double;
using edge_t = std::tuple<vertex_t,
                          vertex_t,
                          edge_weight_t>;
using edges_t = std::vector<edge_t>;

enum class GraphType {
UNDIRECTED,
DIRECTED
};

class Graph {
    public:
        Graph() = delete;
        Graph(const Graph&) = delete;
        Graph(Graph&&) = delete;

        /* Assume that if num_vertices is n, a graph contains n vertices
           from 0 to n-1. */
        Graph(size_t num_vertices,
              const edges_t& edges,
              GraphType Type) {

            adj_list_.resize(num_vertices); 

            for (const auto& edge : edges) {
            vertex_t u = std::get<0>(edge); 
            vertex_t v = std::get<1>(edge); 
            edge_weight_t weight = std::get<2>(edge); 

            adj_list_[u].push_back({v, weight}); 

            if (Type == GraphType::UNDIRECTED) {
                adj_list_[v].push_back({u, weight}); 
            }
        }

        }

    const std::list<std::pair<vertex_t, edge_weight_t>>& out_edges(vertex_t v) const {
    return adj_list_[v];
}

    unsigned int get_adj_list_size() const{
        return adj_list_.size();
    }
		
    private:
        std::vector<std::list<std::pair<vertex_t, edge_weight_t>>> adj_list_;
};

#endif // __GRAPH_H_
