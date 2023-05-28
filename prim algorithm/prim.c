#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/grafos.h"

struct priori{
    int valor;
    int peso;
    struct priori * prox;
}prioridade;


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

//lê o arquivo e cria o grafo a partir dele
GRAFO * criaGrafoArquivo(char urlent[],GRAFO * g){

    int size = 0;

    for(int i = 0; urlent[i] != '\0'; i++){
       size++;
    }
    
    char url[size+1];

    memcpy(url, urlent, size+1);

    FILE * file;

    file = fopen(url, "r");

    if(file == NULL){
        printf("Não foi possível abrir o arquivo");
        return 0;
    }

    int i = 0, x = 0, y = 0,z = 0;
    fscanf(file, "%d %d", &x, &i);
    
    g = criaGrafo(x,i);

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


//Recebe um vetor com a agm e escreve num arquivo.
int imprimeGrafoArquivo(char urlSaida[], int agm[], int num_verts, int custo, int crescente){
    int size = 0;

    for(int i = 0; urlSaida[i] != '\0'; i++){
       size++;
    }
    
    char url[size+1];

    memcpy(url, urlSaida, size+1);

    FILE * file;

    file = fopen(url, "a");

    if(file == NULL){
        printf("Não foi possível abrir o arquivo\n");
        printf("Barras '\\' precisam ser duplas. EX: C:\\ = C:\\\\\n");
        return 0;
    }

    if(crescente){

        for(int i = 0; i < num_verts; i++){
            for(int j = 0; j<num_verts; j++){
                if(agm[j] == i){
                    fprintf(file, "(");
                    char aresta[4];
                    convertIntToChar(i+1, aresta);
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
            fprintf(file, "(");
            char aresta[4];
            convertIntToChar(agm[i]+1, aresta);
            fputs(aresta, file);
            fprintf(file, ",");
            convertIntToChar(i+1, aresta);
            fputs(aresta, file);
            fprintf(file, ") ");
        }
    }

    char totalCusto[3];
    convertIntToChar(custo, totalCusto);
    fprintf(file, "\n");
    fputs(totalCusto, file);    

    fclose(file);
    return 0;
}


//Encontra uma árvore geradora mínima utilizando o algoritmo de prim
void algPrim(GRAFO * g, int origem, int pai[], int *custo){
    
   int i,j, dest, primeiro, num_verts = g->num_verts;    
   int menorPeso = 0;   

   for(i = 0; i < num_verts; i++){
        pai[i] = -1;
   }

    pai[origem-1] = origem-1;

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
        *custo += menorPeso;
    }

}

int main(int argc, char *argv[]){

    int vinicial = 1, crescente = 0;
    char urlEntrada[150],  urlSaida[150];

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

        if(!strcmp(argv[i], "-i")){
            vinicial =  atoi(argv[i+1]);
        }

    }

    GRAFO * g = NULL;

    g = criaGrafoArquivo(urlEntrada, g);

    if(g!=NULL){
        size_t tam = g->num_verts;
        int agm[tam];
        int custo = 0;

        algPrim(g,vinicial, agm, &custo);

        imprimeGrafoArquivo(urlSaida, agm,tam, custo, crescente);

        liberaGrafo(g);
    }

    return 0;
}