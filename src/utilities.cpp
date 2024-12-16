#include "utilities.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> readAdjlist(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return {};
    }

    string line;
    vector<vector<int>> adjMatrix;
    int nodeCount = 0;

    // First pass to determine the number of nodes
    while (getline(file, line)) {
        if (line[0] == '#') continue; // Skip comments
        nodeCount++;
    }

    // Initialize adjacency matrix
    adjMatrix.resize(nodeCount, vector<int>(nodeCount, 0));

    // Reset file stream to beginning
    file.clear();
    file.seekg(0, ios::beg);

    // Second pass to fill the adjacency matrix
    int node = 0;
    while (getline(file, line)) {
        if (line[0] == '#') continue; // Skip comments
        istringstream iss(line);
        int neighbor;
        while (iss >> neighbor) {
            adjMatrix[node][neighbor] = 1;
            adjMatrix[neighbor][node] = 1; // Assuming undirected graph
        }
        node++;
    }

    file.close();
    return adjMatrix;
}