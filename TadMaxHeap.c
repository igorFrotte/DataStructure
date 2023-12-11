#include "TadMaxHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

int full(TadMaxHeap maxHeap){
    return maxHeap->totalElements == N;
}

int leftChildIndex(int totalElements, int x){
	int index = (2 * x) + 1;
	if(x >= totalElements || index >= totalElements)
		return -1;
	else
		return index;
}

int rightChildIndex(int totalElements, int x){
	int index = (2 * x) + 2;
	if(x >= totalElements || index >= totalElements)
		return -1;
	else
		return index;
}

int fatherIndex(int totalElements, int x){
	int index = (int) floor((x - 1) / 2);
	if(x <= 0 || x >= totalElements)
		return -1;
	else
		return index;
}

void upAdjust(TadMaxHeap maxHeap, int pos){
	if(pos != -1){
        Item *heap = maxHeap->items;
		int dad = fatherIndex(maxHeap->totalElements, pos);
		if(dad != -1){
			if(heap[pos].key > heap[dad].key){
				Item aux = heap[pos];
				heap[pos] = heap[dad];
				heap[dad] = aux;
				upAdjust(maxHeap, dad);
			}
		}
	}
}

int insertItem(TadMaxHeap maxHeap, int key, void *obj, int sizeObj){
	if(full(maxHeap))
		return 0;

    maxHeap->items[maxHeap->totalElements].key = key; 
    maxHeap->items[maxHeap->totalElements].obj = (void*)malloc(sizeObj); 
    memcpy(maxHeap->items[maxHeap->totalElements].obj, obj, sizeObj);
	maxHeap->totalElements++;

    upAdjust(maxHeap, maxHeap->totalElements-1);

	return 1;
}

int empty(TadMaxHeap maxHeap){
    return maxHeap->totalElements == 0;
}

void downAdjust(TadMaxHeap maxHeap, int pos){
	if(pos != -1 && leftChildIndex(maxHeap->totalElements, pos) != -1){
        Item *heap = maxHeap->items;
		int olderChildIndex = leftChildIndex(maxHeap->totalElements, pos);
		if(rightChildIndex(maxHeap->totalElements, pos) != -1 && heap[rightChildIndex(maxHeap->totalElements, pos)].key > heap[olderChildIndex].key)
			olderChildIndex = rightChildIndex(maxHeap->totalElements, pos);
		if(heap[olderChildIndex].key > heap[pos].key){
			Item aux = heap[pos];
			heap[pos] = heap[olderChildIndex];
			heap[olderChildIndex] = aux;
			downAdjust(maxHeap, olderChildIndex);
		}
	}
}

int removeItem(TadMaxHeap maxHeap, int *key, void *obj, int sizeObj){
	if(empty(maxHeap))
		return 0;

    Item result = maxHeap->items[0];
    *key = result.key;
    memcpy(obj, result.obj, sizeObj); 
    maxHeap->items[0] = maxHeap->items[maxHeap->totalElements-1];
    free(maxHeap->items[maxHeap->totalElements-1].obj);
    maxHeap->items[maxHeap->totalElements-1].obj = NULL;
    
    downAdjust(maxHeap, 0);
    maxHeap->totalElements--;
	
    return 1;
}

void printAll(TadMaxHeap maxHeap, void *f(void *)){ 
    if(empty(maxHeap))
        printf("\nLista Vazia.\n");
    else {
        printf("\n");
        for(int i = 0; i < maxHeap->totalElements; i++){
            printf("Chave: %d ", maxHeap->items[i].key);
            printf("Item: ");
            f(maxHeap->items[i].obj);
            printf("\n");
        }
        printf("\n");
    }
}

int findIndextem(TadMaxHeap maxHeap, int key, int index){
    if(index == -1)
        return 0;
    if(maxHeap->items[index].key == key)
        return index;

    int child = findIndextem(maxHeap, key, rightChildIndex(maxHeap->totalElements, index));
    if(child != 0)
        return child;
    
    child = findIndextem(maxHeap, key, leftChildIndex(maxHeap->totalElements, index));
    if(child != 0)
        return child;
    
    return -1;
}

int exist(TadMaxHeap maxHeap, int key){
    return !(findIndextem(maxHeap, key, 0) == -1);
}

void printItem(TadMaxHeap maxHeap, int key, void *f(void *)){ 
    if(!exist(maxHeap, key))
        printf("\nItem não encontrado.\n");
    else {
        Item item = maxHeap->items[findIndextem(maxHeap, key, 0)];
        printf("\n%d\n", item.key);
        f(item.obj);
        printf("\n");
    }
}

