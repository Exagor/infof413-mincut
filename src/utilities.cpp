#include "utilities.hpp"
#include "Graph.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

void readAdjMatrix(Graph& graph, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
    }

    string line;
    int row = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        int col = 0;
        int value;
        while (iss >> value) {
            if (value == 1) {
                graph.addEdge(row, col);
            } else if(value > 1) {
                graph.addEdge(row, col, value);
            }
            col++;
        }
        row++;
    }

    file.close();
};