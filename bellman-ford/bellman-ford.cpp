#include <bits/stdc++.h>
#include "bellman-ford.h"

using namespace std;

int main(int argc, char* argv[]) {
    int inicial = 1;
    bool o = false, f = false, in = false;
    char *input_name, *output_name;

    for (int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "-h")) {
            printf("O algoritmo de Bellman-Ford encontra o menor caminho entre dois vértices de um grafo, podendo haver pesos negativos.\n\n");
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
            inicial = atoi(argv[i+1]);
        }
    }
    
    vector<int> distancias;

    if (f) {
        Grafo grafo = read_graph_file(input_name);
        distancias = grafo.BF(grafo, inicial);
    } else {
        Grafo grafo = read_graph_file("grafo.in");
        distancias = grafo.BF(grafo, inicial);
    }

    if (o) {
        ofstream output_file;
        output_file.open(output_name);
        if (distancias[inicial] == INT_MAX) {
            output_file << "O grafo possui ciclo negativo!" << endl;
        } else {
            for (int i = 1; i < distancias.size(); i++) {
                output_file << i << ":" << ((distancias[i] == INT_MAX) ? -1 : distancias[i]) << " ";
            }
        }
        output_file.close();
    } else {
        if (distancias[inicial] == INT_MAX) {
            printf("O grafo possui ciclo negativo!\n");
        } else {
            for (int i = 1; i < distancias.size(); i++) {
                printf("%d:%d ", i, (distancias[i] == INT_MAX) ? -1 : distancias[i]);
            }
            printf("\n");
        }
    } 
    return 0;
}