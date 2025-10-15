/*
 * Exercício: Percorrendo Grafos - Rede Social
 * Estrutura de Dados - Representação com Lista de Adjacência
 */

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
    printf("\n=== REDE SOCIAL ===\n");
    for(int i = 0; i < grafo->numVertices; i++) {
        No *temp = grafo->listaAdj[i];
        printf("Pessoa %d é amiga de:", i + 1);
        while(temp) {
            printf(" %d", temp->vertice + 1);
            temp = temp->proximo;
        }
        printf("\n");
    }
}

// ========== EXERCÍCIO 1: CONTADOR DE AMIGOS ==========

int contarAmigos(GrafoLista *grafo, int pessoa) {
    int amigos = 0;
    No *temp = grafo->listaAdj[pessoa - 1];

    while(temp) {
        amigos++;
        temp = temp->proximo;
    }
    free(temp);
    return amigos;
}

// ========== EXERCÍCIO 2: PESSOA MAIS POPULAR ==========

int pessoaMaisPopular(GrafoLista *grafo) {
    int maxAmigos = -1;
    int pessoaPopular = -1;

    for(int i = 0; i < grafo->numVertices; i++) {
        int numAmigos = contarAmigos(grafo, i + 1);
        if(numAmigos > maxAmigos) {
            maxAmigos = numAmigos;
            pessoaPopular = i + 1;
        }
    }
    return pessoaPopular;
}

// ========== EXERCÍCIO 3: VERIFICAR AMIZADE DIRETA ==========

int saoAmigos(GrafoLista *grafo, int pessoa1, int pessoa2) {
    No *temp = grafo->listaAdj[pessoa1 - 1];
    while(temp) {
        if(temp->vertice == pessoa2 - 1) {
            return 1; // São amigos
        }
        temp = temp->proximo;
    }
    free(temp);
    return 0; // Não são amigos
}

// ========== EXERCÍCIO 4: AMIGOS EM COMUM ==========

void amigosEmComum(GrafoLista *grafo, int pessoa1, int pessoa2) {
    No *temp1 = grafo->listaAdj[pessoa1 - 1];
    No *temp2 = grafo->listaAdj[pessoa2 - 1];

    printf("\nAmigos em comum entre %d e %d: ", pessoa1, pessoa2);
    while (temp1) {
        temp2 = grafo->listaAdj[pessoa2 - 1];
        while (temp2) {
            if (temp1->vertice == temp2->vertice) {
                printf("%d ", temp2->vertice + 1);
            }
            temp2 = temp2->proximo;
        }
        temp1 = temp1->proximo;
    }
    printf("\n");
    free(temp1);
    free(temp2);
}

// ========== EXERCÍCIO 5: RECOMENDAÇÃO DE AMIZADE ==========

void recomendarAmigos(GrafoLista *grafo, int pessoa) {
    int *recomendacoes = calloc(grafo->numVertices, sizeof(int));
    No *temp = grafo->listaAdj[pessoa - 1];

    while (temp){
        No *amigo = grafo->listaAdj[temp->vertice];
        while (amigo){
            if (amigo->vertice != pessoa - 1
                && !saoAmigos(grafo, pessoa, amigo->vertice + 1)
                && recomendacoes[amigo->vertice] == 0) {
                recomendacoes[amigo->vertice] = temp->vertice + 1;
            }
            amigo = amigo->proximo;
        }
        temp = temp->proximo;
    }
    
    printf("\nRecomendações de amizade para pessoa %d: ", pessoa);
    for (int i = grafo->numVertices - 1; i >= 0; i--){
        if (recomendacoes[i] > 0){
            printf("\n  -> Pessoa %d (amiga de %d)", i + 1, recomendacoes[i]);
        }
    }
    printf("\n");
    free(recomendacoes);
    free(temp);
}

// ========== FUNÇÃO PRINCIPAL ==========

int main() {
    // Cria o grafo fixo da rede social
    GrafoLista *grafo = criarGrafo(7);
    
    // Define as amizades (grafo fixo)
    adicionarAresta(grafo, 0, 1);  // Pessoa 1 - 2
    adicionarAresta(grafo, 0, 2);  // Pessoa 1 - 3
    adicionarAresta(grafo, 1, 2);  // Pessoa 2 - 3
    adicionarAresta(grafo, 2, 3);  // Pessoa 3 - 4
    adicionarAresta(grafo, 2, 4);  // Pessoa 3 - 5
    adicionarAresta(grafo, 3, 4);  // Pessoa 4 - 5
    adicionarAresta(grafo, 3, 5);  // Pessoa 4 - 6
    adicionarAresta(grafo, 4, 5);  // Pessoa 5 - 6
    adicionarAresta(grafo, 4, 6);  // Pessoa 5 - 7
    adicionarAresta(grafo, 5, 6);  // Pessoa 6 - 7
    
    // Exibe a rede social
    imprimirGrafo(grafo);
    
    // ========== TESTES DOS EXERCÍCIOS ==========
    
    printf("\n========== EXERCÍCIO 1: CONTADOR DE AMIGOS ==========\n");
    for(int i = 1; i <= 7; i++) {
        printf("Pessoa %d tem %d amigo(s)\n", i, contarAmigos(grafo, i));
    }
    
    printf("\n========== EXERCÍCIO 2: PESSOA MAIS POPULAR ==========\n");
    int popular = pessoaMaisPopular(grafo);
    printf("A pessoa mais popular é %d com %d amigos\n", 
           popular, contarAmigos(grafo, popular));
    
    printf("\n========== EXERCÍCIO 3: VERIFICAR AMIZADE ==========\n");
    printf("Pessoa 1 e 2 são amigas? %s\n", 
           saoAmigos(grafo, 1, 2) ? "SIM" : "NÃO");
    printf("Pessoa 1 e 4 são amigas? %s\n", 
           saoAmigos(grafo, 1, 4) ? "SIM" : "NÃO");
    printf("Pessoa 5 e 7 são amigas? %s\n", 
           saoAmigos(grafo, 5, 7) ? "SIM" : "NÃO");
    
    printf("\n========== EXERCÍCIO 4: AMIGOS EM COMUM ==========\n");
    amigosEmComum(grafo, 1, 3);
    amigosEmComum(grafo, 2, 4);
    amigosEmComum(grafo, 5, 6);
    
    printf("\n========== EXERCÍCIO 5: RECOMENDAÇÃO DE AMIZADE ==========\n");
    recomendarAmigos(grafo, 1);
    recomendarAmigos(grafo, 7);
    
    printf("\n");
    return 0;
}