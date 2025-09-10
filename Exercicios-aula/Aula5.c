#include <stdio.h>
#include <stdlib.h>

/*
Mostre inserção e remoção considerando os seguintes valores
na ordem em que aparecem:
5, 3, 7, 1, 8, 4, 6, 2, 9
*/

#define ARR_SIZE 9

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

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

TreeNode* find_max(TreeNode* node) {
    while (node->right != NULL)
        node = node->right;
    return node;
}

TreeNode* remove(TreeNode* root, int value){
    if (root == NULL)
        return NULL;

    
}

TreeNode* create_tree(int* n) {
    TreeNode* root = NULL;
    for (size_t i = 0; i < ARR_SIZE; i++) {
        root = insert(root, n[i]);
    }

    return root;
}

void print_order(TreeNode* root) {
    if (root == NULL)
        return;

    print_order(root->left);
    printf("%d ", root->value);
    print_order(root->right);
}


// ARVORES BINARIAS
int main(int argc, char const *argv[])
{
    int arr[] = {5,3,7,1,8,4,6,2,9};
    TreeNode* t = create_tree(arr);

    printf("Array original: ");
    print_order(t);

    insert(t, 15);
    
    printf("\nArray apos inserir 15: ");
    print_order(t);

    return 0;
}
