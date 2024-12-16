#include "utilities.hpp"
#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <set>

using namespace std;

void readAdjMatrix(Graph& graph, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    // Read metadata
    int mincut = 0;
    set<int> subsetCut1, subsetCut2;

    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line.find("mincut:") == 0) {
            mincut = stoi(line.substr(7)); // Get the mincut value
        } else if (line.find("subsetCut1:") == 0) {
            istringstream iss(line.substr(11));
            int vertex;
            while (iss >> vertex) {
                subsetCut1.insert(vertex);
            }
        } else if (line.find("subsetCut2:") == 0) {
            istringstream iss(line.substr(11));
            int vertex;
            while (iss >> vertex) {
                subsetCut2.insert(vertex);
            }
        } else {
            break; // End of metadata
        }
    }

    // Set metadata in the graph
    graph.setMinCut(mincut);
    graph.setSubsetCut(subsetCut1,subsetCut2);

    // Read the adjacency matrix
    int row = 0;
    do {
        istringstream iss(line);
        int col = 0;
        int value;
        while (iss >> value) {
            if (value == 1) {
                graph.addEdge(row, col);
            } else if (value > 1) {
                graph.addEdge(row, col, value);
            }
            col++;
        }
        row++;
    } while (getline(file, line));

    file.close();
}