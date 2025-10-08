#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int comparisons;
    int swaps;
    int memory_allocations;
    char algorithm_name[20];
} PerformanceStats;

// ========================================
// MERGE SORT
// ========================================

void merge(int V[], int p, int q, int r, PerformanceStats *stats) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int E[n1+1], D[n2+1];
    stats->memory_allocations++; // Contabiliza as alocações dos arrays temporários

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
    stats->memory_allocations++; // Contabiliza as sentinelas

    int i = 0, j = 0;
    for (size_t k = p; k <= r; k++)
    {
        stats->comparisons++;
        if (E[i] <= D[j])
        {
            stats->swaps++;
            V[k] = E[i++];
        }
        else
        {
            stats->swaps++;
            V[k] = D[j++];
        }
    }
}

void mergeSort_recursive(int V[], int p, int r, PerformanceStats *stats) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort_recursive(V, p, q, stats);
        mergeSort_recursive(V, q + 1, r, stats);
        merge(V, p, q, r, stats);
    }
}

void merge_sort(int V[], int tamanho, PerformanceStats *stats) {
    strcpy(stats->algorithm_name, "Merge Sort");
    stats->comparisons = 0;
    stats->swaps = 0;
    stats->memory_allocations = 0;
    mergeSort_recursive(V, 0, tamanho - 1, stats);
}

// ========================================
// QUICK SORT
// ========================================

void trocar(int *a, int *b, PerformanceStats *stats) {
    int temp = *a;
    *a = *b;
    *b = temp;
    stats->swaps++;
}

int partition(int V[], int p, int r, PerformanceStats *stats) {
    int x = V[r];
    int i = p-1;

    for (int j = p; j < r; j++)
    {
        stats->comparisons++;
        if (V[j] <= x)
        {
            i++;
            trocar(&V[i], &V[j], stats);
        }
    }
    trocar(&V[i+1], &V[r], stats);
    return i+1;
}

void quickSort_recursive(int V[], int p, int r, PerformanceStats *stats) {
    if (p < r) {
        int q = partition(V, p, r, stats);
        quickSort_recursive(V, p, q-1, stats);
        quickSort_recursive(V, q+1, r, stats);
    }
}

void quick_sort(int V[], int tamanho, PerformanceStats *stats) {
    strcpy(stats->algorithm_name, "Quick Sort");
    stats->comparisons = 0;
    stats->swaps = 0;
    stats->memory_allocations = 0;
    quickSort_recursive(V, 0, tamanho - 1, stats);
}

// ========================================
// HEAP SORT (Versão fiel ao anexo - índices 1-based)
// ========================================

// Estrutura para representar o heap com tamanho e heapSize
typedef struct {
    int *dados;
    int tamanho;
    int heapSize;
} Heap;

// Função para trocar dois elementos no heap
void trocar_heap(int *a, int *b, PerformanceStats *stats) {
    int temp = *a;
    *a = *b;
    *b = temp;
    stats->swaps++;
}

// Função MaxHeapify - mantém a propriedade do max-heap
void maxHeapify(Heap *heap, int i, PerformanceStats *stats) {
    int esq = 2*i + 1;
    int dir = 2*i + 2;
    int maior = i;

    if (esq < heap->heapSize) {
        stats->comparisons++;
        if (heap->dados[esq] > heap->dados[maior])
            maior = esq;
    }

    if (dir < heap->heapSize) {
        stats->comparisons++;
        if (heap->dados[dir] > heap->dados[maior])
            maior = dir;
    }

    if (maior != i) {
        trocar_heap(&heap->dados[i], &heap->dados[maior], stats);
        maxHeapify(heap, maior, stats);
    }
}

// Função BuildMaxHeap - constrói um max-heap a partir do array
void buildMaxHeap(Heap *heap, PerformanceStats *stats) {
    for (int i = (heap->heapSize / 2) - 1; i >= 0; i--) {
        maxHeapify(heap, i, stats);
    }
}

// Função HeapSort - algoritmo principal de ordenação
void heapSort_heap(Heap *heap, PerformanceStats *stats) {
    buildMaxHeap(heap, stats);

    for (int i = heap->heapSize - 1; i > 0; i--) {
        trocar_heap(&heap->dados[0], &heap->dados[i], stats);   // move o maior para o fim
        heap->heapSize--;
        maxHeapify(heap, 0, stats);
    }
}

// Função para criar um heap a partir de um array comum (índices 0 a n-1)
Heap* criarHeap(int array[], int tamanho, PerformanceStats *stats) {
    Heap *heap = (Heap*)malloc(sizeof(Heap));
    heap->dados = (int*)malloc(tamanho * sizeof(int));
    heap->tamanho = tamanho;
    heap->heapSize = tamanho;

    for (int i = 0; i < tamanho; i++) {
        heap->dados[i] = array[i];
    }

    stats->memory_allocations += 2; // Contabiliza as alocações do heap e dos dados
    return heap;
}

// Função para copiar dados do heap de volta para o array original (ajustando índices)
void copiarHeapParaArray(Heap *heap, int array[]) {
    for (int i = 0; i < heap->tamanho; i++) {
        array[i] = heap->dados[i];
    }
}

// Função para liberar memória do heap
void liberarHeap(Heap *heap) {
    free(heap->dados);
    free(heap);
}

void heap_sort(int V[], int tamanho, PerformanceStats *stats) {
    strcpy(stats->algorithm_name, "Heap Sort");
    stats->comparisons = 0;
    stats->swaps = 0;
    stats->memory_allocations = 0;

    Heap *heap = criarHeap(V, tamanho, stats);
    heapSort_heap(heap, stats);
    copiarHeapParaArray(heap, V);
    liberarHeap(heap);
}

// ========================================
// FUNÇÕES AUXILIARES
// ========================================

void print_array(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]\n");
}

void copy_array(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int is_sorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void print_stats(PerformanceStats stats[], int count) {
    printf("\n--- Estatisticas de Desempenho ---\n");
    printf("%-15s | %-12s | %-10s | %-15s\n", "Algoritmo", "Comparacoes", "Movimentos", "Alocacoes Mem.");
    printf("%-15s-|-%-12s-|-%-10s-|-%-15s\n", "---------------", "------------", "----------", "---------------");
    
    for (int i = 0; i < count; i++) {
        printf("%-15s | %-12d | %-10d | %-15d\n", 
               stats[i].algorithm_name, 
               stats[i].comparisons, 
               stats[i].swaps,
               stats[i].memory_allocations);
    }
}

// ========================================
// FUNÇÃO PRINCIPAL
// ========================================

int main() {
    printf("========================================\n");
    printf("  ALGORITMOS DE ORDENACAO AVANCADOS\n");
    printf("========================================\n");
    printf("Implementacao exata conforme os slides\n\n");
    
    int original[] = {8, 2, 1, 6, 7, 0, 3, 5, 4, 9};
    int tamanho = sizeof(original) / sizeof(original[0]);
    
    printf("Array original: ");
    print_array(original, tamanho);
    
    // Arrays para cada algoritmo
    int arr_merge[10], arr_quick[10], arr_heap[10];
    PerformanceStats stats[3];
    
    // Teste Merge Sort
    printf("\n=== MERGE SORT ===\n");
    copy_array(original, arr_merge, tamanho);
    merge_sort(arr_merge, tamanho, &stats[0]);
    printf("Array apos ordenacao: ");
    print_array(arr_merge, tamanho);
    printf("Verificacao: %s\n", is_sorted(arr_merge, tamanho) ? "Correto" : "Erro");
    
    // Teste Quick Sort
    printf("\n=== QUICK SORT ===\n");
    copy_array(original, arr_quick, tamanho);
    quick_sort(arr_quick, tamanho, &stats[1]);
    printf("Array apos ordenacao: ");
    print_array(arr_quick, tamanho);
    printf("Verificacao: %s\n", is_sorted(arr_quick, tamanho) ? "Correto" : "Erro");
    
    // Teste Heap Sort
    printf("\n=== HEAP SORT ===\n");
    copy_array(original, arr_heap, tamanho);
    heap_sort(arr_heap, tamanho, &stats[2]);
    printf("Array apos ordenacao: ");
    print_array(arr_heap, tamanho);
    printf("Verificacao: %s\n", is_sorted(arr_heap, tamanho) ? "Correto" : "Erro");
    
    // Estatísticas comparativas
    print_stats(stats, 3);
    
    // Teste adicional com diferentes cenários para análise
    printf("\n\n========================================\n");
    printf("         ANALISE COMPARATIVA\n");
    printf("========================================\n");
    
    // Cenário 1: Array já ordenado [1, 2, 3, 4, 5]
    printf("\n--- Cenario 1: Array ja ordenado ---\n");
    int sorted_array[] = {1, 2, 3, 4, 5};
    int sorted_size = 5;
    printf("Array: ");
    print_array(sorted_array, sorted_size);
    
    int test_arr[5];
    PerformanceStats sorted_stats[3];
    
    copy_array(sorted_array, test_arr, sorted_size);
    merge_sort(test_arr, sorted_size, &sorted_stats[0]);
    
    copy_array(sorted_array, test_arr, sorted_size);
    quick_sort(test_arr, sorted_size, &sorted_stats[1]);
    
    copy_array(sorted_array, test_arr, sorted_size);
    heap_sort(test_arr, sorted_size, &sorted_stats[2]);
    
    print_stats(sorted_stats, 3);
    
    // Cenário 2: Array em ordem reversa [5, 4, 3, 2, 1]
    printf("\n--- Cenario 2: Array em ordem reversa ---\n");
    int reverse_array[] = {5, 4, 3, 2, 1};
    int reverse_size = 5;
    printf("Array: ");
    print_array(reverse_array, reverse_size);
    
    PerformanceStats reverse_stats[3];
    
    copy_array(reverse_array, test_arr, reverse_size);
    merge_sort(test_arr, reverse_size, &reverse_stats[0]);
    
    copy_array(reverse_array, test_arr, reverse_size);
    quick_sort(test_arr, reverse_size, &reverse_stats[1]);
    
    copy_array(reverse_array, test_arr, reverse_size);
    heap_sort(test_arr, reverse_size, &reverse_stats[2]);
    
    print_stats(reverse_stats, 3);
    
    // Cenário 3: Array com elementos iguais [3, 3, 3, 3, 3]
    printf("\n--- Cenario 3: Array com elementos iguais ---\n");
    int equal_array[] = {3, 3, 3, 3, 3};
    int equal_size = 5;
    printf("Array: ");
    print_array(equal_array, equal_size);
    
    PerformanceStats equal_stats[3];
    
    copy_array(equal_array, test_arr, equal_size);
    merge_sort(test_arr, equal_size, &equal_stats[0]);
    
    copy_array(equal_array, test_arr, equal_size);
    quick_sort(test_arr, equal_size, &equal_stats[1]);
    
    copy_array(equal_array, test_arr, equal_size);
    heap_sort(test_arr, equal_size, &equal_stats[2]);
    
    print_stats(equal_stats, 3);
    
    // Resumo das características
    printf("\n========================================\n");
    printf("              RESUMO\n");
    printf("========================================\n");
    printf("MERGE SORT:\n");
    printf("- Divisao e conquista recursiva\n");
    printf("- Sempre O(n log n) - estavel e previsivel\n");
    printf("- Requer memoria extra O(n)\n");
    printf("- Algoritmo estavel\n\n");
    
    printf("QUICK SORT:\n");
    printf("- Particiona array em torno de um pivo\n");
    printf("- Medio caso O(n log n), pior caso O(n²)\n");
    printf("- In-place, memoria O(log n)\n");
    printf("- Nao estavel\n\n");
    
    printf("HEAP SORT:\n");
    printf("- Usa estrutura de heap binario\n");
    printf("- Sempre O(n log n) - performance consistente\n");
    printf("- In-place, memoria O(1)\n");
    printf("- Nao estavel\n\n");
    
    printf("Todos sao algoritmos eficientes O(n log n) para grandes volumes.\n");
    printf("Merge Sort: melhor para estabilidade e performance previsivel.\n");
    printf("Quick Sort: melhor performance media, mas instavel no pior caso.\n");
    printf("Heap Sort: melhor para memoria limitada e performance consistente.\n");
    
    return 0;
}