#include <stdlib.h>
#include <stdio.h>
#include "grafos.h"

//Preenche todos os indices de um vetor com 0.
void zeraVetor(int v[], int tam){

    for(int i = 0; i<tam; i++){
        v[i] = 0;
    }
}

//Procura um valor dentro de um vetor
int buscaValorVetor(int v[], int tam, int valor){

    for(int i = 0; i<tam; i++){
        if(v[i] == valor){
            return 1;
        }
    }

    return 0;
}

//Essa função procura um caminho entre dois vértices. Retorna 1(Se existir) ou 0(Se não existir)
//v0 = vertice inicial, vi = objetivo, percorridos = vetor com tamanho igual número de vertices no grafo.
int existeCaminho(GRAFO * g, int v0, int vi, int percorridos[]){
        
         //Verifica se o valor passado é igual ao buscado
        if(v0 == vi){
            return 1;
        }

        //Caso não seja, adiciona o vetor atual nos percorridos.
        percorridos[v0-1] = v0;

        //Busca o indice que o vertice(v0) está no gráfico.
        int indice = buscaVertice(v0, g);

        if(indice != -1){
            lista_adjacencias * l = g->lista_vertices[indice].primeiro;

            //Percorre todos os filhos de v0.
            while(l != NULL){
                
                //Garante que só visite vertices não visitados
                if(!buscaValorVetor(percorridos, g->num_verts, l->valor)){
                    int retorno = existeCaminho(g, l->valor, vi, percorridos);

                    //Ser retorno =1 acabou a função. (Valor encontrado)
                    if(retorno){
                        return retorno;
                    }
                }

                l = l->proximo;

            }
        }

    //Se não tem mais filhos retorna 0.
    return 0;
}

//Encontra a árvore geradora mínima(agm), a partir de um grafo direcionado e conexo
//Utilizada o algorítmo de kruskal.
GRAFO * encontraAgmKruskal(GRAFO * g, GRAFO * agm){

    //Roda até não ter mais vertices não adicionados à agm
    while(1){
        //aresta
        int v1 = 0 , v2 = 0;
        int menorPeso = 0;

        //Percorre todos as arestas do grafo procurando a com menor peso(que já não foi adicionada)
        for(int i = 0; i<g->num_verts; i++){
            lista_adjacencias * l = g->lista_vertices[i].primeiro;
            
            //Percorre todos os filhos do vertice atual
            while(l){

                if(menorPeso == 0){
                    menorPeso = l->peso;
                }

                if(menorPeso > l->peso || v1 == 0){
                    
                    int vtemp = g->lista_vertices[i].valor;
                    int vtemp2 = l->valor;
                    
                    //vetor usado na função existe caminho
                    int percorridos[6];
                    zeraVetor(percorridos, 6);

                    //Verifica se existe caminho entre os dois vértices
                    int resultado = existeCaminho(agm, vtemp, vtemp2, percorridos);

                    //Se não existir caminho, a aresta atual pode ser utilizada.
                    if(!resultado){
                        
                        v1 = vtemp;
                        v2 = vtemp2;
                        menorPeso = l->peso;
                    }
                }

                l = l->proximo;    
            }
        }

        //Não existem mais vértices que não foram visitados. Encerra.
        if(v1 == 0){
            break;
        }

        //Caso encontrou vertices não visitados adiciona eles à agm:
        adicionaVerticeAresta(v1,v2,menorPeso,agm);

    }

    return agm;
}

int main(){

    GRAFO * g = criaGrafo(6,8);

    adicionaVerticeAresta(1,2,5,g);
    adicionaVerticeAresta(1,3,4,g);
    adicionaVerticeAresta(1,4,2,g);
    adicionaVerticeAresta(1,6,6,g);
    adicionaVerticeAresta(2,4,1,g);
    adicionaVerticeAresta(2,5,7,g);
    adicionaVerticeAresta(3,5,6,g);
    adicionaVerticeAresta(4,6,1,g);

    imprimeGrafo(g);

    GRAFO * agm = criaGrafo(g->num_verts, g->num_arestas);

    agm = encontraAgmKruskal(g, agm);

    imprimeGrafo(agm);

    return 0;
}