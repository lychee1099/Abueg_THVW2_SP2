#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using namespace std;

struct Vertex {
    // 1st - dest, 2nd - weight
    vector<pair<int, int>> adjacency_vec;
    int name;
};

class Graph {
private:
    vector<Vertex> vertices;
    vector<vector<pair<int, int>>> _adj_list_list;

public:
    Graph();
    Graph(vector<vector<pair<int, int>>> adj_list_list, bool isDirected=true);

    void addVertex(int name);
    void connectVertices(int src, int dest, int weight=1, bool isDirected=true);

    void printAdjList();
    void printAdjMatrix();

    inline const vector<Vertex>& getVertices() {return vertices;}
    inline const vector<vector<pair<int, int>>>& getAdjListList() {return _adj_list_list;}
};

void createGraph(Graph& g, bool isDirected);

#endif