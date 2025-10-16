#include <stdio.h>
#include <stdlib.h>

/*
Faça a inserção dos seguintes valores em uma árvore AVL:
21, 26, 30, 9, 4, 14, 28, 18, 15, 10, 2, 3, 7
Lembre-se, para cada valor inserido:
- Calcule o fator de balanceamento de cada nó;
- Caso haja desbalanceamento, então faça as rotações necessárias
*/

#define ARR_SIZE 13

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

int height(TreeNode* node) {
    if (node == NULL)
        return 0;
    
    int left_height = height(node->left);
    int right_height = height(node->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}


int fb(TreeNode* v) {
    if (v == NULL)
        return 0;
    return height(v->left) - height(v->right);
}

TreeNode* rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T = x->right;
    
    x->right = y;
    y->left = T;

    return x;
}

TreeNode* rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T = y->left;
    
    y->left = x;
    x->right = T;

    return y;
}

TreeNode* insert(TreeNode* root, int value) {
    if (root == NULL) {
        TreeNode* new_node = malloc(sizeof(TreeNode));
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }

    if (value < root->value)
        root->left = insert(root->left, value);
    else if (value > root->value)
        root->right = insert(root->right, value);
    else
        return root; // valores duplicados não são permitidos

    int balance = fb(root);

    // Caso Esquerda-Esquerda
    if (balance > 1 && value < root->left->value)
        return rotateRight(root);

    // Caso Direita-Direita
    if (balance < -1 && value > root->right->value)
        return rotateLeft(root);

    // Caso Esquerda-Direita
    if (balance > 1 && value > root->left->value) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Caso Direita-Esquerda
    if (balance < -1 && value < root->right->value) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

TreeNode* create_tree(int* n) {
    TreeNode* root = NULL;
    for (size_t i = 0; i < ARR_SIZE; i++) {
        root = insert(root, n[i]);
    }

    return root;
}

void printInOrder(TreeNode* root) {
    if (root != NULL) {
        printInOrder(root->left);
        printf("%d ", root->value);
        printInOrder(root->right);
    }
}

// ARVORE AVL
int main() {
    int arr[] = {21, 26, 30, 9, 4, 14, 28, 18, 15, 10, 2, 3, 7};
    TreeNode* t = create_tree(arr);

    printf("Arvore AVL em ordem: ");
    printInOrder(t);
    printf("\n");

    return 0;
}

