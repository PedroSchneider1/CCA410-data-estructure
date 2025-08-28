#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct Heap
{
    int capacity;
    int size;
    int *values;
} Heap;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

Heap *create_heap(int n){
    Heap *heap = malloc(sizeof(Heap));
    heap->capacity = n;
    heap->size = 0;
    heap->values = (int*)malloc(n * sizeof(int));
    return heap;
}

void heapify(Heap *h, int i){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < h->size && h->values[left] > h->values[largest])
        largest = left;
    if (right < h->size && h->values[right] > h->values[largest])
        largest = right;
    if (largest != i) {
        swap(&h->values[i], &h->values[largest]);
        heapify(h, largest);
    }
}

void heapify_up(Heap *h, int i){
    if (h->size <= 0)
        return;

    int father = (i-1)/2;

    // corrige o heap se violou a regra
    if(h->values[father] < h->values[i]) {
        swap(&h->values[i], &h->values[father]);
        heapify_up(h, father);
    }
}

void build_heap(Heap *h){
    for (int i = (h->size - 1) / 2; i >= 0; i--)
        heapify(h, i);
}

void insert(Heap *h, int value){
    if (h->size == h->capacity) {
        printf("Heap overflow\n");
        return;
    }

    h->size++;
    int i = h->size - 1;
    h->values[i] = value;

    heapify_up(h, i);
}

int extract_max(Heap *h){
    if (h->size <= 0)
        return INT_MIN;
    if (h->size == 1) {
        h->size--;
        return h->values[0];
    }

    int root = h->values[0];
    h->values[0] = h->values[h->size - 1];
    h->size--;
    heapify(h, 0);

    return root;
}

void print_heap(Heap* h)
{
    for (int i = 0; i < h->size; ++i)
        printf("%d ", h->values[i]);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    // correto: {16,14,10,8,7,9,3,2,4,1}
    int arr[] = {4,1,3,2,16,9,10,14,8,7};
    Heap *heap = create_heap(10);
    
    for(size_t i = 0; i < 10; i++){
        heap->values[i] = arr[i];
    }
    heap->size = 10;

    printf("Heap antes de construir:\n");
    print_heap(heap);

    build_heap(heap);

    printf("\nHeap depois de construir:\n");
    print_heap(heap);

    heap->capacity += 1;
    insert(heap, 15);

    printf("\nHeap depois de inserir 15:\n");
    print_heap(heap);

    printf("\nExtraindo o maximo: %d\n", extract_max(heap));
    printf("Heap depois de extrair o maximo:\n");
    print_heap(heap);

    free(heap);
    return 0;
}