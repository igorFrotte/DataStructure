#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

#define N 100

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

struct queue {
	int *vet;
	int init;
	int end;
	int len;
};

Queue start() {
	Queue q = (Queue)malloc(sizeof(struct queue));
	q->vet = (int *)malloc(N * sizeof(int)); 
	q->init = 0;
	q->end = -1;
	q->len = 0;
	return q;
}

Queue destruct(Queue q) {
	free(q->vet); 
	free(q);
    return NULL;
}

int full(Queue q) {
	return (q->len == N - 1);
}

int push(Queue q, int x) {
	if(full(q))
		return 0;
	q->end++;
	q->vet[q->end] = x;
	q->len++;
	return 1;
}

int empty(Queue q) {
	return (q->len == 0);
}

int pop(Queue q, int *x) {
	if(empty(q))
		return 0;
	*x = q->vet[q->init];
	q->init++;
	if(q->init == N)
		q->init = 0;
	q->len--;
	return 1;
}

void print(Queue q) {
	printf("\nElementos: ");
	for (int i = q->init; i <= q->end; i++)
		printf("%d ", q->vet[i]);
}