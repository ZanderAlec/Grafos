#include <bits/stdc++.h>
#include "prim.h"

using namespace std;

int main(int argc, char* argv[]) {
    int inicial = 1;
    bool o = false, f = false, in = false, sol = false;
    char *input_name, *output_name;

    for (int i = 0; i < argc; i++) {
        if(!strcmp(argv[i], "-h")) {
            printf("O algoritmo de Prim encontra a Árvore geradora mínima do grafo.\n\n");
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

    pair <vector<int>, int> res;

    if (f) {
        Grafo grafo = read_graph_file(input_name);
        res = grafo.Prim(grafo, inicial);
    } else {
        Grafo grafo = read_graph_file("grafo.in");
        res = grafo.Prim(grafo, inicial);
    }


    if (o) {
        ofstream output_file;
        output_file.open(output_name);
        if (sol) {
            for (int i = 0; i < res.first.size(); i++) {  
                if (res.first[i] == -1) continue;
                output_file << "(" << res.first[i] << "," << i << ") ";
            }
            output_file << endl;
        } else {
            output_file << res.second << endl;
        }
        output_file.close();
    } else {
        if (sol) {
            for (int i = 0; i < res.first.size(); i++) {  
                if (res.first[i] == -1) continue;
                printf("(%d,%d) ", res.first[i], i);
            }
            printf("\n");
        } else {
            printf("%d\n", res.second);
        }
    }
    return 0;
}