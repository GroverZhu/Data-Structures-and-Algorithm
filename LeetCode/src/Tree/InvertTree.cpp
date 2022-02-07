#include <iostream>

#include "../../include/Tree/BinaryTreeNode.h"


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