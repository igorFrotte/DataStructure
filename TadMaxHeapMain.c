#include <stdio.h>
#include "TadMaxHeap.h"

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

int mainMenu(){
    int option;
    printf("\n1 - Inserir um elemento na fila.");
    printf("\n2 - Remover um elemento da fila.");
    printf("\n3 - Verificar se existe na fila.");
    printf("\n4 - Imprimir a fila.");
    printf("\n6 - Sair\n");
    scanf("%d", &option);
    return option;
}

int main(){
    TadMaxHeap q = start();
    int option;

    while (option != 6){

        option = mainMenu();
        if(option == 1){
            int x;
            printf("\nDigite o valor do elemento.\n");
            scanf("%d", &x);
            if(insertItem(q, x, &x, sizeof(x)) == 0)
                printf("\nA fila esta cheia!\n");
        }
        if(option == 2){
            int x;
            if(removeItem(q, &x, &x, sizeof(x)) == 0)
                printf("\nA fila esta vazia!\n");
            else 
                printf("\nO item removido foi: %d\n", x);
        }
        if(option == 3){
            int x;
            printf("\nDigite a chave do elemento.\n");
            scanf("%d", &x);
            if(exist(q, x) == 1)
                printf("\nO elemento existe!\n");
            else printf("\nO elemento não existe!\n");
        }
        if(option == 4){
            printAll(q);            
        }
        if(option == 6){
            q = destruct(q);
        }
    }
}