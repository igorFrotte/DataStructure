#include <stdio.h>

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

typedef struct list{
    int dest;
    int cost;
    struct list *next;
}List;

List** createGraph(int n){
    List **g = (List**)malloc((n + 1) * sizeof(List*));
    for(int i = 0; i <= n; i++) 
        g[i] = NULL;
    return g;
}

List *InseritList(List *list, int d, int c){
    List *new = (List *) malloc(sizeof(List));
    new->dest = d;
    new->cost = c;
    new->next = list;
    return new;
}

void InsertEdge(List **g, int o, int d, int c){
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

void RemoveEdge(List **g, int o, int d) {
    g[o] = RemoveItem(g[o], d);  
}







int mainMenu(){
    int option;
    printf("\n1- Inserir uma aresta no Grafo.");
    printf("\n2- Remover uma aresta do Grafo.");
    printf("\n3- Imprimir Grafo.");
    printf("\n4- Imprimir os graus de entrada e saída de um Vértice.");
    printf("\n5- Verificar se é completo.");
    printf("\n6- Sair\n");
    scanf("%d", &option);
    return option;
}

int main(){
    int option, n;
    printf("\nDigite o número de vértices do Grafo.\n");
    scanf("%d", &n);

    List** graph = createGraph(n);

    while (option != 6){

        option = mainMenu();
        if(option == 1){
            int orig, dest, cost;
            printf("Digite a origem, o destino e o custo (Nesta ordem): \n");
            scanf("%d %d %d", &orig, &dest, &cost);

            InsertEdge(graph,  orig,  dest,  cost);
        }
        if(option == 2){
            
        }
        if(option == 3){
            
        }
        if(option == 4){
            
        }
        if(option == 5){
            
        }
        if(option == 6){
            
        }
    }
}