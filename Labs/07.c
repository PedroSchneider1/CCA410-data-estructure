#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int comparisons;
    int swaps;
    char algorithm_name[20];
} PerformanceStats;

void swap(int* a, int* b){
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void bubble_sort(int V[], int tamanho, PerformanceStats *stats) {
    stats->comparisons = 0;
    stats->swaps = 0;
    strcpy(stats->algorithm_name, "Bubble Sort");
    for (size_t i = 0; i < tamanho-1; i++)
	{
		for (size_t j = tamanho-1; j > i; j--)
		{
            stats->comparisons++;
			if (V[j] < V[j-1])
			{
				swap(&V[j], &V[j-1]);
                stats->swaps++;
			}
		}
	}
}

void insertion_sort(int V[], int tamanho, PerformanceStats *stats) {
    stats->comparisons = 0;
    stats->swaps = 0;
    strcpy(stats->algorithm_name, "Insertion Sort");
    for (size_t i = 1; i < tamanho; i++)
	{
		int key = V[i];
		int j = i-1;

		while (j >= 0 && V[j] > key)
		{
			stats->comparisons++;
            V[j+1] = V[j];
            stats->swaps++;
            j = j-1;
		}
        if (j >= 0)
            stats->comparisons++; // V[j] <= key
        V[j + 1] = key;
	}
}

void selection_sort(int V[], int tamanho, PerformanceStats *stats) {
    stats->comparisons = 0;
    stats->swaps = 0;
    strcpy(stats->algorithm_name, "Selection Sort");
    for (size_t i = 0; i < tamanho - 1; i++) {
        int min_index = i;
        for (size_t j = i + 1; j < tamanho; j++) {
            stats->comparisons++;
            if (V[j] < V[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&V[i], &V[min_index]);
            stats->swaps++;
        }
    }
}

void print_array(int arr[], int n) {
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
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
    printf("%-15s | %-12s | %-10s\n", "Algoritmo", "Comparacoes", "Trocas");
    printf("%-15s-|-%-12s-|-%-10s\n", "---------------", "------------", "----------");
    
    for (int i = 0; i < count; i++) {
        printf("%-15s | %-12d | %-10d\n", 
               stats[i].algorithm_name, 
               stats[i].comparisons, 
               stats[i].swaps);
    }
}

int main() {
    printf("========================================\n");
    printf("  ALGORITMOS DE ORDENACAO SIMPLES\n");
    printf("========================================\n");
    printf("Implementacao exata conforme os slides\n\n");
    
    int original[] = {8, 2, 1, 6, 7, 0, 3, 5, 4, 9};
    int tamanho = sizeof(original) / sizeof(original[0]);
    
    printf("Array original: ");
    print_array(original, tamanho);
    
    // Arrays para cada algoritmo
    int arr_bubble[10], arr_insertion[10], arr_selection[10];
    PerformanceStats stats[3];
    
    // Teste Bubble Sort
    printf("\n=== BUBBLE SORT ===\n");
    copy_array(original, arr_bubble, tamanho);
    bubble_sort(arr_bubble, tamanho, &stats[0]);
    printf("Array apos ordenacao: ");
    print_array(arr_bubble, tamanho);
    printf("Verificacao: %s\n", is_sorted(arr_bubble, tamanho) ? "Correto" : "Erro");
    
    // Teste Insertion Sort
    printf("\n=== INSERTION SORT ===\n");
    copy_array(original, arr_insertion, tamanho);
    insertion_sort(arr_insertion, tamanho, &stats[1]);
    printf("Array apos ordenacao: ");
    print_array(arr_insertion, tamanho);
    printf("Verificacao: %s\n", is_sorted(arr_insertion, tamanho) ? "Correto" : "Erro");
    
    // Teste Selection Sort
    printf("\n=== SELECTION SORT ===\n");
    copy_array(original, arr_selection, tamanho);
    selection_sort(arr_selection, tamanho, &stats[2]);
    printf("Array apos ordenacao: ");
    print_array(arr_selection, tamanho);
    printf("Verificacao: %s\n", is_sorted(arr_selection, tamanho) ? "Correto" : "Erro");
    
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
    bubble_sort(test_arr, sorted_size, &sorted_stats[0]);
    
    copy_array(sorted_array, test_arr, sorted_size);
    insertion_sort(test_arr, sorted_size, &sorted_stats[1]);
    
    copy_array(sorted_array, test_arr, sorted_size);
    selection_sort(test_arr, sorted_size, &sorted_stats[2]);
    
    print_stats(sorted_stats, 3);
    
    // Cenário 2: Array em ordem reversa [5, 4, 3, 2, 1]
    printf("\n--- Cenario 2: Array em ordem reversa ---\n");
    int reverse_array[] = {5, 4, 3, 2, 1};
    int reverse_size = 5;
    printf("Array: ");
    print_array(reverse_array, reverse_size);
    
    PerformanceStats reverse_stats[3];
    
    copy_array(reverse_array, test_arr, reverse_size);
    bubble_sort(test_arr, reverse_size, &reverse_stats[0]);
    
    copy_array(reverse_array, test_arr, reverse_size);
    insertion_sort(test_arr, reverse_size, &reverse_stats[1]);
    
    copy_array(reverse_array, test_arr, reverse_size);
    selection_sort(test_arr, reverse_size, &reverse_stats[2]);
    
    print_stats(reverse_stats, 3);
    
    // Cenário 3: Array com elementos iguais [3, 3, 3, 3, 3]
    printf("\n--- Cenario 3: Array com elementos iguais ---\n");
    int equal_array[] = {3, 3, 3, 3, 3};
    int equal_size = 5;
    printf("Array: ");
    print_array(equal_array, equal_size);
    
    PerformanceStats equal_stats[3];
    
    copy_array(equal_array, test_arr, equal_size);
    bubble_sort(test_arr, equal_size, &equal_stats[0]);
    
    copy_array(equal_array, test_arr, equal_size);
    insertion_sort(test_arr, equal_size, &equal_stats[1]);
    
    copy_array(equal_array, test_arr, equal_size);
    selection_sort(test_arr, equal_size, &equal_stats[2]);
    
    print_stats(equal_stats, 3);
    
    // Resumo das características
    printf("\n========================================\n");
    printf("              RESUMO\n");
    printf("========================================\n");
    printf("BUBBLE SORT:\n");
    printf("- Compara elementos adjacentes\n");
    printf("- Faz multiplas passadas pelo array\n");
    printf("- Elementos 'borbulham' para posicao correta\n\n");
    
    printf("INSERTION SORT:\n");
    printf("- Insere cada elemento na posicao correta\n");
    printf("- Eficiente para arrays pequenos\n");
    printf("- Adaptativo (rapido em arrays ordenados)\n\n");
    
    printf("SELECTION SORT:\n");
    printf("- Seleciona o menor elemento a cada iteracao\n");
    printf("- Numero minimo de trocas\n");
    printf("- Nao adaptativo (sempre O(n²))\n\n");
    
    printf("Todos os algoritmos têm complexidade O(n²) no pior caso.\n");
    
    return 0;
}