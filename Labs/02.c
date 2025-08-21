#include <stdio.h>
#include <stdlib.h>

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
    while (atual != NULL)
    {
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
}

void enqueue(int valor, Fila *fila){
    Celula *nova = criar_celula(valor);

    if (fila->tail == NULL && fila->head == NULL){
        fila->head = nova;
        fila->tail = nova;
    } else{
        fila->tail->proximo = nova;
        nova->anterior = fila->tail;
        fila->tail = nova;
    }
    fila->qtde++;
}

void dequeue(Fila *fila){
    if (fila->qtde == 0 || fila->head == NULL) {
        return;
    }

    Celula *temp = fila->head;

    if (fila->head == fila->tail) {
        fila->head = NULL;
        fila->tail = NULL;
    } else {
        fila->head = fila->head->proximo;
        fila->head->anterior = NULL;
    }

    free(temp);
    fila->qtde--;
}

int main(int argc, char const *argv[])
{
    Fila *fila = criar_fila();
    int nums[] = {10,2,0,4,5,5,6,2,8,1,9};
    size_t len_nums = sizeof(nums) / sizeof(int);

    printf("=== INSERINDO ELEMENTOS ===");
    for (size_t i = 0; i < len_nums; i++)
    {
        printf("\nInserido %d: ", nums[i]);
        enqueue(nums[i], fila);
        imprimir(fila);
    }
    
    printf("\n\n");
    printf("=== REMOVENDO ELEMENTOS ===");
    for (size_t i = 0; i < len_nums; i++)
    {
        printf("\nValor removido: %d, Fila restante: ", nums[i]);
        dequeue(fila);
        imprimir(fila);
    }    

    return 0;
}