#include "utilities.hpp"
#include "Graph.hpp"
#include <iostream>

using namespace std;

int main() {
    string filename = "graph_data/random_graph_adjmatrix.txt";
    Graph* graph = new Graph(15);
    readAdjMatrix(*graph, filename);
    graph->printGraph();

    delete graph;
    return 0;
}