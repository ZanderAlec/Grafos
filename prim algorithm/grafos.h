#include <stdio.h>
#include <stdlib.h>

//Estrutura do grafo---------------------------------

typedef struct adj{
    //valor do vertice ligado
    int valor;
    //peso da aresta
    int peso; 
    //proximo vertice 
    struct adj * proximo;
}lista_adjacencias;

typedef struct vert{
    //valor do vertice 
    int valor;
    //primeira aresta
    lista_adjacencias * primeiro;
}vertice;

typedef struct grafo{
    int num_verts;
    int num_arestas;
    vertice * lista_vertices;
}GRAFO;

//Inicia o grafo.
GRAFO * criaGrafo(int numVerts, int numArestas){
    GRAFO * g = (GRAFO *)malloc(sizeof(GRAFO));

    if(g == NULL){
        printf("Não há espaço para criar o grafo!\n");
        return NULL;
    }

    g->lista_vertices =  (vertice * ) malloc(numVerts * sizeof(vertice));

     //Inicia a lista de vértices

    for(int i = 0; i < numVerts; i++){
        g->lista_vertices[i].valor = -1;
        g->lista_vertices[i].primeiro = NULL;
    }

    g->num_arestas = numArestas;
    g->num_verts = numVerts;

    return g;
}

//Insere o vertice no grafo
void  insereVertice(GRAFO * g, int valor){

    int tam = g->num_verts;

    //Procura um indice vazio e insere o valor nele
    for(int i = 0; i < tam; i++){

        int tempValue = g->lista_vertices[i].valor;

        if(tempValue == -1){
            g->lista_vertices[i].valor = valor;
            break;
        }
    }
}

//Cria a estrutura do elemento da lista de adjacencia e retorna-o
lista_adjacencias * criaAdjacencia(int valor, int peso){

    lista_adjacencias * l = (lista_adjacencias * ) malloc(sizeof(lista_adjacencias));

    if(l == NULL){
        printf("Não há espaço para criar a lista!\n");
        return NULL;
    }

    l->valor = valor;
    l->peso = peso;
    l->proximo = NULL;

    return l;
}

//Adiciona a adjacencia a lista de adjacencias do vertice
lista_adjacencias * insereAdjacencia(lista_adjacencias * lista, int valor, int peso){
    
    // printf("ENTREI NO INSERE ADJACENCIA\n");
    // printf("valor: %d\n", valor);

    lista_adjacencias * adj = criaAdjacencia(valor , peso);

    //Se a lista estiver vazia, adiciona o elemento como primeiro
    if(lista == NULL){
        // printf("lista TAVA VAZIAR\n");
        lista = adj;
    
    //Se não estiver, procura um espaço vazio e adiciona:
    }else{

        // printf("lista JÁ TINHA COISA\n");

        lista_adjacencias * l = lista;

        while(l->proximo != NULL){
            l = l->proximo;
        }

        l->proximo = adj;
    }
    return lista;
}

// //Verifica se um vértice já foi inserido no grafo
//Retorna a posição do vertice se existir, ou -1, se não existir.
int  buscaVertice(int valorBuscado, GRAFO * g){

    int tam = g->num_verts;

    for( int i = 0; i< tam ; i++){
        int valor = g->lista_vertices[i].valor;

        //Valor existe
        if(valor == valorBuscado) return i;
    }

    //Valor não existe

    return -1;
}

// //Adiciona os vertices e as arestas ao grafo
GRAFO * adicionaVerticeAresta(int valorPai, int valorFilho, int peso, GRAFO * g){

    int vPai = buscaVertice(valorPai, g);
  
    // //Se o pai não existe, cria-o.
    if(vPai == -1){
        insereVertice(g, valorPai);
        vPai = buscaVertice(valorPai, g);
    }

    int  vFilho = buscaVertice(valorFilho, g);

    // //Se o filho não existe, cria-o.
    if(vFilho == -1){
        insereVertice(g, valorFilho);
        vFilho = buscaVertice(valorFilho, g);
    }

    //Adiciona as adjacencias, tanto no pai quanto no filho, pois o grafo não é direcionado.
    lista_adjacencias * lpai = g->lista_vertices[vPai].primeiro;
    g->lista_vertices[vPai].primeiro = insereAdjacencia(lpai, valorFilho, peso);

    lista_adjacencias * lfilho = g->lista_vertices[vFilho].primeiro;
    g->lista_vertices[vFilho].primeiro = insereAdjacencia(lfilho, valorPai, peso);

    return g;
}

void imprimeGrafo(GRAFO * g){

      for(int i = 0; i < g->num_verts; i++){
        printf("%d ",g->lista_vertices[i].valor);

        lista_adjacencias * l = g->lista_vertices[i].primeiro;

        while(l != NULL){
            printf("%d(%d) ",l->valor, l->peso);

            l = l->proximo;
        }
        printf("\n");
    }
}