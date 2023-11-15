#include <stdio.h>

#define N 11

typedef struct student {
    int regist;
    char name[50];
    char course[50];
} Student;

typedef struct data {
    Student *stud;
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

int hash(int x){
    return x % N;
}

int insertStudent(char *fName, int x){
    int pos = hash(x);
    Data d;
    FILE *f = fopen(fName, "rb");
    fseek(f ,pos * sizeof(Data), SEEK_SET);
    fread(&d , sizeof(Data), 1, f);
    while(d.avail == 0){
        pos = (pos+1) % N;
        fseek(f ,pos * sizeof(Data), SEEK_SET);
        fread(&d , sizeof(Data), 1, f);
    }
    fclose(f);
    return pos;
}

void insertStudent(char *fName, Student *s){
    int pos = findPos(fName, s->regist);
    FILE *f = fopen(fName, "r+b");
    Data d;
    d.avail = 0;
    d.stud = s;
    fseek(f ,pos * sizeof(Data), SEEK_SET);
    fwrite(&d , sizeof(Data), 1, f);
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