#include <stdio.h>
#include <stdlib.h>

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
    //prox elemento da lista de vertices
    struct vert * proximo; 
    //primeira aresta
    lista_adjacencias * primeiro;
}vertice;

typedef struct grafo{
    int num_verts;
    int num_arestas;
    vertice * lista_vertices;
}GRAFO;

//Inicia o grafo
GRAFO * criaGrafo(int verts, int arestas){
    GRAFO * g = (GRAFO *)malloc(sizeof(GRAFO));

    if(g == NULL){
        printf("Não há espaço para criar o grafo!\n");
        return NULL;
    }

    g->num_arestas = arestas;
    g->num_verts = verts;
    g->lista_vertices = NULL;

    return g;
}

//Cria a estrutura do vertice
vertice * criaVertice(int valor){
    vertice * v = (vertice *) malloc(sizeof(vertice));

    if(v == NULL){
        printf("Não há espaço para criar o vértice!\n");
        return NULL;
    }

    v->valor = valor;
    v->primeiro = NULL;
    v->proximo = NULL;

    return v;
}

//Insere o vertice no grafo
void insereVertice(GRAFO * g, int valor){
    vertice * vert = criaVertice(valor);

     //Se o grafo não tiver vertices, adiciona ele como primeiro da lista:
    if(g->lista_vertices == NULL){
        vert->proximo = NULL;
        g->lista_vertices = vert;
        return;
    }

    //Se o grafo ja tiver vertices, procura um espaço vazio na lista de vertices e adiciona ele:
    vertice * p = g->lista_vertices;

    while(p->proximo != NULL){
        p = p->proximo;
    }

    p->proximo = vert;
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
    
    lista_adjacencias * adj = criaAdjacencia(valor , peso);

    //Se a lista estiver vazia, adiciona o elemento como primeiro
    if(lista == NULL){
        lista = adj;
    
    //Se não estiver, procura um espaço vazio e adiciona:
    }else{

        lista_adjacencias * l = lista;

        while(l->proximo != NULL){
            l = l->proximo;
        }

        l->proximo = adj;
    }

    return lista;
}

//Verifica se um vértice já foi inserido no grafo
//Retorna um ponteiro para o vertice se existir. Ou null, se não existir.
vertice *  buscaVertice(int valorVertice, GRAFO * g){

    vertice * v = g->lista_vertices;

    while(v){
        if(v->valor == valorVertice){
            //Valor existe
            return v;
        }

        v = v->proximo;
    }

    //valor não existe
    return NULL;
}

//Adiciona os vertices e as arestas ao grafo com base no 
//formato de entrada agm
GRAFO * adicionaVerticeAresta(int valorPai, int valorFilho, int peso, GRAFO * g){

    vertice * vPai = buscaVertice(valorPai, g);
  
    // //Se o pai não existe, cria-o.
    if(vPai == NULL){
        insereVertice(g, valorPai);
        vPai = buscaVertice(valorPai, g);
    }

    vertice * vFilho = buscaVertice(valorFilho, g);

    // //Se o filho não existe, cria-o.
    if(vFilho == NULL){
        insereVertice(g, valorFilho);
        vFilho = buscaVertice(valorFilho, g);
    }

    //Adiciona a adjacencia
    vPai->primeiro = insereAdjacencia(vPai->primeiro, valorFilho, peso);

    vFilho->primeiro = insereAdjacencia(vFilho->primeiro, valorPai, peso);

    return g;
}

void imprimeGrafo(GRAFO * g){

    printf("%d %d\n", g->num_verts, g->num_arestas);

    vertice * v = g->lista_vertices;

    while(v != NULL){
        lista_adjacencias * l = v->primeiro;

        while(l != NULL){
            printf("%d ", v->valor);
            printf("%d ", l->valor);
            printf("%d\n", l->peso);
            
            l = l->proximo;
        }

        v = v->proximo;
    }
}

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

//Zera todos os indices de um vetor
void zeraVetor(int vet[], int tam){
    for(int i = 0; i < tam; i++){
        vet[i] = 0;
    }
}

//Procura um indice vazio e insere o valor nesse indice
void insereVetor(int vet[], int valor, int tam){

    for(int i = 0; i < tam; i++){
        if(vet[i] == 0){
            vet[i] = valor;
            return;
        }
    }
}

//Encontra uma árvore geradora mínima utilizando o algoritmo de prim
void encontraAGM(GRAFO * g){
   
    int vertsVisitados[g->num_verts];
    int agm[g->num_verts];
    int custo = 0;

    zeraVetor(vertsVisitados, g->num_verts);
    zeraVetor(agm, g->num_verts);

    int menorPeso = 0;
    int vertMenor = -1;

    // //Sempre começa pelo primeiro indice
    vertice * v = g->lista_vertices;

    while(1){

        vertsVisitados[(v->valor)-1] = 1;

        insereVetor(agm, v->valor, g->num_verts);

        menorPeso = 0;
        vertMenor = -1;

        lista_adjacencias * l = v->primeiro;

        while(l != NULL){

            //primeiro valor p/ base
            if(vertsVisitados[l->valor-1] == 0 && menorPeso == 0){
                menorPeso = l->peso;
                vertMenor = l->valor;
            }

            //atribui o menor peso
            if(vertsVisitados[l->valor-1] == 0 && menorPeso > l->peso){
                menorPeso = l->peso;
                vertMenor = l->valor;
            }

            l = l->proximo;
        }

        //Se o menor peso não foi alterado, então todos os vertices foram percorridos
        if(menorPeso == 0){
            break;
        }

        custo += menorPeso;
        
        v = buscaVertice(vertMenor, g);

    }

    for(int i = 0; i< g->num_verts; i++){
        printf("%d -> ", agm[i]);
    }

    printf("\n%d\n", custo);
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