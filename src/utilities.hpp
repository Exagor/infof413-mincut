#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

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

/**
 * @brief Write the results of the experiments to a file
 * @param filename The filename
 * @param results The results of the experiments
 * @param time The time taken for each experiment
 */
void writeResults1(const string& filename, int size, const vector<int>& results, const vector<double>& times);

/**
 * @brief Write the results of the experiments to a file (but for different experiments)
 * @param filename The filename
 * @param size The size of the graph
 * @param algoName The name of the algorithm
 * @param mincut The mincut value
 * @param results The results of the experiments
 * @param time The time taken for each experiment
 * 
 */
void writeResults2(const string& filename, int size, const string& algoName, int mincut, const vector<int>& results, double time);
#endif