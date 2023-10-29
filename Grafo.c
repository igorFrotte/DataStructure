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
    int option;

    while (option != 6){
    
        option = mainMenu();
        if(option == 1){
            
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