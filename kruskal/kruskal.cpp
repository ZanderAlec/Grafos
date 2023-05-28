#include <bits/stdc++.h>
#include "kruskal.h"

using namespace std;

int main(int argc, char* argv[]) {
    int inicial = 1;
    bool o = false, f = false, in = false, sol = false;
    char *input_name, *output_name;

    for (int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "-h")) {
            printf("O algoritmo de Kruskal encontra a Árvore geradora mínima do grafo.\n\n");
            printf("-o <arquivo>: redireciona a saida para o ‘‘arquivo’’\n");
            printf("-f <arquivo>: indica o ‘‘arquivo’’ que contém o grafo de entrada\n");
            printf("-i: vértice inicial\n");
            printf("-s: mostra a solução\n");
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
            inicial = atoi(argv[i+1]);
        }
        if(!strcmp(argv[i], "-s")) {
            sol = true;
        }
    }

    vector<Edge> MST;

    if (f) {
        Grafo grafo = read_graph_file(input_name);
        MST = grafo.Kruskal(grafo);
    } else {
        Grafo grafo = read_graph_file("grafo.in");
        MST = grafo.Kruskal(grafo);
    }


    if (o) {
        ofstream output_file;
        output_file.open(output_name);
        if (sol) {
            for (int i = 0; i < MST.size(); i++) {  
                output_file << "(" << MST[i].src << "," << MST[i].destino << ") ";
            }
            output_file << endl;
        } else {
            output_file << peso_total(MST) << endl;
        }
        output_file.close();
    } else {
        if (sol) {
            for (int i = 0; i < MST.size(); i++) {  
                cout << "(" << MST[i].src << "," << MST[i].destino << ") ";
            }
            cout << endl;
        } else {
            cout << peso_total(MST) << endl;
        }
    }
    return 0;
}