#include <bits/stdc++.h>
#include "dijkstra.h"

using namespace std;

int main(int argc, char* argv[]) {
    int inicial;
    bool o = false, f = false, in = false;
    char *input_name, *output_name;

    for (int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "-h")) {
            printf("O algoritmo de Dijkstra encontra o menor caminho entre dois vértices de um grafo.\n\n");
            printf("-o <arquivo>: redireciona a saida para o ‘‘arquivo’’\n");
            printf("-f <arquivo>: indica o ‘‘arquivo’’ que contém o grafo de entrada\n");
            printf("-i: vértice inicial\n");
            return 0;
        } 
        if(!strcmp(argv[i], "-o")) {
            o = true;
            output_name = argv[i+1];
        }
        if(!strcmp(argv[i], "-f")) {
            f = true;
            input_name = argv[i+1];
        }
        if(!strcmp(argv[i], "-i")) {
            in = true;
            inicial = stoi(argv[i+1]);
        }
    }

    vector<int> distancias;

    if (f || in) {
        if (f) {
            Grafo grafo = read_graph_file(input_name);
            if (in) {
                distancias = grafo.Dijkstra(grafo, inicial);
            } else {
                distancias = grafo.Dijkstra(grafo, 1);
            }
        } else {
            Grafo grafo = read_graph_file("grafo.in");
            distancias = grafo.Dijkstra(grafo, inicial);
        }
    } else {
        Grafo grafo = read_graph_file("grafo.in");
        distancias = grafo.Dijkstra(grafo, 1);
    }

    if (o) {
        ofstream output_file;
        output_file.open(output_name);
        for (int i = 1; i < distancias.size(); i++) {
            output_file << i << ":" << ((distancias[i] == INT_MAX) ? -1 : distancias[i]) << " ";
        }
        output_file.close();
    } else {
        for (int i = 1; i < distancias.size(); i++) {
            printf("%d:%d ", i, (distancias[i] == INT_MAX) ? -1 : distancias[i]);
        }
        printf("\n");
    } 
    return 0;
}