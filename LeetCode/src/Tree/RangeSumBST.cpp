#include <iostream>
#include <vector>
#include <cassert>

#include "Tree/BinaryTreeNode.h"

using namespace std;

// https://leetcode-cn.com/problems/range-sum-of-bst/
int rangeSumBST(TreeNode* root, int low, int high) {
    if (!root) return 0;
    int val = root->val;
    if (val > high) return rangeSumBST(root->left, low, high);
    if (val < low) return rangeSumBST(root->right, low, high);
    return val + rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high);
}

int main(int argc, char* argv[]) {
    vector<int> preorder = {10, 5, 3, 7, 15, 18};
    vector<int> inorder = {3, 5, 7, 10, 15, 18};
    int size = static_cast<int>(preorder.size());
    auto root = buildTreeFromPreOrderAndInorderSerial(preorder, 0, size - 1, inorder, 0, size - 1);
    assert(32 == rangeSumBST(root, 7, 15));
    destroyTree(root);

    preorder = {10, 5, 3, 1, 7, 6, 15, 13, 18};
    inorder = {1, 3, 5, 6, 7, 10, 13, 15, 18};
    size = static_cast<int>(preorder.size());
    root = buildTreeFromPreOrderAndInorderSerial(preorder, 0, size - 1, inorder, 0, size - 1);
    assert(23 == rangeSumBST(root, 6, 10));
    destroyTree(root);

    return 0;
}