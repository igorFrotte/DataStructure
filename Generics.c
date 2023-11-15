int mainMenu(){
    int option;
    printf("\n1- Inserir uma pessoa na lista.");
    printf("\n2- Remover uma pessoa pela matrícula.");
    printf("\n3- Buscar uma pessoa pela matrícula.");
    printf("\n4- Contar número de alunos no curso.");
    printf("\n5- Imprimir professores com maior salário.");
    printf("\n6- Sair\n");
    scanf("%d", &option);
    return option;
}

int main(){
    int option;

    while (option != 6){

        option = mainMenu();
        if(option == 1){
            
        }
        if(option == 2){
            
        }
        if(option == 3){
            
        }
        if(option == 4){
            
        }
        if(option == 5){
            
        }
        if(option == 6){
            
        }
    }
}