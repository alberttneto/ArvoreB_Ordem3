#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"
#include "ArvoreB.h"

//Tratamento de erro das funcoes
void trataErro(int erro){

    if(erro){
        printf("Comando executado!\n");
    }else{
        printf("Erro ao executar comando!\n");
    }
}

//Interface com o usuario
void menu(){

    ArvB *arv;
    arv = cria_ArvB();
    int repete = 1;

    while(repete){

        int op, valor, teste;
        printf("\n\nDigite uma opcao:\n--------------"
               "\n1-Insetir Elemento"
               "\n2-Remove Elemento"
               "\n3-Busca Elemento"
               "\n4-Verifica se esta vazia"
               "\n5-Total de no"
               "\n6-Arvore em Ordem"
               "\n7-Arvore pos Ordem"
               "\n8-Sair\n\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                printf("Informe valor:");
                scanf("%d", &valor);
                teste = insere_ArvB(arv, valor);
                trataErro(teste);
            break;
            case 2:
                printf("Informe valor:");
                scanf("%d", &valor);
                printf("Funcao esta Incompleta!\n");
                teste = remove_ArvB(arv, valor);
                trataErro(teste);
            break;
            case 3:
                printf("Informe valor:");
                scanf("%d", &valor);
                teste = busca_ArvB(arv, valor);
                if(teste){
                    printf("Valor esta na arvore!\n");
                }else{
                    printf("Valor nao esta na arvore!\n");
                }
            break;
            case 4:
                teste = ehVazia_ArvB(arv);
                if(teste){
                    printf("Arvore esta vazia!\n");
                }else{
                    printf("Arvore nao esta vazia!");
                }
            break;
            case 5:
                teste = totalNo_ArvB(arv);
                printf("Quantidade de no eh: %d\n", teste);
            break;
            case 6:
                printf("Arvore em ordem: \n =================\n");
                emOrdem_ArvB(arv);
            break;
            case 7:
                printf("Arvore pos ordem: \n ================\n");
                posOrdem_ArvB(arv);
            break;
            case 8:
                printf("Encerrando!\n");
                repete = 0;
            break;
            default:
                printf("Opcao incorreta! Tente novamente.\n");
            break;
        }
    }

    //Liberando arvore
    libera_ArvB(arv);
}


int main(){

    int op;
    printf("Digite uma opcao:\n--------------"
           "\n1-Criar Arvore B"
           "\n2-Sair\n");
    scanf("%d", &op);

    if(op == 1){
        menu();
    }else{
        printf("Encerrando!.\n");
    }

    return 0;

}
