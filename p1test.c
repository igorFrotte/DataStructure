#include <stdio.h>

int ehMin(int *v, int i, int n){
    if(i>=n)
        return 1;
    int f1 = (2*i+1), f2 = (2*i+2);
    if(f1 < n)
        if(v[f1] < v[i])
            return 0;
    if(f2 < n)
        if(v[f2] < v[i])
            return 0;
    return ehMin(v, f1, n) * ehMin(v, f2, n);
}

int main(){
    int vet[] = {1,2,3,4,5,6,7,8,10};
    printf("\n%d\n", ehMin(vet, 0, 9));
    return 1;
}