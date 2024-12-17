#include "utilities.hpp"

void readAdjMatrix(Graph& graph, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
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

void writeResults(const string& filename, int size, const vector<int>& results, const vector<double>& times) {
    ofstream file;
    // Extract family from filename
    regex re("\\D+");
    smatch match;
    string family;
    if (regex_search(filename, match, re)) {
        family = match.str(0);
    }
    // Remove everything before the last "/"
    size_t pos = family.find_last_of('/');
    if (pos != string::npos) {
        family = family.substr(pos + 1);
    }
    // Remove the last character of family string
    if (!family.empty()) {
        family.pop_back();
    }
    file.open("results/" + family + ".csv", ios::app); // Open file in append mode

    if (file.is_open()) {
        // Write the CSV row
        file << family << ","
             << size << ","
             << results[0] << ","
             << results[1] << ","
             << results[2] << ","
             << times[0] << ","
             << times[1] << ","
             << (results[0] == results[1] ? 1 : 0) << ","
             << (results[0] == results[2] ? 1 : 0) << "\n";

        file.close();
    } else {
        cerr << "Unable to open file: " << "results/" + family + ".csv" << endl;
    }
}