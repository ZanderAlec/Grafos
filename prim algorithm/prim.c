#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/grafos.h"

struct priori{
    int valor;
    int peso;
    struct priori * prox;
}prioridade;

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




//Verifica se a url atende todos os requisitos.
//retorna 1 se atender.
//Retorna 0 se não atender.
int verificaUrl(char url[]){

    if(url == NULL){
        printf("Digite um endereço!\n");
    }else{
        for(int i = 0; url[i] != '\0'; i++){
            if(url[i] == '\\'){
                return 1;
            }
         }
    }

    return 0;
}

//lê o arquivo e cria o grafo a partir dele
GRAFO * criaGrafoArquivo(char urlent[],GRAFO * g){

    int size = 0;

    for(int i = 0; urlent[i] != '\0'; i++){
       size++;
    }
    
    char url[size+1];

    memcpy(url, urlent, size+1);

    FILE * file;

    file = fopen(urlent, "r");

    if(file == NULL){
        printf("Não foi possível abrir o arquivo");
        return 0;
    }

    int i, x = 0, y = 0,z = 0;
    fscanf(file, "%d %d", &x, &i);

    g = criaGrafo(x,y);

    for(int j = 0; j<i+1; j++){
        if(j == 0){

        }else{
            fscanf(file, "%d %d %d\n", &x, &y, &z);
             adicionaVerticeAresta(x,y,z, g);
        }
    }

    fclose(file);
    return g;
}

// void imprimeGrafoArquivo(char urlSaida[], GRAFO * g){
//     int size = 0;

//     for(int i = 0; urlSaida[i] != '\0'; i++){
//        size++;
//     }
    
//     char url[size+1];

//     memcpy(url, urlSaida, size+1);

//     FILE * file;

//     file = fopen(url, "a");

//     if(file == NULL){
//         printf("Não foi possível abrir o arquivo");
//         return 0;
//     }

//     //Imprime o agm
  
// }


//Encontra uma árvore geradora mínima utilizando o algoritmo de prim
void algPrim(GRAFO * g, int origem, int pai[]){

    printf("ENTREI NO ALGO\n");
    
   int i,j, dest, primeiro, num_verts = g->num_verts;    
   double menorPeso;
   double pesoTotal = 0;

   printf("origem: %d\n", origem);
   

   for(i = 0; i < num_verts; i++){
        pai[i] = -1;
   }

    pai[origem-1] = origem-1;

     //--------------até aqui suave

    while(1){

        primeiro = 1;

        for(int i =0; i < num_verts; i++){
            //Procura um pai já visitado
            if(pai[i] != -1){
                //Percorre os vizinhos do vértice visitado
                int vertAtual = buscaVertice(i+1, g);
                
                lista_adjacencias * lista = g->lista_vertices[vertAtual].primeiro;

                while(lista != NULL){

                    if(pai[lista->valor-1] == -1){

                        if(primeiro){
                            menorPeso = lista->peso;
                            origem = i;
                            dest = lista->valor;
                            primeiro = 0;

                        }else{

                            if(menorPeso > lista->peso){
                                menorPeso = lista->peso;
                                origem = i;
                                dest = lista->valor;
                            }
                        }
                    }
                
                    lista = lista->proximo;
                }
            }
        }
        
        if(primeiro) break;
        pai[dest-1] = origem;
    }

    for(i = 0; i < num_verts; i++){
        printf("(%d,%d) ", pai[i]+1, i+1);
    }

    printf("\n");
}

int main(int argc, char *argv[]){

    int vinicial = 1;
    char urlEntrada[100], urlSaida[100];

    for(int i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-h")){
            printf("AYUDA!\n");
        }
        if(!strcmp(argv[i], "-o")){

            if(verificaUrl(argv[i+1])){
                strcpy(urlSaida,argv[i+1]);
            }else{
                printf("O endereço do arquivo deve ser enviada com barras duplas. Ex: \"c:\\\" = \"c:\\\\\"\n");
                return 0;
            }
        }

        if(!strcmp(argv[i], "-f")){

            if(verificaUrl(argv[i+1])){
                strcpy(urlEntrada,argv[i+1]);
            }else{
                printf("O endereço do arquivo deve ser enviada com barras duplas. Ex: \"\\\" = \"\\\\\"\n");
                return 0;
            }
        }

        if(!strcmp(argv[i], "-s")){
            printf("SOLUÇÃO CRESCENTE\n");
        }

        if(!strcmp(argv[i], "-i")){
            vinicial =  atoi(argv[i+1]);
        }

    }

    // char urlEntrada[] = "C:\\Users\\WINDOWS\\Downloads\\Bat1\\instances\\exemp.mtx";

    GRAFO * g = NULL;
    g = criaGrafoArquivo(urlEntrada, g);

    if(g!=NULL){
        imprimeGrafo(g);

        int agm[g->num_verts];

        //O vinicial é passado -1 por causa da relação com o vetor agm.
        //onde agm[0] = 1; agm[1] = 1 etc...
        algPrim(g,vinicial, agm);

        liberaGrafo(g);
    }

    

    return 0;
}