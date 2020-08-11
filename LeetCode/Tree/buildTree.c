#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/**
 * 根据前序遍历与中序遍历建立二叉树
 * @param preorder 前序遍历的结果
 * @param preorderSize 前序遍历的长度
 * @param inorder 中序遍历
 * @param inorderSize 中序遍历长度
 * @return root 二叉树的根节点
 */ 
struct TreeNode* preInorderBuildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (preorderSize <= 0) return NULL;
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    int i = 0;
    while (i < preorderSize && inorder[i] != preorder[0]) i++;
    root->left = preInorderBuildTree(preorder+1, i, inorder, i);
    root->right = preInorderBuildTree(preorder + 1 + i, preorderSize - i - 1, inorder + i + 1, inorderSize - i - 1);
    return root;
}

/**
 * 根据中序与后序遍历遍历建立二叉树
 * @param inorder 中序遍历
 * @param inorderSize 中序遍历长度
 * @param postorder 后序遍历的结果
 * @param postorderSize 后序遍历的长度
 * @return root 二叉树的根节点
 */ 
struct TreeNode* inPostorderBuildTree(int* inorder, int inorderSize, int *postorder, int postorderSize) {
    if (postorderSize <= 0) return NULL;
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize - 1];
    int i = 0;
    while (i < postorderSize && inorder[i] != postorder[postorderSize - 1]) i++;
    root->left = inPostorderBuildTree(inorder, i, postorder, i);
    root->right = inPostorderBuildTree(inorder + i + 1, inorderSize - i - 1, postorder + i, postorderSize - i - 1);

    return root;
}

/**
 * 根据二叉搜索树的前序遍历结果建立二叉搜索树
 * @param preorder 前序遍历结果
 * @param preorderSize 前序遍历的长度
 * @return root 二叉搜索树的根节点
 */
struct TreeNode* bstFromPreorder(int* preorder, int preorderSize){
    if (preorderSize <= 0) return NULL;
    struct TreeNode *root = malloc(sizeof(struct TreeNode));
    int pivot = preorder[0];
    root->val = pivot;
    int i = 0;
    while (i < preorderSize && preorder[i] <= pivot) i++;
    root->left = bstFromPreorder(preorder + 1, i - 1);
    root->right = bstFromPreorder(preorder + i, preorderSize - i);
    return root;
}

void inorder(struct TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void preorder(struct TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct TreeNode *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}

int main() {
    int size = 6;
    int preorders[] = {8,5,1,7,10,12};
    struct TreeNode *root = bstFromPreorder(preorders, size);
    // int preorders[] = {3, 9, 11, 8, 20, 15, 7};
    // int inorders[] = {11, 9, 8, 3, 15, 20, 7};
    // int postorders[] = {11, 8, 9, 15, 7, 20, 3};
    // struct TreeNode *root = inPostorderBuildTree(inorders, size, postorders, size);
    preorder(root);
    printf("\n");
    inorder(root);
    printf("\n");
    postorder(root);
}