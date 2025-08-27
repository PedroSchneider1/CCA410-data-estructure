#include <stdio.h>
#include <stdlib.h>

typedef struct Heap
{
    int qtde;
    int *valores;
} Heap;

typedef struct Celula
{
    int valor;
    struct Celula *pai;
    struct Celula *filho_esq;
    struct Celula *filho_dir;
} Celula;

Heap *create_heap(int capacidade){
    Heap *heap = malloc(sizeof(Heap));
    heap->valores = (int*)malloc(capacidade * sizeof(int));
    return heap;
}

void heapify(Heap h, Celula *pai){
    return;
}

int main(int argc, char const *argv[])
{
    // correto: {16,14,10,8,7,9,3,2,4,1}
    int arr[] = {4,1,3,2,16,9,10,14,8,7};
    Heap *heap = create_heap(sizeof(arr));
    return 0;
}
