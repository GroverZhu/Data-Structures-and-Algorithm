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

int max(int a, int b) {
    return a >= b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

// 求最大深度
int maxDepth(struct TreeNode* root){
    if (root == NULL) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return max(left, right) + 1;
}


// 求最小深度
int minDepth(struct TreeNode* root){
    if (root == NULL) return 0;
    int left = minDepth(root->left);
    int right = minDepth(root->right);
    // 有些树仅有左子树或右子树
    if (left == 0) {
        return right + 1;
    } else if (right == 0) {
        return left + 1;
    } else {
        return min(left, right) + 1;
    }
}

int main(int argc, char* argv[]) {
    return 0;
}