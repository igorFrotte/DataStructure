#include <stddef.h>

typedef struct lista{
    int info;
    struct lista *prox;
}lista;

int Somar(lista *l){
    if(l == NULL)
        return 0;
    return l->info + Somar(l->prox);
}

int Contar(lista *l, int x){
    if(l == NULL)
        return 0;
    else {
        if(l->info == x)
            return 1 + Contar(l->prox, x);
        return Contar(l->prox, x);
    }
}

void Remover(lista **l, int x){
    if(*l != NULL){
        if((*l)->info != x)
            Remover(&((*l)->prox), x);
        else {
            lista *aux = *l;
            *l = (*l)->prox;
            free(aux);
        }
    }
}