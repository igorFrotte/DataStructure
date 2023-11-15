#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

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
    struct person *next;
} Person;

void insertPerson(Person **list, void *inf, char type){
    Person *p = (Person*)malloc(sizeof(Person));
    p->type = type;
    p->item = inf;
    p->next = *list;
    *list = p;
}

void insertStudent(Person **list, int reg, char *nam, char *cou, int yea){
    Student *s = (Student*)malloc(sizeof(Student));
    s->regist = reg;
    strcpy(s->name, nam);
    strcpy(s->course, cou);
    s->year = yea;
    insertPerson(list, s, 's');
}

void insertTeacher(Person **list, int reg, char *nam, int sal){
    Teacher *t = (Teacher*)malloc(sizeof(Teacher));
    t->regist = reg;
    strcpy(t->name, nam);
    t->salary = sal;
    insertPerson(list, t, 't');
}

Person* removePerson(Person *list, int reg){
    if(list != NULL){
        if(list->type == 's'){
            Student *s = (Student*) list->item;
            if(s->regist == reg){
                Person *aux = list->next;
                free(s);
                free(list);
                return aux;
            }
        }
        if(list->type == 't'){
            Teacher *t = (Teacher*) list->item;
            if(t->regist == reg){
                Person *aux = list->next;
                free(t);
                free(list);
                return aux;
            }
        }
        list->next = removePerson(list->next, reg);
        return list;
    }
    return NULL;
}

void findPerson(Person *list, int reg){
    if(list != NULL){
        if(list->type == 's'){
            Student *s = (Student*) list->item;
            if(s->regist == reg)
                printf("\nAluno -> Matrícula: %d, Nome: %s, Curso: %s, Ano de Ingresso: %d\n", s->regist, s->name, s->course, s->year);
        }
        if(list->type == 't'){
            Teacher *t = (Teacher*) list->item;
            if(t->regist == reg)
                printf("\nProfessor -> Matrícula: %d, Nome: %s, Salário: %d\n", t->regist, t->name, t->salary);
        }
        findPerson(list->next, reg);
    }
}

void countStudents(Person *list, char *cou, int *count){
    if(list != NULL){
        if(list->type == 's'){
            Student *s = (Student*) list->item;
            if(strcmp(s->course, cou) == 0)
                *count = *count + 1;
        }
        countStudents(list->next, cou, count);
    }
}

void findHigherSalary(Person *list, int *high){
    if(list != NULL){
        if(list->type == 't'){
            Teacher *t = (Teacher*) list->item;
            if(t->salary > *high)
                *high = t->salary;
        }
        findHigherSalary(list->next, high);
    }
}

void printHigherSalary(Person *list, int high){
    if(list != NULL){
        if(list->type == 't'){
            Teacher *t = (Teacher*) list->item;
            if(t->salary == high)
                printf("\nMatrícula: %d, Nome: %s, Salário: %d", t->regist, t->name, t->salary);
        }
        printHigherSalary(list->next, high);
    }
}

void destruct(Person *l){
    if(l != NULL){
        destruct(l->next);
        free(l);
    }
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
    Person *list = NULL;

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
                insertStudent(&list, r, n, c, y);
            } else if(opt == 2){
                int s;
                printf("\nDigite a matrícula, o nome e o salário.\n");
                scanf("%d %s %d", &r, n, &s);
                insertTeacher(&list, r, n, s);
            } else
                printf("\nOpção inválida.\n");       
        }
        if(option == 2){
            int r;
            printf("\nDigite a Matrícula.\n");
            scanf("%d", &r);
            list = removePerson(list, r);
        }
        if(option == 3){
            int r;
            printf("\nDigite a Matrícula.\n");
            scanf("%d", &r);
            findPerson(list, r);
        }
        if(option == 4){
            int n = 0;
            char c[50];
            printf("\nDigite o Curso.\n");
            scanf("%s", c);
            countStudents(list, c, &n);
            printf("\nExistem %d alunos no curso de %s.\n", n, c);
        }
        if(option == 5){
            int high = 0;
            findHigherSalary(list, &high);
            printHigherSalary(list, high);
            printf("\n");
        }
        if(option == 6){
            destruct(list);
        }
    }
}