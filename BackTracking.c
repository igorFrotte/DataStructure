#include <stdio.h>

void combMoreAs(int *array, int pos, int n, char *items, int len){
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
            combMoreAs(array, pos+1, n, items, len);
        }
    }
}

void combPairs(int *array, int pos, int n, int *items, int len){
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
            combPairs(array, pos+1, n, items, len);
        }
    }
}

int main(){
    // Changeable
    int n = 3, array[3], items[] = {15, 31, 55, 44}, length;
    char chars[] = {'a', 'e', 'i'};

    // More a's
    length = sizeof(chars)/sizeof(chars[0]);
    combMoreAs(array, 0, n, chars, length);

    // Only pairs
    length = sizeof(items)/sizeof(items[0]);
    combPairs(array, 0, n, items, length);
    
    
}