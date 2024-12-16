#include "utilities.hpp"
#include "Graph.hpp"
#include <iostream>

using namespace std;

int main() {
    string filename = "graph_data/random_graph_matrix.txt";
    Graph* graph = new Graph(15);
    readAdjMatrix(*graph, filename);
    graph->printGraph();

    int mincut = graph->getMinCut();
    cout << "Min cut = "<< mincut << endl;
    
    set<int>subsetCut1 = graph->getSubsetCut1();
    set<int>subsetCut2 = graph->getSubsetCut2();
    cout << "Subset cut 1: ";
    for (auto vertex : subsetCut1) {
        cout << vertex << " ";
    }
    cout << endl;
    cout << "Subset cut 2: ";
    for (auto vertex : subsetCut2) {
        cout << vertex << " ";
    }
    cout << endl;

    delete graph;
    return 0;
}