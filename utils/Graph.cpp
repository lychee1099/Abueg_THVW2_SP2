#include "Graph.h"

#include <iostream>

Graph::Graph()
{
}

Graph::Graph(vector<vector<pair<int, int>>> adj_list_list, bool isDirected)
{
    // get all vector pair
    int k = 0;
    while (k < adj_list_list.size()) {
        addVertex(k + 1);
        k++;
    }

    for (int i = 0; i < adj_list_list.size(); i++) {
        // ith vector pair is adj list of ith vertex
        vector<pair<int, int>>& current_vec_pair = adj_list_list[i];
        for (int j = 0; j < current_vec_pair.size(); j++) {
            // now we have each pair
            connectVertices(i + 1, current_vec_pair[j].first, current_vec_pair[j].second, isDirected);
        }
    }

    _adj_list_list = adj_list_list;
}

void Graph::addVertex(int name)
{
    Vertex v;
    v.name = name;

    vertices.push_back(v);
}

void Graph::connectVertices(int src, int dest, int weight, bool isDirected)
{
    // check if src and dest exists
    int src_index = -1;
    int dest_index = -1;
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].name == src) {
            src_index = i;
        } else if (vertices[i].name == dest) {
            dest_index = i;
        }
    }

    if (src_index == -1 || dest_index == -1) {
        // either src or dest does not exist so do nothing
        return;
    }

    vertices[src_index].adjacency_vec.push_back({dest, weight});
    
    // if undirected
    if (!isDirected) {
        vertices[dest_index].adjacency_vec.push_back({src, weight});    
    }
}

void Graph::printAdjList()
{
    cout << "Source |" << " Dest" << endl; 
    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i].name << " -> ";
        
        for (int j = 0; j < vertices[i].adjacency_vec.size(); j++) {
            cout << "{" << vertices[i].adjacency_vec[j].first << ", " 
            <<  vertices[i].adjacency_vec[j].second << "} ";
        }
        cout << endl;
    }
}

void Graph::printAdjMatrix()
{
    cout << "Source (rows) & Dest (cols)" << endl; 

    cout << "  | ";
    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i].name << " | ";
    }
    cout << endl;

    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i].name << " | ";
        
        for (int j = 0; j < vertices.size(); j++) {
            bool inAdj = false;

            for (int k = 0; k < vertices[i].adjacency_vec.size(); k++) {
                if (vertices[j].name == vertices[i].adjacency_vec[k].first) {
                    inAdj = true;
                    cout << vertices[i].adjacency_vec[k].second << " | ";
                    break;
                }
            }

            if (!inAdj) {
                cout << "* | ";
            }
        }

        cout << endl;
    }
    
}

void createGraph(Graph &g, bool isDirected)
{
    vector<vector<pair<int, int>>> adj_list_list;

    int n_vertices;
    cout << "Enter number of vertices: ";
    cin >> n_vertices;

    cin.ignore();

    adj_list_list.resize(n_vertices);

    cout << "!! Kindly use the form (neighbor, weight) [with parenthesis] !!" << endl;
    cout << "!! e.g. (2, 10)(3, 5) or (2,10)(3,5) or (2,10)   (3,   5)   [spaces do not matter] !!" << endl;
    cout << "!! Enter a newline if the vertex is not connected to other vertices !!" << endl;
    cout << "!! Moreover, make sure that any of the neighbors are within [1, n_vertices]. TY!" << endl << endl;

    for (int i = 0; i < n_vertices; i++) {
        string input = "";
        vector<pair<int, int>> temp;

        cout << "Enter neighbor and weight for node " << i + 1 << ": ";

        getline(cin, input);

        // process input
        // no error handling!
        while (input != "") {
            int indx_left_par = input.find("(");
            int indx_right_par = input.find(")");

            if (indx_left_par == -1 && indx_right_par == -1) {
                break;
            }

            int n = indx_right_par - indx_left_par;

            string neighbor_weight = input.substr(indx_left_par + 1, n - 1);

            int indx_comma = neighbor_weight.find(",");

            int neighbor = stoi(neighbor_weight.substr(0, indx_comma));
            int weight = stoi(neighbor_weight.substr(indx_comma + 1));

            // remove substr from orig input
            input.erase(indx_left_par, n + 1);

            temp.push_back({neighbor, weight});
        }

        adj_list_list[i] = temp;
    }
    
    g = Graph(adj_list_list, isDirected);
}