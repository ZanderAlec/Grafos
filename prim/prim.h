#include <iostream>
#include <fstream>
#include <unistd.h>
#include <bits/stdc++.h>
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

    int custo_total(vector<int> custos){
        int total = 0;
        for(int i=1; i<custos.size(); i++) {
            total += custos[i];
        }
        return total;
    }
    
    pair <vector<int>, int> Prim(Grafo grafo, int inicial) {
        vector<node*> arestas = grafo.adj; 
        vector<int> custos;
        vector<int> prev;
        vector<bool> visitados;

        for(int i=0; i <= grafo.vertices; i++){
            custos.push_back(INT_MAX);
            prev.push_back(-1);  
            visitados.push_back(false);
        }

        priority_queue<pair<int,int>, vector <pair<int,int>>, greater<pair<int,int>>> min_heap;

        custos[inicial] = 0;
        min_heap.push(make_pair(custos[inicial], inicial));

        while(min_heap.size() > 0) {
            int u = min_heap.top().second; 
            min_heap.pop();
            visitados[u] = true;  
            node *current = arestas[u];
            while(current != NULL) {
                int peso = current->peso;
                int destino = current->destino;

                if(!visitados[destino] && custos[destino] > peso){
                    custos[destino] = peso;
                    prev[destino] = u; 
                    min_heap.push(make_pair(custos[destino], destino));
                }
                current = current->next;
            }
        }
        
        return make_pair(prev, custo_total(custos));
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