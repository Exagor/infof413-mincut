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

void Graph::printGraph() const{
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
