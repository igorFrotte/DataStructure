#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 100

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

int nextFreeIndex = 0;

typedef struct teacher {
    int regist;
    char name[50];
    int salary;
} Teacher;

typedef struct student {
    int regist;
    char name[50];
    char course[50];
    int year;
} Student;

typedef struct person {
    char type;
    void *item;
} Person;

void vetStart(Person *vetP){
    int i;
    for(i=0; i<N; i++){
        vetP[i].type = ' ';
        vetP[i].item = NULL;
    }
}

void insertPerson(Person *vetP, void *inf, char type){
    if(nextFreeIndex < N){
        vetP[nextFreeIndex].type = type;
        vetP[nextFreeIndex].item = inf;
        nextFreeIndex++;
    } else
        printf("\nA lista está cheia!\n");
}

void insertStudent(Person *vetP, int reg, char *nam, char *cou, int yea){
    Student *s = (Student*)malloc(sizeof(Student));
    s->regist = reg;
    strcpy(s->name, nam);
    strcpy(s->course, cou);
    s->year = yea;
    insertPerson(vetP, s, 's');
}

void insertTeacher(Person *vetP, int reg, char *nam, int sal){
    Teacher *t = (Teacher*)malloc(sizeof(Teacher));
    t->regist = reg;
    strcpy(t->name, nam);
    t->salary = sal;
    insertPerson(vetP, t, 't');
}

void removePerson(Person *vetP, int reg){
    int i;
    for(i=0; i<nextFreeIndex; i++){
        if(vetP[i].type == 's'){
            Student *s = (Student*) vetP[i].item;
            if(s->regist == reg){
                free(s);
                vetP[i].type = ' ';
                vetP[i].item = NULL;
            }
        }
        if(vetP[i].type == 't'){
            Teacher *t = (Teacher*) vetP[i].item;
            if(t->regist == reg){
                free(t);
                vetP[i].type = ' ';
                vetP[i].item = NULL;
            }
        }
    }
}

void findPerson(Person *vetP, int reg){
    int i;
    for(i=0; i<nextFreeIndex; i++){
        if(vetP[i].type == 's'){
            Student *s = (Student*) vetP[i].item;
            if(s->regist == reg){
                printf("\nAluno -> Matrícula: %d, Nome: %s, Curso: %s, Ano de Ingresso: %d\n", s->regist, s->name, s->course, s->year);
            }
        }
        if(vetP[i].type == 't'){
            Teacher *t = (Teacher*) vetP[i].item;
            if(t->regist == reg){
                printf("\nProfessor -> Matrícula: %d, Nome: %s, Salário: %d\n", t->regist, t->name, t->salary);
            }
        }
    }
}

int countStudents(Person *vetP, char *cou){
    int i, count = 0;
    for(i=0; i<nextFreeIndex; i++){
        if(vetP[i].type == 's'){
            Student *s = (Student*) vetP[i].item;
            if(strcmp(s->course, cou) == 0)
                count++;
        }
    }
    return count;
}

int mainMenu(){
    int option;
    printf("\n1- Inserir uma pessoa na lista.");
    printf("\n2- Remover uma pessoa pela matrícula.");
    printf("\n3- Buscar uma pessoa pela matrícula.");
    printf("\n4- Contar número de alunos no curso.");
    printf("\n5- Imprimir professores com maior salário.");
    printf("\n6- Sair\n");
    scanf("%d", &option);
    return option;
}

int main(){
    int option;
    Person vet[N]; 
    vetStart(vet);

    while (option != 6){

        option = mainMenu();
        if(option == 1){
            int opt, r;
            char n[50];
            printf("\n1- Inserir um Aluno.");
            printf("\n2- Inserir um Professor.\n");
            scanf("%d", &opt);
            if(opt == 1){
                int y;
                char c[50];
                printf("\nDigite a matrícula, o nome, o curso e o ano de ingresso.\n");
                scanf("%d %s %s %d", &r, n, c, &y);
                insertStudent(vet, r, n, c, y);
            } else if(opt == 2){
                int s;
                printf("\nDigite a matrícula, o nome e o salário.\n");
                scanf("%d %s %d", &r, n, &s);
                insertTeacher(vet, r, n, s);
            } else
                printf("\nOpção inválida.\n");       
        }
        if(option == 2){
            int r;
            printf("\nDigite a Matrícula.\n");
            scanf("%d", &r);
            removePerson(vet, r);
        }
        if(option == 3){
            int r;
            printf("\nDigite a Matrícula.\n");
            scanf("%d", &r);
            findPerson(vet, r);
        }
        if(option == 4){
            int n;
            char c[50];
            printf("\nDigite o Curso.\n");
            scanf("%s", c);
            n = countStudents(vet, c);
            printf("Existem %d alunos no curso de %s", n, c);
        }
        if(option == 5){
            
        }
        if(option == 6){
            
        }
    }
}