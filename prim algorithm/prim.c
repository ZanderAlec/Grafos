#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"


//Solicita os valores e preenche o grafo:
GRAFO * pedeValores(GRAFO * g){

    int vPai = 0, vFilho = 0, peso = 0;

    for(int i = 1; i <= g->num_arestas; i++){
        printf("Informe o valor do vertice pai, vertice filho e peso da arestas: ");
        scanf("%d %d %d", &vPai, &vFilho, &peso);

        g = adicionaVerticeAresta(vPai, vFilho, peso, g);

    }

    return g;
}

//Preenche todos os índices do vetor com "-1"
void limpaVetor(int vet[], int tam){
    for(int i = 0; i < tam; i++){
        vet[i] = -1;
    }
}

void insereValorVetor(int vet[], int tam, int valor){
    for(int i = 0; i < tam; i++){
        if(vet[i] == -1){
            vet[i] = valor;
            return;
        }
    }
}


//retorna 0 se não há não visitados na lista.
//Retorna 1 se há verticeis não visitados
//Preenche as variáveis menorPeso e verticeMenor
//visitado = 0 (ignora os visitados) | visitado = 1 (não ignora os já visitados)
int procuraMenorPeso(int vertsVisitados[], lista_adjacencias * lista, int *menorPeso, int *verticeMenor, int visitado){

    while(lista != NULL){
        int valor = lista->valor;

        //Verifica se o vertice ainda não foi visitado
        if(vertsVisitados[valor-1] == -1 && visitado == 1){
            
            //Guarda o menor valor 
            if(*menorPeso > lista->peso || *menorPeso == 0){                
                    *menorPeso = lista->peso;
                    *verticeMenor = valor;
            }
        }

        //Pega o menor vertice, independente dele ja ter sido visitado ou não
        if(visitado == 0){

            //Guarda o menor valor 
            if(*menorPeso > lista->peso || *menorPeso == 0){
                    *menorPeso = lista->peso;
                    *verticeMenor = valor;
            }
        }
        
        lista = lista->proximo;
    }

    if(*menorPeso == 0) return 0;

    return 1;
}


//Encontra uma árvore geradora mínima utilizando o algoritmo de prim
int encontraAGM(GRAFO * g){
    
    int pesoTotal = 0;
    int num_verts = g->num_verts;

    int vertsVisitados[num_verts];

    //Arvore agm
    int agm[num_verts];

    limpaVetor(agm, num_verts);
    limpaVetor(vertsVisitados, num_verts);

    //primeiro indice(raiz), ja é marcado como visitado.
    vertsVisitados[0] = 1;
    agm[0] = 0;
    int verticeAtual = 0;
    int verticePai = 0;

    while(1){

        verticePai = verticeAtual;
        
        int menorPeso = 0;
        int verticeMenor = -1; 


        //A posição do vertice no vetor agm, pode ser não ser a mesma na lista de adjacencia
        verticeAtual = buscaVertice(verticeAtual+1, g);

        lista_adjacencias * l = g->lista_vertices[verticeAtual].primeiro;

        // //Pega o menor peso, apenas se o vertice que o possui não foi visitado.
        int retorno = procuraMenorPeso(vertsVisitados, l, &menorPeso, &verticeMenor, 1);
          
        //Não conseguiu encontrar nenhum vertice não visitado na lista
        if(!retorno){
            int check = 1;

            //procura por vertices não visitados no grafo.
            for(int i = 0; i < num_verts; i++){
                if(vertsVisitados[i] == -1){
                
                    verticeAtual = buscaVertice(i+1, g);
                    lista_adjacencias * l = g->lista_vertices[verticeAtual].primeiro;

                    //pega o menor vertice, sendo ele visitado ou não.
                    procuraMenorPeso(vertsVisitados, l, &menorPeso, &verticeAtual, 0);

                    verticeAtual -=1;                    
                    check = 0;

                    break;
                }   
            }   
            
            //se não há vertices não visitados, encerra o programa.
            if(check == 1) break;

            //Vai p/ o vertice que ainda tem filhos não visitados
            if(check == 0) continue;
        }

        pesoTotal += menorPeso;
        vertsVisitados[verticeMenor-1] = verticeAtual;
        verticeAtual = verticeMenor-1;

        if(agm[verticeAtual] == -1){
            agm[verticeAtual] = verticePai;
        }

    }

    //Imprime o agm
    for(int i = 0 ; i < num_verts; i++){
        for(int j = 0; j<num_verts; j++){

            int valor = agm[j];

            if(valor == i && j != i){
                printf("%d -> %d\n", valor+1, j+1);
            }
                
        }            
    }

    printf("peso total: %d\n", pesoTotal);

}

int main(){
    int num_verts = 0;
    int num_arestas = 0;

    printf("Informe o número de vertices e de arestas, respectivamente: ");
    scanf("%d %d", &num_verts, &num_arestas);

    GRAFO * g = criaGrafo(num_verts, num_arestas);

    g = pedeValores(g);

    imprimeGrafo(g);
    
    encontraAGM(g);
    return 0;
}