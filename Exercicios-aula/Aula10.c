#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10
#define BRANCO 0
#define CINZA 1
#define PRETO 2

int cor[MAX_NODES];

// BFS
int distancia[MAX_NODES];

// DFS
int d[MAX_NODES]; // tempo de descoberta
int f[MAX_NODES]; // tempo de finalização
int tempo = 0;

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


// Estrutura da fila
typedef struct Fila {
    int dados[MAX_NODES];
    int frente, tras;
} Fila;

// Estrutura da pilha (usado em DFS sem recursão)
typedef struct Pilha {
    int dados[MAX_NODES];
    int topo;
} Pilha;

// ========== FUNÇÕES BÁSICAS DA FILA ===========

void inicializa_fila(Fila *f) {
    f->frente = f->tras = 0;
}

void insere_fila(Fila *f, int valor) {
    f->dados[f->tras++] = valor;
}

int remove_fila(Fila *f) {
    return f->dados[f->frente++];
}

int fila_vazia(Fila *f) {
    return f->frente == f->tras;
}

// ========== FUNÇÕES BÁSICAS DA PILHA ===========

void inicializa_pilha(Pilha *p) {
    p->topo = 0;
}

void insere_pilha(Pilha *p, int valor) {
    if (p->topo < MAX_NODES) {
        p->dados[p->topo++] = valor;
    }
}

int remove_pilha(Pilha *p) {
    if (p->topo > 0) {
        return p->dados[--p->topo];
    }
    return -1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == 0;
}

// ========== FUNÇÕES BÁSICAS DO GRAFO ==========

No* criarNo(int v) {
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = v;
    novoNo->proximo = NULL;
    return novoNo;
}

GrafoLista* criarGrafo(int n) {
    GrafoLista *grafo = (GrafoLista*)malloc(sizeof(GrafoLista));
    grafo->numVertices = n;
    grafo->listaAdj = (No**)malloc(n * sizeof(No*));
    
    for(int i = 0; i < n; i++) {
        grafo->listaAdj[i] = NULL;
    }
    return grafo;
}

void adicionarAresta(GrafoLista *grafo, int origem, int destino) {
    No *novoNo = criarNo(destino);
    novoNo->proximo = grafo->listaAdj[origem];
    grafo->listaAdj[origem] = novoNo;
    
    novoNo = criarNo(origem);
    novoNo->proximo = grafo->listaAdj[destino];
    grafo->listaAdj[destino] = novoNo;
}

void imprimirGrafo(GrafoLista *grafo) {
    for(int i = 0; i < grafo->numVertices; i++) {
        No *temp = grafo->listaAdj[i];
        printf("No %.2d:", i + 1);
        while(temp) {
            printf(" %2d", temp->vertice + 1);
            temp = temp->proximo;
        }
        printf("\n");
    }
}

// ========== BFS ==========

void bfs(int source, GrafoLista *grafo){
    Fila fila;
    inicializa_fila(&fila);

    for (int i = 0; i < MAX_NODES; i++) {
        cor[i] = BRANCO;
        distancia[i] = -1;
    }

    cor[source] = CINZA;
    distancia[source] = 0;
    insere_fila(&fila, source);

    while (!fila_vazia(&fila)) {
        int u = remove_fila(&fila);
        No *vizinho = grafo->listaAdj[u];

        while (vizinho != NULL) {
            int v = vizinho->vertice;
            if (cor[v] == BRANCO) {
                cor[v] = CINZA;
                distancia[v] = distancia[u] + 1;
                insere_fila(&fila, v);
            }
            vizinho = vizinho->proximo;
        }

        cor[u] = PRETO;
    }
}

void imprime_distancias(int origem) {
    printf("\nDistancias a partir do no %d:\n", origem + 1);
    for (int i = 0; i < MAX_NODES; i++) {
        printf("No %2d: %d\n", i + 1, distancia[i]);
    }
}

// ========== DFS ==========

void visitaDFS(GrafoLista *grafo, int u) {
    tempo += 1;
    d[u] = tempo;
    cor[u] = CINZA;

    No *vizinho = grafo->listaAdj[u];
    while (vizinho != NULL) {
        int v = vizinho->vertice;
        if (cor[v] == BRANCO) {
            visitaDFS(grafo, v);
        }
        vizinho = vizinho->proximo;
    }

    tempo += 1;
    f[u] = tempo;
    cor[u] = PRETO;
}

void dfs(GrafoLista *grafo) {
    for (int i = 0; i < MAX_NODES; i++) {
        cor[i] = BRANCO;
        d[i] = f[i] = -1;
    }

    tempo = 0;

    for (int i = 0; i < MAX_NODES; i++) {
        if (cor[i] == BRANCO) {
            visitaDFS(grafo, i);
        }
    }
}

void imprime_tempos() {
    printf("\nTempos de descoberta e finalizacao:\n");
    for (int i = 0; i < MAX_NODES; i++) {
        printf("No %2d: d = %2d, f = %2d\n", i + 1, d[i], f[i]);
    }
}

// ========== MAIN ==========

int main(int argc, char const *argv[]) {
    /* GRAFO:
         1 - 2 - 3
         |   |   |
         4 - 5 - 6
         |   |   |
         7 - 8 - 9
             |  /
            10-/
    */

    GrafoLista *grafo = criarGrafo(MAX_NODES);
    
    adicionarAresta(grafo, 0, 1); // 1 - 2
    adicionarAresta(grafo, 0, 3); // 1 - 4
    adicionarAresta(grafo, 1, 2); // 2 - 3
    adicionarAresta(grafo, 1, 4); // 2 - 5
    adicionarAresta(grafo, 2, 5); // 3 - 6
    adicionarAresta(grafo, 3, 6); // 4 - 7
    adicionarAresta(grafo, 3, 4); // 4 - 5
    adicionarAresta(grafo, 4, 5); // 5 - 6
    adicionarAresta(grafo, 4, 7); // 5 - 8
    adicionarAresta(grafo, 5, 8); // 6 - 9
    adicionarAresta(grafo, 6, 7); // 7 - 8
    adicionarAresta(grafo, 7, 9); // 8 - 10
    adicionarAresta(grafo, 7, 8); // 8 - 9
    adicionarAresta(grafo, 8, 9); // 9 - 10

    if (argc < 2) {
        printf("Modo de busca não especificado.\n");
        return 1;
    }

    printf("GRAFO ORIGINAL:\n");
    imprimirGrafo(grafo);

    switch (*argv[1]) {
        case '1':
            printf("\n=== BREADTH FIRST SEARCH (BFS) ===\n");

            bfs(0, grafo);
            imprime_distancias(0);
            break;

        case '2':
            printf("\n=== WIDTH FIRST SEARCH (BFS) ===\n");

            dfs(grafo);
            imprime_tempos();
            break;

        default:
            printf("Modo de busca inválido.\n");
            break;
    }

    return 0;
}
