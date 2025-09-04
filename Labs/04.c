#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11

typedef struct Celula{
  int valor;
  struct Celula* proximo;
}Celula;

typedef struct {
  Celula* inicio;
}Lista;

typedef struct {
  Lista* table[tam_hash];
}Hash;

int h(int k){
    return k % tam_hash;
}

Hash* start_hash(){
    Hash *h = malloc(sizeof(Hash));

    for (size_t i = 0; i < tam_hash; i++)
    {
        h->table[i] = malloc(sizeof(Lista));
        h->table[i]->inicio = NULL;
    }
    
    return h;
}

void inserir_hash(Hash* hash, int valor){
    int index = h(valor);
    Celula *nova = malloc(sizeof(Celula));
    nova->valor = valor;
    nova->proximo = hash->table[index]->inicio;
    hash->table[index]->inicio = nova;
}

void remover_hash(Hash* hash, int valor){
    int index = h(valor);
    Celula *atual = hash->table[index]->inicio;
    Celula *anterior = NULL;
    
    while (atual != NULL)
    {
        if(atual->valor == valor){
            if (anterior == NULL) {
                hash->table[index]->inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void imprimir(Hash* hash){
    printf("---------------------\n");
    for (int i = 0; i < tam_hash; i++) {
        Celula *atual = hash->table[i]->inicio;
        printf("%d -> ", i);
        while (atual != NULL) {
            printf("%d ", atual->valor);
            atual = atual->proximo;
        }
        printf("\n");
    }
    printf("---------------------\n");
}

int main(void) {
    Hash* hash = start_hash();
    int valor;

    while(1){
        scanf("%d", &valor);
        if(valor == 0)
            break;
        inserir_hash(hash, valor);
    }
    imprimir(hash);

    while(1){
        scanf("%d", &valor);
        if(valor == 0)
            break;
        remover_hash(hash, valor);
    }
    imprimir(hash);
    return 0;
}