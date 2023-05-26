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
void encontraAgmKruskal(GRAFO * g, int vagm[], int *custo){

    limpaVetor(vagm, g->num_verts);

    GRAFO * agm = criaGrafo(g->num_verts, g->num_arestas);

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

        if(vagm[v2-1] == -1){
             vagm[v2-1] = v1;
        }else{
             vagm[v1-1] = v2;
        }

        *custo += menorPeso;

        //Caso encontrou vertices não visitados adiciona eles à agm:
        adicionaVerticeAresta(v1,v2,menorPeso,agm);
    }

    liberaGrafo(agm);

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
        printf("Não foi possível abrir o arquivo");
        return 0;
    }

    if(crescente){

        for(int i = 0; i < num_verts; i++){
            for(int j = 0; j<num_verts; j++){
                if(agm[j] == i){
                    fprintf(file, "(");
                    char aresta[2];
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
            if(agm[i] != -1){
                fprintf(file, "(");
                char aresta[2];
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

    if(g!=NULL){

        imprimeGrafo(g);

        int agm[g->num_verts];
        int custo = 0;
        // GRAFO * agm = criaGrafo(g->num_verts, g->num_arestas);
        // imprimeGrafoArquivo(urlSaida, agm, g->num_verts, custo, crescente);
        encontraAgmKruskal(g, agm, &custo);
        // imprimeGrafo(agm);

        imprimeGrafoArquivo(urlSaida, agm, g->num_verts, custo, crescente);

        liberaGrafo(g);        
    }


    return 0;
}