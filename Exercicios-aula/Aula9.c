#include <stdio.h>
#include <stdlib.h>

void imprime_grafo(int **edges, int nodes) {
    for (size_t i = 0; i < nodes; i++) {
        for (size_t j = 0; j < nodes; j++) {
            printf("%d ", edges[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[]) {
    // .\a.exe OPT_GRAFO (1~3)
    int nodes;
    printf("Digite o numero de nos: ");
    scanf("%d", &nodes);

    if (argc < 2) {
        printf("Modo de grafo nao especificado.\n");
        return 1;
    }
    
    switch (*argv[1]) {
    case '1': {
        printf("===GRAFO NAO-ORIENTADO===\n");
        // incializa a matriz
        int **edges = malloc(nodes * sizeof(int *));
        for (int i = 0; i < nodes; i++) {
            edges[i] = malloc(nodes * sizeof(int));
        }
        int n_edges;
        int p1, p2;

        printf("Digite o numero de arestas: ");
        scanf("%d", &n_edges);

        // zero-fill no array de arestas
        for (size_t i = 0; i < nodes; i++) {
            for (size_t j = 0; j < nodes; j++) {
                edges[i][j] = 0;
            }
        }

        // coloca 1 nos nós que possuem arestas para outro nó
        for (size_t i = 0; i < n_edges; i++) {
            scanf("%d %d", &p1, &p2);
            edges[p1-1][p2-1] = 1;
            edges[p2-1][p1-1] = 1;
        }

        imprime_grafo(edges, nodes);

        for (int i = 0; i < nodes; i++) {
            free(edges[i]);
        }
        free(edges);
        break;
    }
    case '2': {
        printf("===GRAFO ORIENTADO===\n");
        // incializa a matriz
        int **edges = malloc(nodes * sizeof(int *));
        for (int i = 0; i < nodes; i++) {
            edges[i] = malloc(nodes * sizeof(int));
        }
        int n_edges;
        int p1, p2;

        printf("Digite o numero de arestas: ");
        scanf("%d", &n_edges);

        // zero-fill no array de arestas
        for (size_t i = 0; i < nodes; i++) {
            for (size_t j = 0; j < nodes; j++) {
                edges[i][j] = 0;
            }
        }

        // coloca 1 nos nós que possuem arestas para outro nó
        for (size_t i = 0; i < n_edges; i++) {
            scanf("%d %d", &p1, &p2);
            edges[p1-1][p2-1] = 1;
        }

        imprime_grafo(edges, nodes);

        for (int i = 0; i < nodes; i++) {
            free(edges[i]);
        }
        free(edges);
        break;
    }
    case '3': {
        printf("===GRAFO PONDERADO===\n");
        // incializa a matriz
        int **edges = malloc(nodes * sizeof(int *));
        for (int i = 0; i < nodes; i++) {
            edges[i] = malloc(nodes * sizeof(int));
        }
        int n_edges;
        int p1, p2, weight;

        printf("Digite o numero de arestas: ");
        scanf("%d", &n_edges);

        // zero-fill no array de arestas
        for (size_t i = 0; i < nodes; i++) {
            for (size_t j = 0; j < nodes; j++) {
                edges[i][j] = 0;
            }
        }

        // coloca 1 nos nós que possuem arestas para outro nó
        for (size_t i = 0; i < n_edges; i++) {
            scanf("%d %d %d", &p1, &p2, &weight);
            edges[p1-1][p2-1] = weight;
            edges[p2-1][p1-1] = weight;
        }

        imprime_grafo(edges, nodes);

        for (int i = 0; i < nodes; i++) {
            free(edges[i]);
        }
        free(edges);
        break;
    }
    default:
        printf("Modo de grafo invalido.\n");
        break;
    }

    return 0;
}