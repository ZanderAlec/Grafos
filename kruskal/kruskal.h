#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

typedef struct edge Edge;
typedef struct Node node;

struct edge {
    int src;
    int destino;
    int peso;
};


struct Node{
    int destino;
    int peso;
    node* next;
};

void Union(int x, int y, int parent[], int rank[]) {
    if (rank[x] >= rank[y]) {
        parent[y] = x;
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
        return;
    }
    parent[x] = y;
}

int Find(int x, int parent[], int rank[]) {
    if (parent[x] != x) {
        parent[x] = Find(parent[x], parent, rank);
    }
    return parent[x];
}

bool compareEdges(Edge a, Edge b) {
    return (a.peso < b.peso);
}

vector<Edge> make_edges(vector<node*> g) {
    vector<Edge> edges;
    for (int i = 0; i < g.size(); i++) {
        node* current = g[i];
        while (current != NULL) {
            Edge new_edge;
            new_edge.src = i;
            new_edge.destino = current->destino;
            new_edge.peso = current->peso;
            edges.push_back(new_edge);
            current = current->next;
        }
    }
    return edges;
}

int peso_total(vector<Edge> MST) {
    int total = 0;
    for (int i = 0; i < MST.size(); i++) {
        total += MST[i].peso;
    }
    return total;
}

class Grafo {
    int vertices;
    vector <node*> adj;
public:
    Grafo(int vertices) {
        this->vertices = vertices;
        for (int i = 0; i <= vertices; i++) {
            this->adj.push_back(NULL);
        }
    }

    void adcAresta(int vertc1, int vertc2, int peso) {
        node* edge = (node*) malloc(sizeof(node));
        edge->destino = vertc2;
        edge->peso = peso;
        edge->next = adj[vertc1];
        adj[vertc1] = edge;
    }

    vector<Edge> Kruskal(Grafo grafo) {
        vector<Edge> MST;
        vector<Edge> sorted_edges = make_edges(grafo.adj);
        sort(sorted_edges.begin(), sorted_edges.end(), compareEdges);
        int rank[grafo.vertices], parent[grafo.vertices];
        for (int i = 0; i <= grafo.vertices; i++){
            parent[i] = i;
            rank[grafo.vertices] = grafo.vertices;
        }

        for (int i = 0; i < sorted_edges.size(); i++) {
            int u = sorted_edges[i].src;
            int v = sorted_edges[i].destino;
            int c1 = Find(u, parent, rank);
            int c2 = Find(v, parent, rank);

            if (c1 != c2) {
                MST.push_back(sorted_edges[i]);
                Union(c1, c2, parent, rank);
            }
        }

        return MST;
        
    }
};

void split(string line, int* source, int* dest, int* weight) {
    string delimiter = " "; 
    size_t pos = 0;
    string token;
    vector <int> values;
    line = line + " ";
    while ((pos = line.find(delimiter)) != string::npos) {
        token = line.substr(0, pos);
        values.push_back(stoi(token));
        line.erase(0, pos + delimiter.length());
    }

    *source = values[0];
    *dest = values[1];
    
    (values.size() == 2) ? *weight = 1 : *weight = values[2];
}

Grafo read_graph_file(const char* file){

    ifstream input_file(file);
    if (input_file.is_open()){
        string line;
        getline(input_file, line);
        int edges, vertexes, temp;
        split(line, &vertexes, &edges, &temp);
        Grafo grafo(vertexes);
        while (getline(input_file,line)) {
            int source, dest, weight;
            split(line, &source, &dest, &weight);
            grafo.adcAresta(source, dest, weight);
            grafo.adcAresta(dest, source, weight);
        }
        input_file.close();
        return grafo;
    }
    else {
        cout << "Não foi possível abrir o arquivo de entrada" << endl;
    }
    return 0;
}