#include <stdio.h>


#ifndef TREE_H__
#define TREE_H__

// 二叉树节点定义
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#endif

struct TreeNode* invertTree(struct TreeNode *root) {
    if (!root) return NULL;
    struct TreeNode *left = invertTree(root->left);
    struct TreeNode *right = invertTree(root->right);

    root->left = right;
    root->right = left;

    return root;
}

int main(int argc, char* argv[]) {
    return 0;
}