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
    printf("\n1- Ler a árvore de um arquivo\n2- Imprimir a árvore\n3- Verificar se um elemento x existe na árvore\n");
    printf("4- Contar o número de elementos na árvore\n5- Imprimir os nós folhas da árvore\n6- Verificar se a árvore está balanceada\n");
    printf("7- Verificar se a árvore é cheia\n8- Imprimir o nível de um nó x\n9- Sair\n");
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

int count(Tree *t){
    if(t != NULL){
        return 1 + count(t->left) + count(t->right);
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

int isBalanced(Tree *t){
    if(t != NULL){
        if(abs(height(t->left) - height(t->right)) > 1)
            return 0;
        return isBalanced(t->left) * isBalanced(t->right);
    }
    return 1;
}

int isFull(Tree *t){
    int result = (int) (pow(2, height(t)) - 1);
    if(result == count(t))  
        return 1; 
    return 0;
}

int lvlOf(int x, Tree *t, int n){
    if(t == NULL)
        return 0;
    if(t->info == x){
        return n;
    }
    return lvlOf(x, t->left, n+1) + lvlOf(x, t->right, n+1);
}

Tree *destruct(Tree *t){
    if(t != NULL){
        t->left = destruct(t->left);
        t->right = destruct(t->right);
        free(t);
    }
    return NULL;
}

int main(){
    int option;
    Tree *tree = NULL; 

    while (option != 9){
    
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
        if(option == 4)
            printf("\nA árvore possui %d elementos\n", count(tree));
        if(option == 5){
            printf("\nOs nós folhas da árvore são: ");
            countLeaves(tree);
            printf("\n");
        }
        if(option == 6){
            if(isBalanced(tree) == 0)
                printf("\nA árvore não é balanceada\n");
            else
                printf("\nA árvore é balanceada\n");
        }
        if(option == 7){
            if(isFull(tree) == 0)
                printf("\nA árvore não é cheia\n");
            else
                printf("\nA árvore é cheia\n");
        }
        if(option == 8){
            int x;
            printf("\nDigite o nó\n");
            scanf("%d", &x);
            if(exist(x ,tree) != 0)
                printf("\nO nó %d está no nível %d\n", x, lvlOf(x, tree, 0));
            else
                printf("\nO elemento %d não está presente na árvore\n", x);
        }
        if(option == 9){
            destruct(tree);
        }
    }
}

