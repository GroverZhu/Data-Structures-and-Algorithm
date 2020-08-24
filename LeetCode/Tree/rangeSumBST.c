#include <stdio.h>

#include "tree.h"

int rangeSumBST(struct TreeNode *root, int L, int R) {
    if (!root) return 0;
    int val = root->val;
    if (val > R) return rangeSumBST(root->left, L, R);
    if (val < L) return rangeSumBST(root->right, L, R);
    return val + rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);
}