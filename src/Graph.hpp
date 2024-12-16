#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * @class Graph
 * @brief Graph class
 */
class Graph {
public:
    Graph(int vertices); //Creates empty graph with vertices
    /*
    * @brief Add an edge to the graph
    * @param v The first vertex
    * @param w The second vertex
    */
    void addEdge(int v, int w);
    /*
    * @brief Add an edge to the graph with weight
    * @param v The first vertex
    * @param w The second vertex
    * @param weight The weight of the edge
    */ 
    void addEdge(int v, int w, int weight);
    int getVertices() const;
    void setMinCut(int mincut);
    int getMinCut() const;
    void setSubsetCut(set<int> subsetCut1, set<int> subsetCut2);
    set<int> getSubsetCut1() const;
    set<int> getSubsetCut2()const;
    /*
    * @brief Contract two vertices
    * @param u The first vertex
    * @param v The second vertex
    */
    void contract(int u, int v);
    /*
    * @brief Contract the graph until only two vertices remain (simple kargers algorithm)
    * @return The minimum cut value
    */
    int contractAlgorithm();
    /*
    * @brief Implementation of the fast cut algorithm
    * @return The minimum cut value
    */
    int fastCut();
    /*
    * @brief Print the graph in the standard output in adjacency matrix form
    */
    void printGraph();

private:
    int vertices;
    int mincut;
    set<int> subsetCut1;
    set<int> subsetCut2;
    vector<vector<int>> adjMatrix;
};

#endif //GRAPH_HPP