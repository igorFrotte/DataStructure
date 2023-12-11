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
    printf("\n5 - Exibir elemento pela posição.");
    printf("\n6 - Sair\n");
    scanf("%d", &option);
    return option;
}

void printMain(int *x){
    printf("%d", *x);
} 

int main(){
    TadMaxHeap q = start();
    int option;

    while (option != 6){

        option = mainMenu();
        if(option == 1){
            int x, y;
            printf("\nDigite o valor do elemento.\n");
            scanf("%d", &x);
            y = x;
            if(insertItem(q, x, &y, sizeof(int)) == 0)
                printf("\nA fila esta cheia!\n");
        }
        if(option == 2){
            int x, y;
            if(removeItem(q, &x, &y, sizeof(int)) == 0)
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
            void *f = &printMain;
            printAll(q, f);            
        }
        if(option == 5){
            int x;
            void *f = &printMain;
            printf("\nDigite a chave do elemento.\n");
            scanf("%d", &x);
            printItem(q, x, f);
        }
        if(option == 6){
            q = destruct(q);
        }
    }
}