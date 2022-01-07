#include <stdio.h>
#include <stdlib.h>

#ifndef TREE_H__
#define TREE_H__

// 二叉树节点定义
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#endif


struct TreeNode* buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize) {
    if (preorderSize <= 0) return NULL;
    
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    int i = 0;
    while (i < inorderSize && inorder[i] != preorder[0]) i++;
    root->left = buildTree(preorder + 1, i, inorder, i);
    root->right = buildTree(preorder + i + 1, preorderSize - i - 1, inorder + i + 1, inorderSize - i - 1);
    return root;
}

struct TreeNode* mergeTrees(struct TreeNode *t1, struct TreeNode *t2) {
    if (t1 == NULL && t2 == NULL) return NULL;
    if (t1 != NULL && t2 == NULL) return t1;
    if (t1 == NULL && t2 != NULL) return t2;  
    t1->val += t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    return t1;
}

int main() {
    int pre1[] = {1, 3, 5, 2};
    int in1[] = {5, 3, 1, 2};
    int size1 = 4;
    int pre2[] = {2, 1, 4, 3, 7};
    int in2[] = {1, 4, 2, 3, 7};
    int size2 = 5;
    struct TreeNode *root1 = buildTree(pre1, size1, in1, size1);
    struct TreeNode *root2 = buildTree(pre2, size2, in2, size2);
    struct TreeNode *merge = mergeTrees(root1, root2);
    merge = nullptr;
    return 0;
}
