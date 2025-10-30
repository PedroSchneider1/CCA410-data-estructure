#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da lista
typedef struct No {
    int vertice;
    struct No *proximo;
} No;

// Estrutura do grafo
typedef struct {
    int numVertices;
    No **listaAdj;
} GrafoLista;

// ========== Kruskal ==========

void kruskal(){

}

// ========== Prim ==========

void prim(){
    
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("Modo de busca nao especificado.\n");
        return 1;
    }

    switch (*argv[1]) {
        case '1':
            printf("\n=== Kruskal ===\n");
            break;
        case '2':
            printf("\n=== Prim ===\n");
            break;

        default:
            printf("Modo de busca inválido.\n");
            break;
    }
    return 0;
}