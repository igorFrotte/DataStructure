#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 11

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

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
    d.stud = NULL;
    int i;
    for(i = 0; i<N ; i++)
        fwrite(&d, sizeof(Data), 1, f);
    fclose(f);
} 

int hash(int x){
    return x % N;
}

int findPos(char *fName, int x){
    int pos = hash(x) -1;
    Data d;
    FILE *f = fopen(fName, "rb");
    do {
        pos = (pos+1) % N;
        fseek(f ,pos * sizeof(Data), SEEK_SET);
        fread(&d , sizeof(Data), 1, f);
    } while(d.avail == 0);
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

Student * createStudent(int reg, char *nam, char *cou){
    Student *s = (Student*)malloc(sizeof(Student));
    s->regist = reg;
    strcpy(s->name, nam);
    strcpy(s->course, cou);
    return s;
}

Student* findStudent(char *fName, int x){
    int count = 0, pos = hash(x) - 1;
    Data d;
    FILE *f = fopen(fName, "rb");
    do {
        pos = (pos+1) % N;
        fseek(f ,pos * sizeof(Data), SEEK_SET);
        fread(&d , sizeof(Data), 1, f);
        count++;
        if(count == N || d.stud == NULL)
            break;
    } while(d.stud->regist != x);
    fclose(f);
    if(count == N)
        return NULL;
    return d.stud;
}

void printStudent(char *fName, int r){
    Student *s = findStudent(fName, r);
    if(s == NULL)
        printf("\nEsta Matrícula não existe!\n");
    else
        printf("\nMatricula: %d, Nome: %s, Curso: %s.\n", s->regist, s->name, s->course);
}

void printHashTable(char *fName){
    FILE *f = fopen(fName, "rb");
    Data d;
    int i;
    printf("\n");
    for(i=0; i<N; i++){
        fread(&d , sizeof(Data), 1, f);
        if(d.avail == 0)
            printf("Matricula: %d, Nome: %s, Curso: %s.\n", d.stud->regist, d.stud->name, d.stud->course);
        else if(d.avail == 1)
            printf("Disponível\n");
    }
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
    char *fName = "hash.bin";
    fStart(fName);

    while (option != 4){

        option = mainMenu();
        if(option == 1){
            int r;
            char n[50], c[50];
            Student *s;
            printf("\nDigite a matrícula, o nome e o curso do Aluno.\n");
            scanf("%d %s %s", &r, n, c);
            s = createStudent(r , n, c);
            insertStudent(fName, s);
        }
        if(option == 2){
            int r;
            printf("\nDigite a matrícula do Aluno.\n");
            scanf("%d", &r);
            printStudent(fName ,r);
        }
        if(option == 3){
            printHashTable(fName);
        }
    }
}