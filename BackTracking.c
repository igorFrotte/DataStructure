#include <stdio.h>

void moreAsComb(int *array, int pos, int n, char *items, int len){
    int i;
    if(pos == n){
        int count = 0;
        for(i = 0; i < n; i++){
            if(array[i] == 'a')
                count++;
        }
        if(count > n/2){
            for(i = 0; i < n; i++)
                printf("%c ", array[i]);
            printf("\n");
        }
    } else {
        for(i = 0; i < len; i++){
            array[pos] = items[i];
            moreAsComb(array, pos+1, n, items, len);
        }
    }
}

void pairsComb(int *array, int pos, int n, int *items, int len){
    int i;
    if(pos == n){
        int sum = 0;
        for(i = 0; i < n; i++)
            sum += array[i];
        if(sum%2 == 0){
            for(i = 0; i < n; i++)
                printf("%d ", array[i]);
            printf("\n");
        }
    } else {
        for(i = 0; i < len; i++){
            array[pos] = items[i];
            pairsComb(array, pos+1, n, items, len);
        }
    }
}

void coinComb(int *array, int pos, int value){
    int i;
    if(pos == 5){
        int cents[] = {1, 5, 10, 25, 50}, sum = 0;
        for(i = 0; i < 5; i++)
            sum += array[i] * cents[i];
        if(sum == value){
            for(i = 0; i < 5; i++)
                printf("%d de %d, ", array[i], cents[i]);
            printf("\n");  
        }
    } else {
        for(i = 0; i <= value; i++){
            array[pos] = i;
            coinComb(array, pos+1, value);
        }
    }
}

void optCoinComb(int *array, int pos, int value){
    int i, cents[] = {1, 5, 10, 25, 50};
    if(pos == 5){
        int sum = 0;
        for(i = 0; i < 5; i++)
            sum += array[i] * cents[i];
        if(sum == value){
            for(i = 0; i < 5; i++)
                printf("%d de %d, ", array[i], cents[i]);
            printf("\n");  
        } 
    } else {
        for(i = 0; i <= value/cents[pos]; i++){
            array[pos] = i;
            optCoinComb(array, pos+1, value);
        }
    }
}

int main(){
    // Changeable
    int n = 3, array[n], length;
    
    printf("\n---Combinação de a, e, i com mais a's---\n\n");
    char chars[] = {'a', 'e', 'i'};
    length = sizeof(chars)/sizeof(chars[0]);
    moreAsComb(array, 0, n, chars, length);

    
    printf("\n---Combinação de valores pares---\n\n");
    int items[] = {15, 31, 55, 44};
    length = sizeof(items)/sizeof(items[0]);
    pairsComb(array, 0, n, items, length);


    printf("\n---Combinação de Moedas---\n\n");
    int arrayAux[5], value = 12;
    coinComb(arrayAux, 0, value);

    printf("\n---Combinação de Moedas Otimizada---\n\n");
    optCoinComb(arrayAux, 0, value);
}