#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 
*/

typedef struct tree{
    int info;
    int BFac;
    struct tree *left;
    struct tree *right;
}Tree;

int mainMenu(){
    int option;
    printf("\n1- Ler a árvore de um arquivo");
    printf("\n2- Imprimir a árvore");
    printf("\n3- Verificar se um elemento x existe na árvore");
    printf("\n4- Imprimir o nível de um nó x");
    printf("\n5- Imprimir as folhas menores que x");
    printf("\n6- Inserir um nó x na árvore");
    printf("\n7- Remover um nó x da árvore");
    printf("\n8- Sair\n");
    scanf("%d", &option);
    return option;
}

int height(Tree *t){
    if(t!= NULL){
        int hl = height(t->left);
        int hr = height(t->right);
        if(hl > hr)
            return hl + 1;
        return hr + 1;
    }
    return 0;
}

void adjustBFac(Tree *t){
    if(t != NULL){
        int hl = height(t->left);
        int hr = height(t->right);
        t->BFac = hr-hl;
        adjustBFac(t->left);
        adjustBFac(t->right);
    }
}

Tree *createTree(FILE *f){
    char c;
    int n;
    
    fscanf(f, "%c", &c);
    fscanf(f, "%d", &n);

    if(n == -1){
        fscanf(f, "%c", &c);
        return NULL;
    } else {
        Tree *t = (Tree*) malloc(sizeof(Tree));
        t->info = n;
        t->left = createTree(f);
        t->right = createTree(f);
        fscanf(f, "%c", &c);
        return t;
    }
}

char *createFromPath(char *path, Tree **t){
    FILE* fp;
    fp = fopen(path,"rt");
    if (fp == NULL) 
        return "\nErro na abertura do arquivo!\n";
    *t = createTree(fp);
    adjustBFac(*t);
    fclose(fp);
    return "\nArvore criada com sucesso!\n";
}

void preOrder(Tree *t){
    if(t != NULL){
        printf("%d  ", t->info);
        preOrder(t->left);
        preOrder(t->right);
    }
}

void inOrder(Tree *t){
    if(t != NULL){
        inOrder(t->left);
        printf("%d  ", t->info);
        inOrder(t->right);
    }
}

void postOrder(Tree *t){
    if(t != NULL){
        postOrder(t->left);
        postOrder(t->right);
        printf("%d  ", t->info);
    }
}

void printLvl(Tree *t, int c, int lvl){
    if(t != NULL){
        if(c == lvl)
            printf("%d  ", t->info);
        else {
            printLvl(t->left, c+1, lvl);
            printLvl(t->right, c+1, lvl);
        }
    }
}

void inWidth(Tree *t){
    int i;
    for(i=0; i<height(t); i++){
        printLvl(t, 0, i);
    }
}

void printTree(int opt, Tree *t){
    if(opt == 1){
        preOrder(t);
    } else if(opt == 2){
        inOrder(t);
    } else if(opt == 3){
        postOrder(t);
    } else if(opt == 4){
        inWidth(t);
    }
}

int exist(int x, Tree *t){
    if(t != NULL){
        if(t->info == x)
            return 1;
        if(x < t->info)
            return exist(x, t->left);
        else
            return exist(x, t->right);
    }
    return 0;
}

void printLeavesSmallerThan(int x, Tree *t){
    if(t != NULL){
        if(t->left == NULL && t->right == NULL && t->info < x)
            printf("%d ", t->info);
        if(x < t->info)
            printLeavesSmallerThan(x, t->left);
        else {
            printLeavesSmallerThan(x, t->left);
            printLeavesSmallerThan(x, t->right);
        }
    }
}

int lvlOf(int x, Tree *t, int n){
    if(t == NULL)
        return -1;
    if(t->info == x)
        return n;
    if(x < t->info)
        return lvlOf(x, t->left, n+1);
    else
        return lvlOf(x, t->right, n+1); 
}

void destruct(Tree *t){
    if(t != NULL){
        destruct(t->left);
        destruct(t->right);
        free(t);
    }
}

// ----------------------------------------------------------

Tree *simpleLeftRot(Tree *t){
    Tree *a = t;
    Tree *b = a->right;
    a->right = b->left;
    b->left = a;
    if(b->BFac == 1){
        a->BFac = 0;
        b->BFac = 0;
    } else {
        a->BFac = 1;
        b->BFac = -1;
    }
    t = b;
    return t;
}

Tree *doubleLeftRot(Tree *t){
    Tree *a = t;
    Tree *c = a->right;
    Tree *b = c->left; 
    c->left = b->right;
    a->right = b->left;
    b->left = a;
    b->right = c;
    switch(b->BFac){
        case -1:
            a->BFac = 0;
            c->BFac = 1;
            break;
        case 0:
            a->BFac = 0;
            c->BFac = 0;
            break;
        case +1:
            a->BFac = -1;
            c->BFac = 0;
            break;
    }
    b->BFac = 0;
    t = b;
    return t;
}

Tree *leftRot(Tree *t){
    if(t->right->BFac == -1)
        t = doubleLeftRot(t);
    else
        t = simpleLeftRot(t);
    return t;
}

// ----------------------------------------------------------

Tree *simpleRightRot(Tree *t){
    Tree *a = t->left;
    Tree *b = t;
    b->left = a->right;
    a->right = b;
    if(a->BFac == -1){
        a->BFac = 0;
        b->BFac = 0;
    } else {
        a->BFac = 1;
        b->BFac = -1;
    }
    t = a;
    return t;
}

Tree *doubleRightRot(Tree *t){
    Tree *c = t;
    Tree *a = c->left;
    Tree *b = a->right;
    c->left = b->right;
    a->right = b->left;
    b->left = a;
    b->right = c;
    switch(b->BFac){
        case -1:
            a->BFac = 0;
            c->BFac = 1;
            break;
        case 0:
            a->BFac = 0;
            c->BFac = 0;
            break;
        case +1:
            a->BFac = -1;
            c->BFac = 0;
            break;
    }
    b->BFac = 0;
    t = b;
    return t;
}

Tree *rightRot(Tree *t){
    if(t->left->BFac == 1)
        t = doubleRightRot(t);
    else
        t = simpleRightRot(t);
    return t;
}

// ----------------------------------------------------------

Tree *insertItem(int x, Tree *t,  int *hChanged){
    if(t == NULL){
        t = (Tree*) malloc (sizeof(Tree));
        t->info = x;
        t->left = NULL;
        t->right = NULL;
        t->BFac = 0;
        *hChanged = 1;
    } else {
        if(x <= t->info){
            t->left = insertItem(x, t->left, hChanged);
            if(*hChanged == 1){
                switch(t->BFac){
                    case -1:
                        t = rightRot(t);
                        *hChanged = 0;
                        break;
                    case 0:
                        t->BFac = -1;
                        *hChanged = 1;
                        break;
                    case +1:
                        t->BFac = 0;
                        *hChanged = 0;
                        break;
                }
            }
        } else {
            t->right = insertItem(x, t->right, hChanged);
            if(*hChanged == 1){
                switch(t->BFac){
                    case -1:
                        t->BFac = 0;
                        *hChanged = 0;
                        break;
                    case 0:
                        t->BFac = +1;
                        *hChanged = 1;
                        break;
                    case +1:
                        t = leftRot(t);
                        *hChanged = 0;
                        break;
                }
            }
        }
    }
    return t;
}

// ----------------------------------------------------------

Tree *removeItem(int x, Tree *t, int *hChanged){
    if(t != NULL){
        if(t->info == x){
            if(t->left == NULL && t->right == NULL){
                free(t);
                *hChanged = 1;
                return NULL;
            }
            else if(t->left == NULL || t->right == NULL){
                Tree *aux;
                if(t->left == NULL)
                    aux = t->right;
                else
                    aux = t->left;
                free(t);
                *hChanged = 1;
                return aux;
            } else {
                Tree *majorLeft = t->left;
                while(majorLeft->right != NULL)
                    majorLeft = majorLeft->right;
                t->info = majorLeft->info;
                t->left = removeItem(t->info, t->left, hChanged);
                if(*hChanged == 1){
                    switch(t->BFac){
                        case -1:
                            t->BFac = 0;
                            *hChanged = 1;
                            break;
                        case 0:
                            t->BFac = 1;
                            *hChanged = 0;
                            break;
                        case +1:
                            int aux = t->right->BFac;
                            t = leftRot(t);
                            if(aux == 0)
                                *hChanged = 0;
                            else
                                *hChanged = 1;
                            break;
                    }
                }
            }
        }
        else if(x < t->info){
            t->left = removeItem(x, t->left, hChanged);
            if(*hChanged == 1){
                switch(t->BFac){
                    case -1:
                        t->BFac = 0;
                        *hChanged = 1;
                        break;
                    case 0:
                        t->BFac = 1;
                        *hChanged = 0;
                        break;
                    case +1:
                        int aux = t->right->BFac;
                        t = leftRot(t);
                        if(aux == 0)
                            *hChanged = 0;
                        else
                            *hChanged = 1;
                        break;
                }
            }
        } else {
            t->right = removeItem(x, t->right, hChanged);
            if(*hChanged == 1){
                switch(t->BFac){
                    case +1:
                        t->BFac = 0;
                        *hChanged = 1;
                        break;
                    case 0:
                        t->BFac = -1;
                        *hChanged = 0;
                        break;
                    case -1:
                        int aux = t->left->BFac;
                        t = rightRot(t);
                        if(aux == 0)
                            *hChanged = 0;
                        else
                            *hChanged = 1;
                        break;
                }
            }
        }
    }
    return t;
}

// ----------------------------------------------------------

int main(){
    int option;
    Tree *tree = NULL; 

    while (option != 8){
    
        option = mainMenu();
        if(option == 1){
            char path[100];
            printf("\nDigite o caminho do arquivo\n");
            scanf("%s", path);
            printf("%s", createFromPath(path, &tree));
        }
        if(option == 2){
            int opt;
            printf("\nDigite a opção:\n     1- Pré-ordem\n     2- Em-ordem\n     3- Pós-ordem\n     4- Em largura\n");
            scanf("%d", &opt);
            printTree(opt, tree);
        }
        if(option == 3){
            int x;
            printf("\nDigite o valor do elemento\n");
            scanf("%d", &x);
            if(exist(x, tree) == 0)
                printf("\nO elemento %d não está presente na árvore\n", x);
            else
                printf("\nO elemento %d está presente na árvore\n", x);
        }
        if(option == 4){
            int x;
            printf("\nDigite o nó\n");
            scanf("%d", &x);
            if(exist(x ,tree) != 0)
                printf("\nO nó %d está no nível %d\n", x, lvlOf(x, tree, 0));
            else
                printf("\nO elemento %d não está presente na árvore\n", x);
        }
        if(option == 5){
            int x;
            printf("\nDigite o valor do elemento\n");
            scanf("%d", &x);
            printf("\nOs nós folhas da árvore menores que %d são: ", x);
            printLeavesSmallerThan(x, tree);
            printf("\n");
        }
        if(option == 6){
            int x;
            int hChanged = 0;
            printf("\nDigite o valor do elemento\n");
            scanf("%d", &x);
            tree = insertItem(x, tree, &hChanged);
        }
        if(option == 7){
            int x;
            int hChanged = 0;
            printf("\nDigite o valor do elemento\n");
            scanf("%d", &x);
            if(exist(x, tree) == 0)
                printf("\nO elemento %d não está presente na árvore\n", x);
            else
                tree = removeItem(x, tree, &hChanged);
        }
        if(option == 8){
            destruct(tree);
        }
    }
}

