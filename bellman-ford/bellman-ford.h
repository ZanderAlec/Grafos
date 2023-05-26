#include <iostream>
#include <fstream>
#include <unistd.h>

#include <bits/stdc++.h> 
using namespace std;

typedef struct Node node;

struct Node{
    int destino;
    int peso;
    node* next;
};

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

    vector<int> BF(Grafo grafo, int inicial) {
        int v = grafo.vertices;
        vector<node*> arestas = grafo.adj;
        vector<int> distancias;

        for (int i = 0; i <= v; i++) {
            distancias.push_back(INT_MAX);
        }

        distancias[inicial] = 0;

        for (int i = 1; i < v; i++) {
            for (int j = 1; j <= v; j++) {
                node* vizinhos = arestas[j];
                while(vizinhos != NULL) {
                    if (distancias[j] + vizinhos->peso < distancias[vizinhos->destino] && distancias[j] != INT_MAX) {
                        distancias[vizinhos->destino] = distancias[j] + vizinhos->peso;
                    }
                    vizinhos = vizinhos->next;
                }
            }
        }

        for (int j = 0; j <= v; j++) {
            node* vizinhos = arestas[j];
            while(vizinhos != NULL) {
                if (distancias[j] + vizinhos->peso < distancias[vizinhos->destino] && distancias[j] != INT_MAX) {
                    distancias[inicial] = INT_MAX;
                    return distancias;
                }
                vizinhos = vizinhos->next;
            }
        }

        return distancias;
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
        }
        input_file.close();
        return grafo;
    }
    else {
        cout << "Não foi possível abrir o arquivo de entrada" << endl;
    }
    return 0;
}