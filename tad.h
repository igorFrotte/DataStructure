#ifndef Queue_H
#define Queue_H

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

typedef struct queue *Queue;
int push(Queue q, int x);
int pop(Queue q, int *x);
void print(Queue q);
Queue start();
Queue destruct(Queue q);
#endif