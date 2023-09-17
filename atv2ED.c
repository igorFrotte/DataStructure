#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 
    Aluno: Igor Frotté Pedro
    Matrícula: 123060011 

    OBS: o pow() deu problema na inclusão da lib math.h, precisei compilar com o -lm: gcc atv1ED.c -o atv1ED -lm
*/

typedef struct tree{
    int info;
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
        return exist(x, t->left) || exist(x, t->right);
    }
    return 0;
}

void countLeaves(Tree *t){
    if(t != NULL){
        if(t->left == NULL && t->right == NULL)
            printf("%d ", t->info);
        countLeaves(t->left);
        countLeaves(t->right);
    }
}

int lvlOf(int x, Tree *t, int n){
    if(t == NULL)
        return -1;
    if(t->info == x)
        return n;
    int vl = lvlOf(x, t->left, n+1);
    int vr = lvlOf(x, t->right, n+1);
    if(vl == -1 || vr == -1)
        return vl + vr + 1;
    else
        return vl;
}

void destruct(Tree *t){
    if(t != NULL){
        destruct(t->left);
        destruct(t->right);
        free(t);
    }
}


//ver
Tree *insert(int x, Tree *t){
    if(t == NULL){
        Tree *aux = (Tree *)malloc(sizeof(Tree));
        aux->left = NULL;
        aux->right = NULL;
        return aux;
    } else {
        if(x <= t->info)
            t->left = insert(x, t->left);
        else
            t->right = insert(x, t->right);
    }
    return t;
}

//ver
Tree *remove(int x, Tree *t){
    if(t->info == x){
        if(t->left == NULL && t->right == NULL){
            free(t);
            return NULL;
        } else if(t->left == NULL || t->right == NULL){
            Tree *aux;
            if(t->left == NULL)
                aux = t->right;
            else
                aux = t->left;
            free(t);
            return aux;
        } else {
            Tree *aux = t->left;
            while(aux->right != NULL)
                aux = aux->right;
            t->info = aux->info;
            t->left = remove(aux->info, t->left);
        }
    } else if(x < t->info) 
        t->left = remove(x, t->left);
    else
        t->right = remove(x, t->right);
    return t;
}

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
            printf("\nOs nós folhas da árvore são: ");
            countLeaves(tree);
            printf("\n");
        }
        if(option == 6){
            //inserir
        }
        if(option == 7){
            //remover - valor existe
        }
        if(option == 8){
            destruct(tree);
        }
    }
}

