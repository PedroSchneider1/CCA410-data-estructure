#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 7

// Nó para encadeamento externo
typedef struct Node {
    int value;
    struct Node* next;
} Node;

// Função hash
int h(int k) {
    return k % HASH_SIZE;
}

// Inserção na lista encadeada
void insert(Node** table, int key) {
    int index = h(key);
    Node* newNode = malloc(sizeof(Node));
    newNode->value = key;
    newNode->next = table[index];
    table[index] = newNode;
}

// Remoção de um valor específico
void removeKey(Node** table, int key) {
    int index = h(key);
    Node* curr = table[index];
    Node* prev = NULL;

    while (curr != NULL) {
        if (curr->value == key) {
            if (prev == NULL) {
                table[index] = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Impressão da tabela hash
void printTable(Node** table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("[%d]: ", i);
        Node* curr = table[i];
        while (curr != NULL) {
            printf("%d -> ", curr->value);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

// Fator de carga: número de elementos / tamanho da tabela
float loadFactor(Node** table) {
    int count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = table[i];
        while (curr != NULL) {
            count++;
            curr = curr->next;
        }
    }
    return (float)count / HASH_SIZE;
}

int main() {
    Node* hashTable[HASH_SIZE] = {NULL};
    int arr[] = {190, 322, 172, 89, 13, 4, 769, 61, 15, 76};

    // Inserção
    for (int i = 0; i < 10; i++) {
        printf("h(%3d) = %d\n", arr[i], h(arr[i]));
        insert(hashTable, arr[i]);
    }

    printf("\nTabela Hash apos insercoes:\n");
    printTable(hashTable);

    // Remoção de alguns elementos
    removeKey(hashTable, 13);
    removeKey(hashTable, 76);

    printf("\nTabela Hash apos remocoes (13 e 76):\n");
    printTable(hashTable);

    // Fator de carga
    printf("\nFator de carga final: %.2f\n", loadFactor(hashTable));

    // Liberação de memória
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hashTable[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    return 0;
}