#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

using namespace std;

class Graph {
public:
    Graph(int vertices); //Creates empty graph with vertices
    void addEdge(int v, int w);
    void addEdge(int v, int w, int weight);
    void printGraph();

private:
    int vertices;
    vector<vector<int>> adjMatrix;
};

#endif //GRAPH_HPP