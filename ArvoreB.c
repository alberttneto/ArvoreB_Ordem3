#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"
#define ORDEM 3

struct NO{
    int chave[ORDEM-1], contChave, ehRaiz;
    struct NO *filho[ORDEM];
};

// Criar paginas para arvore
ArvB* cria_ArvB(){
    ArvB* raiz;
    raiz = (ArvB*) malloc(sizeof(ArvB));
    if(raiz != NULL){
        raiz->chave[0] = -1;
        raiz->chave[1] = -1;
        raiz->contChave = 0;
        raiz->ehRaiz = 1;
        int i;
        for(i = 0; i < ORDEM; i++){
            raiz->filho[i] = NULL;
        }
    }
    return raiz;
}

//Liberar no e seus filhos
void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    int i;

    // vai em cada filho do nó atual para liberar de forma recursiva
    for(i = 0; i < ORDEM; i++){
        libera_NO(no->filho[i]);
    }

    free(no);
    no = NULL;
}

//Libera a arvore
void libera_ArvB(ArvB* raiz){
    if(raiz == NULL)
        return;
    libera_NO(raiz);//libera nó
    free(raiz);//libera raiz
}

//Verificar se tem elemento na arvore
int busca_ArvB(ArvB *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }

    ArvB *atual = raiz;

    // visita cada nó da arvore em busca do valor igual
    while(atual != NULL){

        int i, posNo;

        for(i = 0; i < ORDEM-1; i++){

            if(atual->chave[i] == valor){
                return 1;
            }else{
                if(valor < atual->chave[i]){
                    posNo = i;
                    break;
                }else if (atual->chave[i] == -1){
                    posNo = i;
                    break;
                }else {
                    posNo = i+1;
                }
            }
        }

        atual = atual->filho[posNo];
    }

    return 0;
}

//Verfica se um determinado nó esta vazio
int ehVazia_ArvB(ArvB *raiz){
    if(raiz->chave[0] == -1)
        return 1;
    return 0;
}

//Conta quantidades de no na arvore
int contaNo_ArvB(ArvB *no, int *cont){

    if(no == NULL){
        return 0;
    }

    int i;
    for(i = 0; i < ORDEM; i++){
        *cont += contaNo_ArvB(no->filho[i], cont);
    }

    return 1;
}

//Chama a contagem de nós da raiz
int totalNo_ArvB(ArvB *raiz){

    if(raiz == NULL){
        return 0;
    }

    int cont = 0;
    contaNo_ArvB(raiz, &cont);

    return cont+1;
}

//Imprimir arvore emOrdem
void emOrdem_ArvB(ArvB *raiz){
    if(raiz == NULL){
        return;
    }
    int i;


    for(i = 0; i < ORDEM-1; i++){
        emOrdem_ArvB(raiz->filho[i]);
        if(raiz->chave[i] != -1){
            printf("%d ", raiz->chave[i]);
        }
    }
    emOrdem_ArvB(raiz->filho[ORDEM-1]);

}

//Imprimir arvore na posOrdem
void posOrdem_ArvB(ArvB *raiz){
    if(raiz == NULL)
        return;

    int i;
    if(raiz != NULL){

        for(i = 0; i < ORDEM; i++){
            posOrdem_ArvB(raiz->filho[i]);
        }


        for(i = 0; i < ORDEM-1; i++){
            if(raiz->chave[i] != -1){
                printf("[%d]", raiz->chave[i]);
            }
        }
        printf("\n");
    }
}

//Retorna quantos filhos tem em um determinado nó
int qtdFilhos(ArvB *raiz){

    int i, cont = 0;

    for(i = 0; i < ORDEM; i++){
        if(raiz->filho[i] != NULL){
            cont++;
        }
    }

    return cont;
}

//Busca por no que o valor está
//Ou busca por nó anterior ao que o valor está
ArvB* buscaNo(ArvB *no, int valor, int op){

    ArvB *noAnt = NULL;

    while(1){

        int i, posNo;
        for(i = 0; i < ORDEM-1; i++){

            if(no->chave[i] == valor){
                return noAnt;
            }else{
                if(valor < no->chave[i]){
                    posNo = i;
                    break;
                }else if (no->chave[i] == -1){
                    posNo = i;
                    break;
                }else {
                    posNo = i+1;
                }
            }
        }
        if(no->filho[posNo] != NULL){
            noAnt = no;
            no = no->filho[posNo];
        }else{
            break;
        }
    }

    if(op == 1){
        return noAnt;
    }
    return no;
}


//Função usada para ordenar os valores da pagina
void ordenaPagina(ArvB *pagina, int valor, int vet[3]){

    vet[0] = pagina->chave[0];
    vet[1] = pagina->chave[1];
    vet[2] = valor;

    if(valor < vet[0]){
        vet[2] = vet[1];
        vet[1] = vet[0];
        vet[0] = valor;
    }else if(valor < vet[1] || vet[1] == -1){
        vet[2] = vet[1];
        vet[1] = valor;
    }
}

void insereNo(ArvB *raiz, ArvB *pagina, int valor);

// Função para dividir a pagina quando estiver cheia
void dividePagina(ArvB *raiz, ArvB *pagina, ArvB *novaPagina,  int valor){


    //nova pagina
    ArvB *novaP1;
    novaP1 = cria_ArvB();
    novaP1->ehRaiz = 0;
    novaP1->contChave += 1;

    //Ordenar valores da pagina
    int vet[3];
    ordenaPagina(pagina, valor, vet);

    //Dividir raiz
    if(pagina->ehRaiz){

        //Quando raiz estiver cheia
        if(pagina->contChave == ORDEM-1){

            ArvB *novaP2;
            novaP2 = cria_ArvB();

            novaP2->ehRaiz = 0;
            novaP2->contChave +=1;
            pagina->contChave -=1;

            //Organizando os filhos da raiz
            if (novaPagina != NULL){

                if(valor < pagina->chave[0]){

                    novaP1->filho[0] = pagina->filho[0];
                    novaP1->filho[1] = novaPagina;
                    novaP2->filho[0] = pagina->filho[1];
                    novaP2->filho[1] = pagina->filho[2];

                } else if(valor < pagina->chave[1]){

                    novaP1->filho[0] = pagina->filho[0];
                    novaP1->filho[1] = pagina->filho[1];
                    novaP2->filho[0] = novaPagina;
                    novaP2->filho[1] = pagina->filho[2];

                }else{

                    novaP1->filho[0] = pagina->filho[0];
                    novaP1->filho[1] = pagina->filho[1];
                    novaP2->filho[0] = pagina->filho[2];
                    novaP2->filho[1] = novaPagina;
                }

                pagina->filho[2] = NULL;
            }

            pagina->chave[1] = -1;
            pagina->chave[0] = vet[1];
            novaP1->chave[0] = vet[0];
            novaP2->chave[0] = vet[2];

            pagina->filho[0] = novaP1;
            pagina->filho[1] = novaP2;

        // Se a raiz não estiver cheia
        }else{

            if(valor < pagina->chave[0]){
                pagina->filho[2] = pagina->filho[1];
                pagina->filho[1] = novaPagina;

            }else{
                pagina->filho[2] = novaPagina;

            }

            insereNo(raiz, pagina, valor);
        }

    //Dividir pagina cheia
    }else {

        //Se a pagina não estiver cheia
        if(pagina->contChave < ORDEM-1){

            if(valor < pagina->chave[0]){
                pagina->filho[2] = pagina->filho[1];
                pagina->filho[1] = novaPagina;

            }else{
                pagina->filho[2] = novaPagina;

            }

            insereNo(raiz, pagina, valor);

        //Pagina cheia chama recursão
        }else{


            if(novaPagina != NULL){

                if(valor < pagina->chave[0]){
                    novaP1->filho[0] = pagina->filho[1];
                    novaP1->filho[1] = pagina->filho[2];
                    pagina->filho[1] = novaPagina;

                }else if(valor > pagina->chave[1]){
                    novaP1->filho[0] = pagina->filho[2];
                    novaP1->filho[1] = novaPagina;

                }else if(valor > pagina->chave[0] && valor < pagina->chave[1]){
                    novaP1->filho[0] = novaPagina;
                    novaP1->filho[1] = pagina->filho[2];
                }
                pagina->filho[2] = NULL;
            }

            pagina->contChave -= 1;
            pagina->chave[1] = -1;
            pagina->chave[0] = vet[0];
            novaP1->chave[0] = vet[2];

            pagina = buscaNo(raiz, pagina->chave[0], 1);

            dividePagina(raiz, pagina, novaP1, vet[1]);
        }
    }
}

//Inserir valor no nó
void insereNo(ArvB *raiz, ArvB *pagina, int valor){

    int aux;
    //Se pagina for vazia insere primeira posição
    if(ehVazia_ArvB(pagina)){
        pagina->chave[0] = valor;
        pagina->contChave += 1;

    //Pagina com 1 elemento insere no proximo
    }else if(pagina->contChave < 2){
        if(valor < pagina->chave[0]){
            aux = pagina->chave[0];
            pagina->chave[0] = valor;
            pagina->chave[1] = aux;

        }else{
            pagina->chave[1] = valor;
        }
        pagina->contChave += 1;

    //pagina cheia, dividi pagina
    }else{

        dividePagina(raiz, pagina, NULL, valor);
    }
}

//chamada da função para inserir valor no nó
int insere_ArvB(ArvB* raiz, int valor){

    if(raiz == NULL || busca_ArvB(raiz, valor)){
        return 0;
    }

    ArvB *pagina;
    pagina = raiz;

    //Inserir na pagina sem filhos
    if (qtdFilhos(raiz) == 0){
        insereNo(raiz, pagina, valor);
        return 1;

    //Se não for raiz sem filhos, procurar no folha
    }else{

        pagina = buscaNo(raiz, valor, 0);

        //enviar raiz, pagina atual, pagina anterior e valor para inserir
        insereNo(raiz, pagina, valor);
    }
    return 1;
}

//Remover elemento de um determinado no
void removeNo(ArvB *raiz, ArvB *pagina, ArvB *pagAnt, int valor){

    if(qtdFilhos(pagina) == 0){
        if(pagina->contChave == ORDEM-1){
            if(valor == pagina->chave[0]){
                pagina->chave[0] = pagina->chave[1];
            }

            pagina->chave[1] = -1;
            pagina->contChave -= 1;
        }
    }
}

// Chama funação para remover chave
int remove_ArvB(ArvB *raiz, int valor){

    if(raiz == NULL || !busca_ArvB(raiz, valor)){
        return 0;
    }

    ArvB *pagAnt, *pagina;
    pagina = raiz;
    pagAnt = NULL;

    pagina = buscaNo(raiz, valor, 0);
    //pagAnt = buscaNo(raiz, valor, 1);

    removeNo(raiz, pagina, pagAnt, valor);

    return 1;
}


