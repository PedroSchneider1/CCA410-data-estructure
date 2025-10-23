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

void initialize_source(){

}

void relax(){

}

// ========== DJISKTRA ==========

void djisktra(){

}

// ========== BELLMAN-FORD ==========

void bellman_ford(){
    
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        printf("Modo de busca nao especificado.\n");
        return 1;
    }

    switch (*argv[1]) {
        case '1':
            printf("\n=== DIJKSTRA ===\n");
            break;
        case '2':
            printf("\n=== BELLMAN-FORD ===\n");
            break;

        default:
            printf("Modo de busca inválido.\n");
            break;
    }
    return 0;
}