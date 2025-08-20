#include <stdio.h>
#include <stdlib.h>
#define ex2

#ifdef ex1
// Pilha dinâmica
typedef struct Celula
{
    int valor;
    struct Celula *proximo; 
} Celula;

typedef struct
{
    int qtde;
    Celula *topo;
} Pilha;

Celula *criar_celula(int valor){
    Celula *nova = malloc(sizeof(Celula));
    
    nova->proximo = NULL;
    nova->valor = valor;

    return nova;
}

Pilha *criar_pilha(){
    Pilha *nova = malloc(sizeof(Pilha));
    
    nova->qtde = 0;
    nova->topo = NULL;
    
    return nova;
}

void push(int valor, Pilha *pilha){
    Celula *nova = criar_celula(valor);
    
    nova->proximo = pilha->topo;
    pilha->topo = nova;
    pilha->qtde++;
}

void pop(Pilha *pilha){
    if(pilha->topo != NULL){
        Celula *temp  = pilha->topo;
        pilha->topo = pilha->topo->proximo;
        free(temp);
    }
    else{
        printf("underflow\n");
        return;
    }
}

void imprimir(Pilha *pilha){
    Celula *atual = pilha->topo;
    printf("TOPO -> ");
    while (atual != NULL)
    {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("<- BASE\n");
}

int main(int argc, char const *argv[])
{
    Pilha *pilha = criar_pilha();

    for (size_t i = 0; i < 9; i++)
    {
        push(i, pilha);
    }
    
    imprimir(pilha);
    
    // teste pop
    pop(pilha);
    pop(pilha);
    pop(pilha);
    imprimir(pilha);

    for (size_t i = 0; i < 6; i++)
    {
        // remove todos os valores
        pop(pilha);
    }

    imprimir(pilha);

    // teste pop sem nada na pilha
    pop(pilha);
    imprimir(pilha);

    return 0;
}
#endif

#ifdef ex2
// Fila dinâmica
typedef struct Celula
{
    int valor;
    struct Celula *anterior;
    struct Celula *proximo;

} Celula;

typedef struct
{
    int qtde;
    Celula *head;
    Celula *tail;
} Fila;

Celula *criar_celula(int valor){
    Celula *nova = malloc(sizeof(Celula));
    
    nova->anterior = NULL;
    nova->proximo = NULL;
    nova->valor = valor;

    return nova;
}

Fila *criar_fila(){
    Fila *nova = malloc(sizeof(Fila));

    nova->qtde = 0;
    nova->head = NULL;
    nova->tail = NULL;

    return nova;
}

void imprimir(Fila *fila){
    Celula *atual = fila->head;
    printf("INICIO -> ");
    while (atual != NULL)
    {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf("<- FIM\n");
}

void enqueue(int valor, Fila *fila){
    Celula *nova = criar_celula(valor);

    if (fila->tail == NULL && fila->head == NULL){
        fila->head = nova;
        fila->tail = nova;
        fila->qtde++;
    } else{
        nova->anterior = fila->head;
        fila->head->proximo = nova;
        fila->qtde++;
    }
}

int main(int argc, char const *argv[])
{
    Fila *fila = criar_fila();

    for (size_t i = 0; i < 9; i++)
    {
        enqueue(i, fila);
    }

    imprimir(fila);

    return 0;
}
#endif