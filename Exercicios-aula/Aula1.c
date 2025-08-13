#include <stdio.h>
#include <stdlib.h>
#define ex1

#ifdef ex1
// LDE = Lista Dinamica Encadeada

typedef struct Celula{
    int valor;
    struct Celula *proximo;
} Celula;

typedef struct LDE{
    int qtde;
    Celula *primeiro;
} LDE;

Celula *criar_celula(int valor){
    Celula *nova = malloc(sizeof(Celula));
    nova->valor = valor;
    nova->proximo = NULL;

    return nova;
}

LDE *criar_lista(){
    LDE *nova = malloc(sizeof(LDE));
    nova->qtde = 0;
    nova->primeiro = NULL;

    return nova;
}

void inserir(LDE *lista, int valor){
    Celula *nova = criar_celula(valor);
    Celula *anterior = NULL;
    Celula *atual = lista->primeiro;

    while(atual != NULL && atual->valor < valor){
        anterior = atual;
        atual = atual->proximo;
    }

    if(anterior == NULL){
        nova->proximo = lista->primeiro;
        lista->primeiro = nova;
    }else{
        anterior->proximo = nova;
        nova->proximo = atual;
    }
    lista->qtde++;
}

void remover(LDE *lista, int valor){

}

void imprimir(LDE *lista){
    Celula *atual = lista->primeiro;
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("\n");
}

int main(){
    LDE *lista = criar_lista();

    int i = 0;

    for(i = 9; i >= 0; i--){
        inserir(lista, i);
        imprimir(lista);
    }

    return 0;
}
#endif

#ifdef ex2
// LDDE = Lista Dinamica Duplamente Encadeada

int main(){

    return 0;
}
#endif
