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

    return root;
}

TreeNode* create_tree(int* n) {
    TreeNode* root = NULL;
    for (size_t i = 0; i < ARR_SIZE; i++) {
        root = insert(root, n[i]);
    }

    return root;
}

// ARVORE AVL
int main(int argc, char const *argv[])
{
    int arr[] = {21,26,30,9,4,14,28,18,15,10,2,3,7};
    TreeNode* t = create_tree(arr);

    for(size_t i = 0; i < ARR_SIZE; i++){
        printf("%d ", t->value);
    }
    

    return 0;
}
