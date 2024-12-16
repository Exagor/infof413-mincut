#include "utilities.hpp"
#include "Graph.hpp"
#include <iostream>
#include <sstream>

using namespace std;

int main() {
    srand(42); //set the seed for the random number generator
    int vertices = 10;
    ostringstream filenameStream;
    filenameStream << "graph_data/random_graph_" << vertices << "_matrix.txt";
    string filename = filenameStream.str();
    for (int i = 0; i < 15; i++) {
        Graph* graph = new Graph(vertices);
        readAdjMatrix(*graph, filename);
        // graph -> printGraph();

        int mincut = graph -> getMinCut();
        cout << "Min cut = "<< mincut << endl;
        int mincut_contract = graph -> contractAlgorithm();
        cout << "Min cut contract = "<< mincut_contract << endl;
        delete graph;
    }

    return 0;
}