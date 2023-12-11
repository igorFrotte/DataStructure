#include "TadMaxHeap.h"
#include <stdio.h>
#include <stdlib.h>

#define N 100

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

typedef struct item {
	int key;
    void *obj;  
}Item;

struct heap {
	int totalElements;
    Item items[N];  
};

TadMaxHeap start(){
    TadMaxHeap maxHeap = (TadMaxHeap)malloc(sizeof(struct heap));
	maxHeap->totalElements = 0; 

    for(int i=0;i<N;i++)
        maxHeap->items[i].obj = NULL;

    return maxHeap;
}

TadMaxHeap destruct(TadMaxHeap maxHeap){
    for(int i=0;i<N;i++)
        free(maxHeap->items[i].obj);
    free(maxHeap);
    return NULL;
}