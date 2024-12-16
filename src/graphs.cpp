#include "graphs.hpp"
#include <vector>

using namespace std;

// Initialize graph with n vertices
vector<vector<int>> initializeGraph(int n) {
    // Adjacency matrix to store capacities
    vector<vector<int>> graph;
    graph.assign(n, vector<int>(n, 0));
    return graph;
}

// Add edge
void addEdge(vector<vector<int>> graph, int u, int v, int capacity) {
    graph[u][v] = capacity;
    // For undirected graph, uncomment:
    // graph[v][u] = capacity;
}