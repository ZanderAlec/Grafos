#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/grafos.h"


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

//Converte um valor inteiro para string
char *  convertIntToChar ( int value, char * str )
{
    memset(str, 0, 4);

    char temp;
    int i =0;
    while (value > 0) {
        int digito = value % 10;

        str[i] = digito + '0';
        value /= 10;
        i++;

    }
   i = 0;
   int j = strlen(str) - 1;

   while (i < j) {
      temp = str[i];
      str[i] = str[j];
      str[j] = temp;
      i++;
      j--;
   }
    return str;
}


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

//Preenche todos os índices do vetor com "-1"
void limpaVetor(int vet[], int tam){
    for(int i = 0; i < tam; i++){
        vet[i] = -1;
    }
}

//Encontra a árvore geradora mínima(agm), a partir de um grafo direcionado e conexo
//Utilizada o algorítmo de kruskal.
void encontraAgmKruskal(GRAFO * g, int agm[], int *custo){

    int num_verts = g->num_verts;
    int arvAgm[num_verts];
    int menorPeso = 0, origem = 0, destino = 0;

    limpaVetor(agm, num_verts);
    for(int i = 0; i < num_verts; i++){
        arvAgm[i] = i;
    }

    agm[0] = 0;

    while(1){   
        int primeiro = 1;

        for(int i = 0; i<num_verts; i++){
            printf("i: %d | i+1: %d\n", i, i+1);

            int vertAtual = buscaVertice(i+1, g);

            // printf("vertAtual: %d\n", vertAtual);

            lista_adjacencias * l = g->lista_vertices[vertAtual].primeiro;
            lista_adjacencias * lista = g->lista_vertices[vertAtual].primeiro;

            while(lista != NULL){
                // printf("%d ", lista->valor);
                lista = lista->proximo;
            }

            printf("\n");

            while(l != NULL){

                // printf("l atual: %d\n", l->valor);
                // printf("i atual: %d\n", i);
                // printf("arvAgm[%d]: %d\n", i, arvAgm[i]);
                // printf("arvAgm[%d]: %d\n", l->valor-1, arvAgm[l->valor-1]);

                if(arvAgm[i] != arvAgm[l->valor-1]){
                     printf("são diferentes\n");
                    printf("%d != %d  ", i, arvAgm[l->valor-1]);
                    printf("\n");

                    for(int i = 0; i< num_verts; i++){
                        printf("%d = %d", i, arvAgm[i]);
                    }
                    printf("\n");
                   
                    if(primeiro){
                        // printf("é o primerio valor\n");
                        menorPeso = l->peso;
                        origem = i;
                        destino = l->valor;
                        primeiro = 0;

                    }else{

                        if(menorPeso > l->peso){
                            menorPeso = l->peso;
                            origem = i;
                            destino = l->valor;
                        }
                    }
                }
                
                // printf("menorPeso: %d\n", menorPeso);
                // printf("origem: %d\n", origem);
                // printf("destino: %d\n", destino);
            
                l = l->proximo;
            }

            printf("menorPeso: %d\n", menorPeso);
                printf("origem: %d\n", origem);
                printf("destino: %d\n", destino);
        }

        printf("SAIU DO LOOP \n");
        printf("menorPeso: %d\n", menorPeso);
        printf("origem: %d\n", origem);
        printf("destino: %d\n", destino);

        if(primeiro) break;

        if(agm[origem] == -1){
            agm[origem] = destino;
        }else{
            agm[destino-1] = origem+1;
        }

        *custo += menorPeso;
        printf("custo : %d\n", *custo);

        //Conecta as diferentes árvores:
        for(int i = 0; i< num_verts; i++){
            if(arvAgm[i] == arvAgm[destino-1]){
                arvAgm[i] = arvAgm[origem];
            }
        }
    }

    printf("custo : %d\n", *custo);
    printf("arvAGM====================================\n");
    for(int i = 0; i< num_verts; i++){
            printf("%d = %d\n", i, arvAgm[i]);
    }

     printf("AGM====================================\n");
     for(int i = 0; i< num_verts; i++){
            printf("%d = %d\n", i, agm[i]);
    }
}


//Recebe um vetor com a agm e escreve num arquivo.
int imprimeGrafoArquivo(char urlSaida[], int agm[], int num_verts, int custo, int crescente){
    printf("entrei no imprime algo\n");

    int size = 0;

    for(int i = 0; urlSaida[i] != '\0'; i++){
       size++;
    }
    
    char url[size+1];

    memcpy(url, urlSaida, size+1);

    FILE * file;

    file = fopen(url, "a");

    if(file == NULL){
        printf("Não foi possível abrir o arquivo");
        printf("Barras '\\' precisam ser duplas. EX: C:\\ = C:\\\\\n");
        return 0;
    }

    if(crescente){

        for(int i = 0; i < num_verts; i++){
            for(int j = 0; j<num_verts; j++){
                if(agm[j] == i){
                    fprintf(file, "(");
                    char aresta[4];
                    convertIntToChar(agm[j], aresta);
                    fputs(aresta, file);
                    fprintf(file, ",");
                    convertIntToChar(j+1, aresta);
                    fputs(aresta, file);
                    fprintf(file, ") ");
                }
            }
        }
    }else{
        for(int i = 0; i < num_verts; i++){
            if(agm[i] != i){
                fprintf(file, "(");
                char aresta[4];
                convertIntToChar(agm[i], aresta);
                fputs(aresta, file);
                fprintf(file, ",");
                convertIntToChar(i+1, aresta);
                fputs(aresta, file);
                fprintf(file, ") ");
            }
        }
    }

    char totalCusto[3];
    convertIntToChar(custo, totalCusto);
    fprintf(file, "\n");
    fputs(totalCusto, file);    

    fclose(file);
    return 0;
}

int main(int argc, char *argv[]){

    int crescente = 0;
    char urlEntrada[150], urlSaida[150];

    for(int i = 0; i < argc; i++){
        if(!strcmp(argv[i], "-h")){
            printf("-h : mostra o help\n -o <arquivo> : redireciona a saida para o ''arquivo''\n -f <arquivo> : indica o ''arquivo'' que contém o grafo de entrada\n -s : mostra a solução (em ordem crescente)\n -i : vértice inicial (para o algoritmo de Prim)\n");
        }

        if(!strcmp(argv[i], "-o")){
                strcpy(urlSaida,argv[i+1]);
        }

        if(!strcmp(argv[i], "-f")){
                strcpy(urlEntrada,argv[i+1]);
        }

        if(!strcmp(argv[i], "-s")){
            crescente = 1;
        }

    }

    GRAFO * g = NULL;
    g = criaGrafoArquivo(urlEntrada, g);

    imprimeGrafo(g);

    if(g!=NULL){

        size_t tam = g->num_verts;

        int agm[tam];
        int custo = 0;

        encontraAgmKruskal(g, agm, &custo);
        imprimeGrafoArquivo(urlSaida, agm, tam, custo, crescente);

        liberaGrafo(g);        
    }


    return 0;
}