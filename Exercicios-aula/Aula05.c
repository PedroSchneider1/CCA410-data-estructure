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

TreeNode* remove_value(TreeNode* root, int value){
    if (root == NULL)
        return NULL;

    // procura o valor na arvore
    if (value < root->value) {
        root->left = remove_value(root->left, value);
    } else if (value > root->value) {
        root->right = remove_value(root->right, value);
    } else {
        // remove o valor
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        } else {
            TreeNode* temp = find_max(root->left);
            root->value = temp->value;
            root->left = remove_value(root->left, temp->value);
        }
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

    printf("\nArray apos inserir 15: ");
    insert(t, 15);
    print_order(t);

    printf("\nArray apos remover 7: ");
    remove_value(t, 7);
    print_order(t);

    free(t);

    return 0;
}
