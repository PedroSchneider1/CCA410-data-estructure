#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice {
    int valor;
    struct Vertice *esq;
    struct Vertice *dir;
    struct Vertice *pai;
} Vertice;

typedef struct Arvore {
    Vertice *raiz;
    int qtde;
} Arvore;

int max(int a, int b) {
    return (a >= b) ? a : b;
}

int altura(Vertice *no) {
    if (no == NULL) return -1;
    return max(altura(no->esq), altura(no->dir)) + 1;
}

int fatorBalanceamento(Vertice *no) {
    return altura(no->dir) - altura(no->esq);
}

void rotacaoEsquerda(Arvore *arvore, Vertice *x) {
    printf("Rotacao Esquerda em %d\n", x->valor);
    
    Vertice *y = x->dir;
    
    if (y == NULL) return;

    x->dir = y->esq;
    if (y->esq != NULL) y->esq->pai = x;

    y->pai = x->pai;
    
    if(x->pai == NULL){
        arvore->raiz = y;
    } else if (x == x->pai->esq){
        x->pai->esq = y;
    } else{
        x->pai->dir = y;
    }

    y->esq = x;
    x->pai = y;
}

void rotacaoDireita(Arvore *arvore, Vertice *x) {
    printf("Rotacao Direita em %d\n", x->valor);
    
    Vertice *y = x->esq;
    
    if (y == NULL) return;

    x->esq = y->dir;
    if (y->dir != NULL) y->dir->pai = x;

    y->pai = x->pai;
    
    if(x->pai == NULL){
        arvore->raiz = y;
    } else if (x == x->pai->dir){
        x->pai->dir = y;
    } else{
        x->pai->esq = y;
    }

    y->dir = x;
    x->pai = y;
}

void balancear(Arvore *arvore, Vertice *x) {
    int fb = fatorBalanceamento(x);

    if (fb > 1){
        if(fatorBalanceamento(x->dir) < 0)
            rotacaoDireita(arvore, x->dir);
        rotacaoEsquerda(arvore, x);
    } else if (fb < -1){
        if(fatorBalanceamento(x->esq) > 0)
            rotacaoEsquerda(arvore, x->esq);
        rotacaoDireita(arvore, x);
    }
}

int inserir(Arvore *arvore, int valor) {
    Vertice *novo = malloc(sizeof(Vertice));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    
    Vertice *pai = NULL;
    Vertice *atual = arvore->raiz;
    
    while (atual != NULL) {
        pai = atual;
        if (valor <= atual->valor) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    
    novo->pai = pai;
    if (pai != NULL) {
        if (valor <= pai->valor) {
            pai->esq = novo;
        } else {
            pai->dir = novo;
        }
    } else {
        arvore->raiz = novo;
    }
    arvore->qtde++;
    
    Vertice *temp = novo->pai;
    while (temp != NULL) {
        balancear(arvore, temp);
        temp = temp->pai;
    }
    return 1;
}

void imprimirArvore(Vertice *no, char *prefixo, int ultimo) {
    if (no == NULL) return;
    
    printf("%s", prefixo);
    printf(ultimo ? "└── " : "├── ");
    printf("%d\n", no->valor);
    
    char novoPrefixo[256];
    sprintf(novoPrefixo, "%s%s", prefixo, ultimo ? "    " : "│   ");
    
    int temEsq = (no->esq != NULL);
    int temDir = (no->dir != NULL);
    
    if (temDir && temEsq) {
        imprimirArvore(no->dir, novoPrefixo, 0);
        imprimirArvore(no->esq, novoPrefixo, 1);
    } else if (temDir) {
        imprimirArvore(no->dir, novoPrefixo, 1);
    } else if (temEsq) {
        imprimirArvore(no->esq, novoPrefixo, 1);
    }
}

void inOrdem(Vertice *raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        inOrdem(raiz->dir);
    }
}

void posOrdem(Vertice *raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

void testeInsere(Arvore *arvore, int valor) {
    printf("\n--- INSERINDO %d ---\n", valor);
    inserir(arvore, valor);
    
    if (arvore->raiz == NULL) {
        printf("Arvore vazia\n");
    } else {
        imprimirArvore(arvore->raiz, "", 1);
    }
    
    printf("In-Ordem: ");
    inOrdem(arvore->raiz);
    printf("\nPós-Ordem: ");
    posOrdem(arvore->raiz);
    printf("\nTotal: %d nos\n", arvore->qtde);
}

int main(void) {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->qtde = 0;
    
    testeInsere(arvore, 21);
    testeInsere(arvore, 26);
    testeInsere(arvore, 30);
    testeInsere(arvore, 9);
    testeInsere(arvore, 4);
    testeInsere(arvore, 14);
    testeInsere(arvore, 28);
    testeInsere(arvore, 18);
    testeInsere(arvore, 15);
    testeInsere(arvore, 10);
    testeInsere(arvore, 2);
    testeInsere(arvore, 3);
    testeInsere(arvore, 7);
    
    printf("\n=== ARVORE FINAL ===\n");
    imprimirArvore(arvore->raiz, "", 1);
    
    return 0;
}