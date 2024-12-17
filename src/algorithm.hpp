#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "Graph.hpp"
#include <cmath>
#include <vector>

using namespace std;

struct Edge {
    int u, v, weight;
};

/**
* @brief Assure to choose a random edge from the graph poderated by its weight
* @param graph The graph
* @return The random edge (struct Edge)
*/
Edge chooseRandomEdge(Graph& graph);

/**
* @brief Implementation of the brute force algorithm
* @return The minimum cut value
*/
int bruteForceMinCut(Graph& graph);

/**
* @brief Contract the graph until only two vertices remain (simple kargers algorithm)
* @param graph The graph
* @param t The number of vertices to remain
* @return The minimum cut value
*/
int contractAlgorithm(Graph& graph, int t=2);

/**
* @brief Implementation of the fast cut algorithm
* @return The minimum cut value
*/
int fastCut(Graph& graph);



#endif // ALGORITHM_HPP