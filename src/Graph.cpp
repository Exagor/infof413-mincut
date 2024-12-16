#include "Graph.hpp"
#include <iostream>
#include <vector>

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

void Graph::setMinCut(int mincut) {
    this->mincut = mincut;
}

int Graph::getMinCut() {
    return mincut;
}

void Graph::setSubsetCut(set<int> subsetCut1, set<int> subsetCut2) {
    this->subsetCut1 = subsetCut1;
    this->subsetCut2 = subsetCut2;
}

set<int> Graph::getSubsetCut1() {
    return subsetCut1;
}

set<int> Graph::getSubsetCut2() {
    return subsetCut2;
}

void Graph::printGraph(){
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
