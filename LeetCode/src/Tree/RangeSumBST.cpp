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

int rangeSumBST(struct TreeNode *root, int L, int R) {
    if (!root) return 0;
    int val = root->val;
    if (val > R) return rangeSumBST(root->left, L, R);
    if (val < L) return rangeSumBST(root->right, L, R);
    return val + rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);
}

int main(int argc, char* argv[]) {
    return 0;
}