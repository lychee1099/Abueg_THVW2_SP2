#include <iostream>
#include <algorithm>

#include "utils/Graph.h"
#include "kruskal.h"

using namespace std;

// Kruskal's Algorithm
// sort edge list in increasing order
// pick edge until V-1 edges
// make sure not to make cyclic

struct Edge {
    int weight;
    int src;
    int dest;
};

bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
};

// VERY VERY VERY ROUGH IMPLEMENTATION OF UNION AND FIND hehehhe

void Union(vector<pair<Vertex, int>>& vertex_and_root, int src, int dest) {
    if (vertex_and_root[src - 1].second <= vertex_and_root[dest - 1].second) {
        vertex_and_root[dest - 1].second = vertex_and_root[src - 1].second;
    } else {
        vertex_and_root[src - 1].second = vertex_and_root[dest - 1].second;
    }
}

// return root node
int Find(vector<pair<Vertex, int>>& vertex_and_root, int vertex) {
    return vertex_and_root[vertex - 1].second;
}

//-----

vector<Edge> doKruskal(vector<Edge> edge_list, vector<Vertex> vertices) {
    // sort edge_list
    sort(edge_list.begin(), edge_list.end(), compareEdges);
    vector<Edge> edge_in_MST;

    // each vertex is its own root node first
    vector<pair<Vertex, int>> vertex_and_root;
    int n_vertices = vertices.size();
    vertex_and_root.resize(n_vertices);

    for (int i = 0; i < n_vertices; i++) {
        vertex_and_root[i].first = vertices[i];
        vertex_and_root[i].second = vertices[i].name;
    }

    // loop until we have v-1 edges
    int have_edges = 0;
    for (int i = 0; i < edge_list.size() && have_edges < n_vertices - 1; i++) {
        // different root node then it is valid
        if (Find(vertex_and_root, edge_list[i].src) != Find(vertex_and_root, edge_list[i].dest)) {
            // we can do union
            Union(vertex_and_root, edge_list[i].src, edge_list[i].dest);
            edge_in_MST.push_back(edge_list[i]);

            have_edges++;
        }
    }

    
    return edge_in_MST;
}  

void doKruskalAlgo() {
    Graph graph;
    // handles input
    createGraph(graph, true);

    cout << endl << "Printing Adjacency list" << endl;
    graph.printAdjList();
    cout << endl;

    // get edge list
    vector<vector<pair<int, int>>> adj_list_list = graph.getAdjListList();
    vector<Vertex> vertices = graph.getVertices();

    vector<Edge> edge_list;

    for (int vert = 0; vert < adj_list_list.size(); vert++) {
        int n_edges = adj_list_list[vert].size();
        for (int edge = 0; edge < n_edges; edge++) {
            Edge edge_;
            edge_.dest = adj_list_list[vert][edge].first;
            edge_.weight = adj_list_list[vert][edge].second;
            edge_.src = vert + 1;

            edge_list.push_back(edge_);
        }
    }

    vector<Edge> MST_edges = doKruskal(edge_list, vertices);
    int weight = 0;

    cout << "Edges included (weight, src, dest): ";
    for (int i = 0; i < MST_edges.size(); i++) {
        weight += MST_edges[i].weight;
        cout << "(" << MST_edges[i].weight << ", " << MST_edges[i].src
        << ", " << MST_edges[i].dest << ") ";
    }

    cout << endl << "Total weight of MST: " << weight << endl;
}