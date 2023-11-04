#include <stdio.h>
#include <stdlib.h>

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

typedef struct list{
    int dest;
    int cost;
    struct list *next;
}List;

int n;

List** createGraph(int n){
    List **g = (List**)malloc((n + 1) * sizeof(List*));
    for(int i = 0; i <= n; i++) 
        g[i] = NULL;
    return g;
}

List *InsertList(List *list, int d, int c){
    List *new = (List *) malloc(sizeof(List));
    new->dest = d;
    new->cost = c;
    new->next = list;
    return new;
}

void InsertEdge(List **g, int o, int d, int c){
    if(o > n)
        printf("\nTamanho máximo é %d\n", n);
    else
        g[o] = InsertList(g[o], d, c);
}

List *RemoveItem(List *list, int d){
    if(list == NULL) 
        return NULL;

    List *prev = list;
    List *aux = prev->next;

    if(prev->dest == d){
        list = aux;
        free(prev);
    } else {
        while(aux != NULL && prev->dest != d){
            prev = aux;
            aux = aux->next;
        }
        if(aux != NULL){
            prev->next = aux->next;
            free(aux);
        }
    }
    return list;
}

void RemoveEdge(List **g, int o, int d){
    if(o > n)
        printf("\nTamanho máximo é %d\n", n);
    else
        g[o] = RemoveItem(g[o], d);  
}

void printList(List *g){
    if(g != NULL) {
        printf(" - (%d,%d)",g->dest, g->cost);
        printList(g->next);
    }
}

void printGraph(List **g, int n){
  for(int i = 1; i <= n; i++) {
    printf("\nOrigem: %d", i);
    printList(g[i]);
  }
  printf("\n");
}

void printInOut(List **g, int x){
    int out = 0;
    List *aux = g[x];
    while(aux != NULL) {
        out++;
        aux = aux->next;
    }

    int in = 0;
    for(int i = 1; i <= n; i++) {
        aux = g[i];
        while(aux != NULL) {
            if(aux->dest == x) 
                in++;
            aux = aux->next;
        }
    }

    printf("\nSaidas: %d", out);
    printf("\nEntradas: %d \n", in);
}

int isCompleted(List **g){
    int count = 0;
    for(int i = 1; i <= n; i++){
        List *aux = g[i];
        while(aux != NULL){
            count++;
            aux = aux->next;
        }
    }
    int eq = n * (n -1);
    if(count == eq)
        return 1;
    else 
        return 0;
} 

int exist(int *vet, int v, int p){
    for(int i = 0; i<p; i++){
        if(vet[i] == v)
            return 1;
    }
    return 0;
}

void path(List **g, int d, int *vet, int p){
    if(vet[p-1] == d){
        printf("\n");
        for(int i = 0; i<p; i++)
            printf("%d ", vet[i]);
    }
    else {
        List *l = g[vet[p-1]];
        while(l != NULL){
            if(!exist(vet, l->dest, p)){
                vet[p] = l->dest;
                path(g, d, vet, p+1);
            }
            l = l->next;
        }
    }
}

void shortestPath(List **g, int d, int *vet, int p, int **res, int *len){
    if(vet[p-1] == d && p < *len){
        //limpar o res
        int *r = (int *)malloc(p*sizeof(int));
        for(int i = 0; i<p; i++)
            r[i] = vet[i];
        *res = r;
        *len = p;
    }
    else {
        List *l = g[vet[p-1]];
        while(l != NULL){
            if(!exist(vet, l->dest, p)){
                vet[p] = l->dest;
                shortestPath(g, d, vet, p+1, res, len);
            }
            l = l->next;
        }
    }
}

void destruct(List **g){
    for(int i = 0; i <= n; i++){
        List* aux = g[i];
        while(aux != NULL){
            List *next = aux->next;
            free(aux);
            aux = next;
        }
    }
    free(g);
}

int mainMenu(){
    int option;
    printf("\n1- Inserir uma aresta no Grafo.");
    printf("\n2- Remover uma aresta do Grafo.");
    printf("\n3- Imprimir Grafo.");
    printf("\n4- Imprimir os graus de entrada e saída de um Vértice.");
    printf("\n5- Verificar se é completo.");
    printf("\n6- Imprimir todos os caminhos entre uma origem e um destino.");
    printf("\n7- Imprimir o caminho mais curto (Com menos arestas).");
    printf("\n8- Imprimir o caminho de menos custo (Menor soma dos custos).");
    printf("\n9- Sair\n");
    scanf("%d", &option);
    return option;
}

int main(){
    int option;
    printf("\nDigite o número de vértices do Grafo.\n");
    scanf("%d", &n);

    List** graph = createGraph(n);

    while (option != 9){

        option = mainMenu();
        if(option == 1){
            int orig, dest, cost;
            printf("\nDigite a origem, o destino e o custo (Nesta ordem).\n");
            scanf("%d %d %d", &orig, &dest, &cost);

            InsertEdge(graph,  orig,  dest,  cost);
        }
        if(option == 2){
            int orig, dest;
            printf("\nDigite a origem e o destino da aresta (Nesta ordem).\n");
            scanf("%d %d", &orig, &dest);

            RemoveEdge(graph, orig, dest);
        }
        if(option == 3){
            printGraph(graph, n);
        }
        if(option == 4){
            int ed;
            printf("\nInsira o vértice a se pesquisar.\n");
            scanf("%d", &ed);

            if(ed > n)
                printf("\nTamanho máximo é %d\n", n);
            else
                printInOut(graph, ed);
        }
        if(option == 5){
            if(isCompleted(graph) == 1)
                printf("\nÉ completo! \n");
            else
                printf("\nNão é completo! \n");
        }
        if(option == 6){
            int dest, *vet = (int *)malloc(n*sizeof(int));
            printf("\nDigite a origem e o destino (Nesta ordem).\n");
            scanf("%d %d", &vet[0], &dest);
            path(graph, dest, vet, 1);
            printf("\n");
        }
        if(option == 7){
            int dest, *res, len = n+1, *vet = (int *)malloc(n*sizeof(int));
            printf("\nDigite a origem e o destino (Nesta ordem).\n");
            scanf("%d %d", &vet[0], &dest);
            shortestPath(graph, dest, vet, 1, &res, &len);
            printf("\n");
            for(int i = 0; i<len; i++)
                printf("%d ", res[i]); 
            printf("\n");
        }
        if(option == 8){
            int orig, dest;
            printf("\nDigite a origem e o destino (Nesta ordem).\n");
            scanf("%d %d", &orig, &dest);
        }
        if(option == 9){
            destruct(graph);
        }
    }
}