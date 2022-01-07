#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TREE_H__
#define TREE_H__

// 二叉树节点定义
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#endif

struct TreeNode* buildTree(int *inorder, int inorderSize, int *postorder, int postorderSize) {
    if (postorderSize <= 0) return NULL;
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize - 1];
    int pivot = 0;
    while (pivot < inorderSize && inorder[pivot] != postorder[postorderSize - 1]) pivot++;
    root->left = buildTree(inorder, pivot, postorder, pivot);
    root->right = buildTree(inorder + pivot + 1, inorderSize - pivot - 1, postorder + pivot, postorderSize - pivot - 1);
    return root;
}

int treeSize(struct TreeNode *root) {
    if (root == NULL) return 0;
    return treeSize(root->left) + treeSize(root->right) + 1;
}

void inorderTraversalHelper(struct TreeNode *root, int *result, int *returnSize) {
    if (root == NULL) {
        return;
    }
    inorderTraversalHelper(root->left, result, returnSize);

    (*returnSize)++;
    result[(*returnSize) - 1] = root->val;

    inorderTraversalHelper(root->right, result, returnSize);
}

int* inorderTraversal(struct TreeNode *root, int *returnSize) {
    int size = treeSize(root);
    int *result = (int*)malloc(size * sizeof(int));
    *returnSize = 0;
    memset(result, 0, size);
    inorderTraversalHelper(root, result, returnSize);
    return result;
}

int main(int argc, char* argv[]) {
    int size = 3;
    int inorders[] = {1, 3, 2};
    int postorders[] = {3, 2, 1};
    // int inorders[] = {11, 9, 8, 3, 15, 20, 7};
    // int postorders[] = {11, 8, 9, 15, 7, 20, 3};
    struct TreeNode *root = buildTree(inorders, size, postorders, size);
    int returnSize = 0;
    int *result = inorderTraversal(root, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    return 0;
}