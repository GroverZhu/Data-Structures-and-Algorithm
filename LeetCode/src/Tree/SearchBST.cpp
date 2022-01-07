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

struct TreeNode* searchBST(struct TreeNode *root, int val) {
    if (root) {
        if (val < root->val) return searchBST(root->left, val);
        if (val > root->val) return searchBST(root->right, val);
        if (root->val == val) return root;
    }
    return NULL;
}


int main(int argc, char* argv[]) {
    return 0;
}