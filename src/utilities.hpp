#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Read the adjacency matrix from a file with the following format:
 * mincut: <mincut_value> \n
 * subsetCut1: <vertex1> <vertex2> ... <vertexN> \n
 * subsetCut2: <vertex1> <vertex2> ... <vertexN> \n
 * <adjacency_matrix>
 * @param graph The graph to populate
 * @param filename The filename
 */
void readAdjMatrix(Graph& graph, const string& filename);

#endif