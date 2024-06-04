#include <stdio.h>
#include <stdlib.h>

int opcount = 0;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int countNodes(struct TreeNode* root) {
    if (root == NULL) 
        return 0;
    else{
        opcount++;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
}

int main() {
    struct TreeNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->left->right->left = newNode(6);
    root->left->right->right = newNode(7);
    
    int totalNodes = countNodes(root);
    printf("Total number of nodes in the binary tree: %d\n", totalNodes);
    printf("Opcount is : %d\n",opcount);
    
    return 0;
}
