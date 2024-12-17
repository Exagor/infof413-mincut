#include "Graph.hpp"
#include "utilities.hpp"
#include "algorithm.hpp"

using namespace std;

int main() {
    srand(42); //set the seed for the random number generator
    vector<int> verticesVector = {10,20,30,40,50,60,70,80,90,100};
    int vertices = 20;
    ostringstream filenameStream;
    filenameStream << "graph_data/random_graph_" << vertices << "_matrix.txt";
    string filename = filenameStream.str();

    for (int i = 0; i < 15; i++) {
        Graph* graph = new Graph(vertices);
        readAdjMatrix(*graph, filename);
        // graph -> printGraph();
        int mincut = graph -> getMinCut();
        cout << "Min cut = "<< mincut << endl;
        int mincut_contract = contractAlgorithm(*graph);
        cout << "Min cut contract = "<< mincut_contract << endl;
        delete graph;
        Graph* graph2 = new Graph(vertices);
        readAdjMatrix(*graph2, filename);
        int mincut_fast = fastCut(*graph2);
        cout << "Min cut fast = "<< mincut_fast << endl;
    }

    return 0;
}