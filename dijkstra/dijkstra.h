#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

typedef pair<int, int> Pair;
typedef struct Node node;

struct Node{
    int destino;
    int peso;
    node* next;
};


class Grafo {
    int vertices;
    vector <node*> adjlist;
public:
    Grafo(int vertices) {
        this->vertices = vertices;
        for (int i = 0; i <= vertices; i++) {
            this->adjlist.push_back(NULL);
        }
    }

    void adcAresta(int v1, int v2, int peso) {
        node* edge = (node*) malloc(sizeof(node));
        edge->destino = v2;
        edge->peso = peso;
        edge->next = adjlist[v1];
        adjlist[v1] = edge;
    }

    vector<int> Dijkstra(Grafo grafo, int inicial) {
        vector<node*> arestas = grafo.adjlist; 
        vector<int> vizinhos;
        vector<int> distancias;

        for (int i=0; i <= grafo.vertices; i++) {
            distancias.push_back(INT_MAX);
            vizinhos.push_back(-1);
        }

        priority_queue<pair<int,int>, vector <pair<int,int>>, greater<pair<int,int>>> min_heap;

        distancias[inicial] = 0;
        min_heap.push(make_pair(distancias[inicial], inicial));

        while(min_heap.size() > 0) {
            int u = min_heap.top().second;
            min_heap.pop();
            node *current = arestas[u];
            while(current != NULL) {
                if(distancias[current->destino] > distancias[u] + current->peso) {
                    distancias[current->destino] = distancias[u] + current->peso;
                    vizinhos[current->destino] = u;
                    min_heap.push(make_pair(distancias[current->destino], current->destino));
                }
                current = current->next;
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