#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <set>

using namespace std;

class Graph {
public:
    Graph(int vertices); //Creates empty graph with vertices
    void addEdge(int v, int w);
    void addEdge(int v, int w, int weight);
    void setMinCut(int mincut);
    int getMinCut();
    void setSubsetCut(set<int> subsetCut1, set<int> subsetCut2);
    set<int> getSubsetCut1();
    set<int> getSubsetCut2();
    void contraction(int u, int v);
    void fastCut();
    void printGraph();

private:
    int vertices;
    int mincut;
    set<int> subsetCut1;
    set<int> subsetCut2;
    vector<vector<int>> adjMatrix;
};

#endif //GRAPH_HPP