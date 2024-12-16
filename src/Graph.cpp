#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

Graph::Graph(int vertices) { //constructor
    this->vertices = vertices;
    adjMatrix.resize(vertices, vector<int>(vertices, 0));
}

void Graph::addEdge(int v, int w) {
    adjMatrix[v][w] = 1;
    adjMatrix[w][v] = 1;
}

void Graph::addEdge(int v, int w, int weight) {
    adjMatrix[v][w] = weight;
    adjMatrix[w][v] = weight;
}

int Graph::getVertices() const{
    return vertices;
}

void Graph::setMinCut(int mincut) {
    this->mincut = mincut;
}

int Graph::getMinCut() const{
    return mincut;
}

void Graph::setSubsetCut(set<int> subsetCut1, set<int> subsetCut2) {
    this->subsetCut1 = subsetCut1;
    this->subsetCut2 = subsetCut2;
}

set<int> Graph::getSubsetCut1() const{
    return subsetCut1;
}

set<int> Graph::getSubsetCut2() const{
    return subsetCut2;
}

void Graph::contract(int u, int v) {
    for (int i = 0; i < vertices; i++) {
        adjMatrix[u][i] += adjMatrix[v][i]; //add the values of the second vertex to the first vertex
        adjMatrix[i][u] += adjMatrix[i][v];
    }
    adjMatrix[u][u] = 0; //we don't want self loops
    for (int i = 0; i < vertices; i++) { //rearrange the matrix
        adjMatrix[i][v] = adjMatrix[vertices - 1][i]; //copy the last row to the second vertex
        adjMatrix[v][i] = adjMatrix[i][vertices - 1];
    }
    adjMatrix[v][v] = 0; //we don't want self loops
    vertices--;
}

int Graph::contractAlgorithm() {
    //Keep trace of the subsets
    // set<int> subset1, subset2;
    // for (int i = 0; i < vertices; i++) {
    //     subset1.insert(i);
    // }
    //Contract the graph until only two vertices remain
    while (vertices > 2) {
        int u = rand() % vertices;
        int v = rand() % vertices;
        while (adjMatrix[u][v] == 0) { //Can be a bottleneck TODO: verify this
            u = rand() % vertices;
            v = rand() % vertices;
        }
        contract(u, v);

        // Update subsets
        // if (subset1.find(u) != subset1.end() && subset1.find(v) != subset1.end()) {
        //     subset1.erase(v);
        // } else if (subset1.find(u) != subset1.end() && subset1.find(v) == subset1.end()) {
        //     subset1.erase(u);
        //     subset2.insert(u);
        // } else if (subset1.find(u) == subset1.end() && subset1.find(v) != subset1.end()) {
        //     subset1.erase(v);
        //     subset2.insert(v);
        // }
    }

    // Calculate the value of the mincut to return
    int mincut = 0;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            mincut += adjMatrix[i][j];
        }
    }
    return mincut/2;
}

int Graph::fastCut() { //Maybe write this function outside the class
    int n = vertices;
    //TODO:
    while (n > 6) { // until 6 vertices left
        int t = ceil(1+ n/sqrt(2));
        int u = rand() % vertices;
        int v = rand() % vertices;
        while (adjMatrix[u][v] == 0) { //Can be a bottleneck TODO: verify this
            u = rand() % vertices;
            v = rand() % vertices;
        }
        contract(u, v);
    }
    // compute mincut by brute force
    int minCut = INT32_MAX;
    int subsetSize = 1 << n; //Shift bits to the left to know the number of subsets
    for (int i = 1; i < subsetSize - 1; ++i) { //Iterate over all subsets i
        int cutSize = 0;
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                if (((i & (1 << u)) != 0) != ((i & (1 << v)) != 0)) {
                    cutSize += adjMatrix[u][v];
                }
            }
        }
        minCut = min(minCut, cutSize);
    }
    return 0;
}

void Graph::printGraph(){
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
