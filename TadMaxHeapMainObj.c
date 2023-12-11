#include <stdio.h>
#include "TadMaxHeap.h"

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

typedef struct carro{
    int n;
    char plate[10];
}Carro;


int mainMenu(){
    int option;
    printf("\n1 - Inserir um carro na fila.");
    printf("\n2 - Remover um carro da fila.");
    printf("\n3 - Verificar se o carro existe na fila.");
    printf("\n4 - Imprimir a fila de carros.");
    printf("\n5 - Exibir elemento pela chave.");
    printf("\n6 - Sair\n");
    scanf("%d", &option);
    return option;
}

void printMain(Carro *c){
    printf("placa: %s e número: %d", c->plate, c->n);
} 

int main(){
    TadMaxHeap q = start();
    int option;

    while (option != 6){

        option = mainMenu();
        if(option == 1){
            Carro c;
            int x;
            printf("\nDigite a chave do carro.\n");
            scanf("%d", &x);
            printf("\nDigite o numero do carro.\n");
            scanf("%d", &c.n);
            printf("\nDigite a placa do carro.\n");
            scanf("%s", c.plate);
            if(insertItem(q, x, &c, sizeof(c)) == 0)
                printf("\nA fila esta cheia!\n");
        }
        if(option == 2){
            int key;
            Carro c;
            if(removeItem(q, &key, &c, sizeof(c)) == 0)
                printf("\nA fila esta vazia!\n");
            else {
                printf("\nO item removido foi: %d\n", key);
                printMain(&c);
                printf("\n");
            }
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