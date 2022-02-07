#include <iostream>

#include "../../include/Tree/BinaryTreeNode.h"

using namespace std;

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