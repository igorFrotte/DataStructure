#include <stdio.h>
#include <math.h>

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

#define Max_N 50

int totalElements = 0;

int leftChildIndex(int x){
	int index = (2 * x) + 1;
	if(x >= totalElements || index >= totalElements)
		return -1;
	else
		return index;
}

int rightChildIndex(int x){
	int index = (2 * x) + 2;
	if(x >= totalElements || index >= totalElements)
		return -1;
	else
		return index;
}

int fatherIndex(int x){
	int index = (int) floor((x - 1) / 2);
	if(x <= 0 || x >= totalElements)
		return -1;
	else
		return index;
}

void upAdjust(int *heap, int pos){
	if(pos != -1){
		int dad = fatherIndex(pos);
		if(dad != -1){
			if(heap[pos] < heap[dad]){
				int aux = heap[pos];
				heap[pos] = heap[dad];
				heap[dad] = aux;
				upAdjust(heap, dad);
			}
		}
	}
}

void insertItem(int *heap, int x){
	heap[totalElements] = x;
	totalElements++;
	upAdjust(heap, totalElements-1);
}

void downAdjust(int *heap, int pos){
	if(pos != -1 && leftChildIndex(pos) != -1){
		int youngestChildIndex = leftChildIndex(pos);
		if(rightChildIndex(pos) != -1 && heap[rightChildIndex(pos)] < heap[youngestChildIndex])
			youngestChildIndex = rightChildIndex(pos);
		if(heap[youngestChildIndex] < heap[pos]){
			int aux = heap[pos];
			heap[pos] = heap[youngestChildIndex];
			heap[youngestChildIndex] = aux;
			downAdjust(heap, youngestChildIndex);
		}
	}
}

int removeItem(int *heap) {
	if(totalElements == 0)
		return -1;
	else {
		int result = heap[0];
		heap[0] = heap[totalElements - 1];
		totalElements--;
		downAdjust(heap, 0);
		return result;
	}
}

void printHeap(int *heap) {
    if(totalElements == 0)
        printf("\nHeap Vazio.\n");
    else {
        printf("\n");
        int i;
        for(i = 0; i < totalElements; i++)
            printf("%d ", heap[i]);
        printf("\n");
    }
}

int mainMenu(){
    int option;
    printf("\n1- Inserir um elemento x na Heap.");
    printf("\n2- Remover um elemento.");
    printf("\n3- Imprimir a Heap.");
    printf("\n4- Sair\n");
    scanf("%d", &option);
    return option;
}

int main(){
    int option;
    int heap[Max_N];

    while (option != 4){
    
        option = mainMenu();
        if(option == 1){
            int x;
            printf("\nDigite o valor de x.\n");
            scanf("%d", &x);
            insertItem(heap, x);
        }
        if(option == 2){
            int removedItem = removeItem(heap);
            printf("\nO elemento %d foi removido.\n", removedItem);
        }
        if(option == 3){
            printHeap(heap);
        }
    }
}