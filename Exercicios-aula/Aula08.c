#include <stdio.h>
#include <limits.h> // usar INT_MAX como "infinito"
#define merge_sort

void print_arr(int *arr, int n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%2d ", arr[i]);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

#ifdef merge_sort

// p -> inicio do vetor
// r -> fim do vetor
// q -> fim da primeira metade do vetor
void Merge(int *V, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int E[n1+1], D[n2+1];

    for (size_t i = 0; i < n1; i++)
    {
        E[i] = V[p + i];
    }
    for (size_t j = 0; j < n2; j++)
    {
        D[j] = V[q + j + 1];
    }

    E[n1] = INT_MAX;
    D[n2] = INT_MAX;

    int i = 0, j = 0;
    for (size_t k = p; k <= r; k++)
    {
        if (E[i] <= D[j])
        {
            V[k] = E[i++];
        }
        else
        {
            V[k] = D[j++];
        }
    }
}

void MergeSort(int *V, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        MergeSort(V, p, q);
        MergeSort(V, q + 1, r);
        Merge(V, p, q, r);
    }
}

int main(int argc, char const *argv[])
{
    int n = 10;
    int arr[] = {8, 2, 1, 6, 7, 0, 3, 5, 4, 9};

    printf("Array desordenado: ");
    print_arr(arr, n);

    MergeSort(arr, 0, n - 1);

    printf("\nArray ordenado:    ");
    print_arr(arr, n);

    return 0;
}
#endif

#ifdef quick_sort
int Partition(int* V, int p, int r){
    int x = V[r];
    int i = p-1;

    for (int j = p; j < r; j++)
    {
        if (V[j] <= x)
        {
            i++;
            // a função swap com XOR nao funciona por que as vezes temos que trocar um mesmo numero
            // e o XOR zera a posição, fazendo com que o array fique zerado
            swap(&V[i], &V[j]);
        }
    }
    swap(&V[i+1], &V[r]);
    return i+1;
}

void QuickSort(int* V, int p, int r){
    if (p < r)
    {
        int q = Partition(V, p, r);
        QuickSort(V,p,q-1);
        QuickSort(V,q+1,r);
    }
}

int main(int argc, char const *argv[])
{
    int n = 10;
    int arr[] = {8, 2, 1, 6, 7, 0, 3, 5, 4, 9};

    printf("Array desordenado: ");
    print_arr(arr, n);

    QuickSort(arr, 0, n-1);

    printf("\nArray ordenado:    ");
    print_arr(arr, n);

    return 0;
}
#endif

#ifdef heap_sort
void MaxHeapify(int* V, int n, int i) {
    int esq = 2*i + 1;
    int dir = 2*i + 2;
    int maior = i;

    if (esq < n && V[esq] > V[maior])
        maior = esq;

    if (dir < n && V[dir] > V[maior])
        maior = dir;

    if (maior != i) {
        swap(&V[i], &V[maior]);
        MaxHeapify(V, n, maior);
    }
}

void BuildMaxHeap(int* V, int n) {
    for (int i = n/2 - 1; i >= 0; i--) {
        MaxHeapify(V, n, i);
    }
}

void HeapSort(int* V, int n) {
    BuildMaxHeap(V, n);

    for (int i = n - 1; i > 0; i--) {
        swap(&V[0], &V[i]);   // move o maior para o fim
        MaxHeapify(V, i, 0);  // restaura a propriedade de heap
    }
}

int main() {
    int n = 10;
    int arr[] = {8, 2, 1, 6, 7, 0, 3, 5, 4, 9};

    printf("Array desordenado: ");
    print_arr(arr, n);

    HeapSort(arr, n);

    printf("\nArray ordenado:    ");
    print_arr(arr, n);

    return 0;
}
#endif