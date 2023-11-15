#include <stdio.h>

#define N 11

typedef struct student {
    int regist;
    char name[50];
    char course[50];
} Student;

typedef struct data {
    Student stud;
    int avail;
} Data;

void fStart(char *fName){
    FILE *f = fopen(fName, "wb");
    Data d;
    d.avail = 1;
    int i;
    for(i = 0; i<N ; i++)
        fwrite(&d, sizeof(Data), 1, f);
    fclose(f);
}



int mainMenu(){
    int option;
    printf("\n1- Inserir um novo Aluno.");
    printf("\n2- Imprimir informações do Aluno.");
    printf("\n3- Imprimir a tabela de dispersão.");
    printf("\n4- Sair\n");
    scanf("%d", &option);
    return option;
}

int main(){
    int option;

    while (option != 4){

        option = mainMenu();
        if(option == 1){
           
        }
        if(option == 2){
            
        }
        if(option == 3){
            
        }
        if(option == 4){
            
        }
    }
}