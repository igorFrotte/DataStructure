#include <stdio.h>

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

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

void queenComb(int *array, int pos, int n){
    int i, j;
    if(pos == n){
        for(i = 0; i < n; i++){
            for(j = i+1; j < n; j++){
                if(array[i] == array[j])
                    return;
                if(array[i] + (j - i) == array[j] || array[i] + (i - j) == array[j])
                    return;
            }
        }
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                if(array[i] == j)
                    printf("1 ");
                else
                    printf("0 ");
            }
            printf("\n");  
        }
        printf("\n");  
    } else {
        for(i = 0; i < n; i++){
            array[pos] = i;
            queenComb(array, pos+1, n);
        }
    }
}

int mainMenu(){
    int option;
    printf("\n1- Todas as Combinações de {a,e,i} de tamanho n, onde os a's > soma(e,i).");
    printf("\n2- Todas as Combinações de {15,31,55,44} de tamanho n, onde a soma é par.");
    printf("\n3- Valor em centavos representado em moedas de 1, 5, 10, 25 e 50 centavos.");
    printf("\n4- Desafio das N-Rainhas onde o valor de n é 8(possível mudar N no código).");
    printf("\n5- Sair\n");
    scanf("%d", &option);
    return option;
}

int main(){
    int option;

    while (option != 5){
    
        option = mainMenu();
        if(option == 1){
            int length, n;
            printf("\nDigite o valor de n.\n");
            scanf("%d", &n);
            printf("\n---Combinação de a, e, i com mais a's---\n\n");
            char chars[] = {'a', 'e', 'i'};
            int array[n];
            length = sizeof(chars)/sizeof(chars[0]);
            moreAsComb(array, 0, n, chars, length);
        }
        if(option == 2){
            int length, n;
            printf("\nDigite o valor de n.\n");
            scanf("%d", &n);
            printf("\n---Combinação de valores pares---\n\n");
            int items[] = {15, 31, 55, 44};
            int array[n];
            length = sizeof(items)/sizeof(items[0]);
            pairsComb(array, 0, n, items, length);
        }
        if(option == 3){
            int value, arrayAux[5];
            printf("\nDigite o valor.\n");
            scanf("%d", &value);
            //printf("\n---Combinação de Moedas---\n\n");
            //coinComb(arrayAux, 0, value);
            printf("\n---Combinação de Moedas Otimizada---\n\n");
            optCoinComb(arrayAux, 0, value);
        }
        if(option == 4){
            int n = 8;
            printf("\n---Problema das N Rainhas---\n\n");
            int array[n];
            queenComb(array, 0, n);
            printf("-> São 92 soluções possíveis!\n\n");
        }
    }
}