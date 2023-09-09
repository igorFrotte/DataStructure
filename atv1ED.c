#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int info;
    struct tree *left;
    struct tree *right;
}Tree;

int mainMenu(){
    int option;
    printf("\n1- Ler a árvore de um arquivo\n2- Imprimir a árvore\n3- Verificar se um elemento x existe na árvore\n");
    printf("4- Contar o número de elementos na árvore\n5- Imprimir os nós folhas da árvore\n6- Verificar a árvore está balanceada\n");
    printf("7- Verificar se árvore é cheia\n8- Imprimir o nível de um nó x\n9- Sair\n");
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

char *createFromFile(char *path, Tree **t){
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
        preOrder(t->left);
        printf("%d  ", t->info);
        preOrder(t->right);
    }
}

void postOrder(Tree *t){
    if(t != NULL){
        preOrder(t->left);
        preOrder(t->right);
        printf("%d  ", t->info);
    }
}

//fazer
void inWidth(){

}

// Em Largura, temos uma função que tem auxilio de uma pilha para organizar os nós da arvore.
void ImprimirEmLargura(Tree *arv, int tamanho) {
  Tree **fila;
  int i = 0;
  int f = 1;
  fila = malloc(tamanho * sizeof(Tree *));
  fila[0] = arv;
  while(f > i) {
    arv =  fila[i++];
    printf("%d \n", arv->info);
    if(arv->left != NULL) {
      fila[f++] = arv->left;
    }
    if(arv->right != NULL) {
      fila[f++] = arv->right;
    }
  }
  free(fila);
} 








void printTree(int opt, Tree **t){
    if(opt == 1){
        preOrder(*t);
    } else if(opt == 2){
        inOrder(*t);
    } else if(opt == 3){
        postOrder(*t);
    } else if(opt == 4){
        ImprimirEmLargura(*t, 2);
    }
}

//destruir a arvore

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

int main(){
    int option;
    Tree *tree = NULL; 

    while (option != 9){
    
        option = mainMenu();
        if(option == 1){
            char path[100];
            printf("\nDigite o caminho do arquivo\n");
            scanf("%s", path);
            printf("%s", createFromFile(path, &tree));
        }else if(option == 2){
            int opt;
            printf("\nDigite a opção:\n     1- Pré-ordem\n     2- Em-ordem\n     3- Pós-ordem\n     4- Em largura\n");
            scanf("%d", &opt);
            printTree(opt, &tree);
        }else if(option == 3){
            int x;
            printf("\nDigite o valor do elemento\n");
            scanf("%d", &x);
            if(exist(x, tree) == 0)
                printf("O elemento %d não está presente na árvore", x);
            else
                printf("O elemento %d está presente na árvore", x);
        }else if(option == 4){
            printf("\nA árvore possui %d elementos\n", count(tree));
        }

    }
}

