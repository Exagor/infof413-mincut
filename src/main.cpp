#include "Graph.hpp"
#include "utilities.hpp"
#include "algorithm.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

void experimentsAlgoMinCut(int vertices, string filename, int iterations=50) {
    for (int i = 0; i < iterations; i++) {
        vector<int> results;
        vector<double> times;
        Graph* graph = new Graph(vertices);
        readAdjMatrix(*graph, filename);
        // graph -> printGraph();
        int mincut = graph -> getMinCut();

        //measure time
        auto start = high_resolution_clock::now();
        int mincut_contract = contractAlgorithm(*graph);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        double time_taken = duration.count()/1000.0; //in milliseconds (micro to milli)
        times.push_back(time_taken);

        // reinitialize the graph to test the second algorithm
        Graph* graph2 = new Graph(vertices);
        readAdjMatrix(*graph2, filename);
        auto start2 = high_resolution_clock::now();
        int mincut_fast = fastCut(*graph2);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(stop2 - start2);
        double time_taken2 = duration2.count()/1000.0; //in milliseconds
        times.push_back(time_taken2);

        results.push_back(mincut);
        results.push_back(mincut_contract);
        results.push_back(mincut_fast);

        writeResults(filename, vertices, results, times);
        delete graph;
        delete graph2;
    }
    cout << "Experiments on " << filename << " finished" << endl;
}

int main(int argc, char* argv[]) {
    srand(42); //set the seed for the random number generator
    vector<string> filenames = {"random_graph_","random_weighted_graph_", "barbell_graph_","complete_graph_","turan_graph_"};
    vector<int> verticesVector = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    // vector<string> filenames = {"random_graph_"};
    // vector<int> verticesVector = {10, 20, 30, 40, 50};
    // Loop to experiment with all the files of all sizes
    for (string filenameOG: filenames){
        for (int vertices: verticesVector){
            // create the right filename
            string filename = "graph_data/" + filenameOG + to_string(vertices) + "_matrix.txt";
            experimentsAlgoMinCut(vertices, filename, 50);
        }
    }
    return 0;
}