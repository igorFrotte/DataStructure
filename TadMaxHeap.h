#ifndef TadMaxHeap_h
#define TadMaxHeap_h

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

typedef struct heap *TadMaxHeap;
TadMaxHeap start();
TadMaxHeap destruct(TadMaxHeap maxHeap);
int insertItem(TadMaxHeap maxHeap, int key, void *obj, int sizeObj);
int removeItem(TadMaxHeap maxHeap, int *key, void *obj, int sizeObj);
void printAll(TadMaxHeap maxHeap);

#endif