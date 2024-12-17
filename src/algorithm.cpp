#include "algorithm.hpp"

Edge chooseRandomEdge(Graph& graph) {
    vector<Edge> edges;
    // Populate the edges vector with all edges and their weights
    int vertices = graph.getVertices();
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < i; ++j) { //Only the lower triangle of the matrix
            if (graph.adjMatrix[i][j] != 0) {
                edges.push_back({i, j, graph.adjMatrix[i][j]});
            }
        }
    }
    // Calculate the total weight
    int totalWeight = 0;
    for (const auto& edge : edges) {
        totalWeight += edge.weight;
    }

    int randomWeight;
    // Generate a random number in the range [0, totalWeight)
    if (totalWeight == 0) {
        return Edge{-1, -1, 0};
    }
    else{
        randomWeight = rand() % totalWeight;
    }

    // Select the edge based on the random weight
    int cumulativeWeight = 0;
    Edge selectedEdge;
    for (const auto& edge : edges) {
        cumulativeWeight += edge.weight;
        if (randomWeight < cumulativeWeight) {
            selectedEdge = edge;
            break;
        }
    }

    return selectedEdge;
}


int bruteForceMinCut(Graph& graph) {
    int n = graph.getVertices();
    int minCut = INT32_MAX;
    int subsetSize = 1 << n; //Shift bits to the left to know the number of subsets
    for (int i = 1; i < subsetSize - 1; ++i) { //Iterate over all subsets i
        int cutSize = 0;
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (((i & (1 << u)) != 0) != ((i & (1 << v)) != 0)) {
                    cutSize += graph.adjMatrix[u][v];
                }
            }
        }
        minCut = min(minCut, cutSize);
    }
    return minCut;
}


int contractAlgorithm(Graph& graph, int t) {
    int vertices = graph.getVertices();
    while (vertices > t) {// until t vertices left (default t=2)
        Edge edge = chooseRandomEdge(graph);
        graph.contract(edge.u, edge.v); //inside the number of vertices is decremented
        vertices--; //nb of vertices is decremented for the loop (can access the number of vertices)
    }

    // Calculate the value of the mincut to return
    int mincut = 0;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < i; j++) { //Only the lower triangle of the matrix
            mincut += graph.adjMatrix[i][j];
        }
    }
    return mincut; //Divide by 2 because we are counting twice the edges (matrix symmetric)
}


int fastCut(Graph& graph) {
    int n = graph.getVertices();
    if(n <= 6) { // if the number of vertices is less than 6
        return bruteForceMinCut(graph);
    }
    else{
        int t = ceil(1 + n/sqrt(2));
        Graph originalGraph = graph; //Save the original graph to avoid copying it again
        contractAlgorithm(graph, t);
        int cutVal1 = fastCut(graph);

        graph = originalGraph;
        contractAlgorithm(graph, t);
        int cutVal2 = fastCut(graph);

        return min(cutVal1, cutVal2);
    }
}