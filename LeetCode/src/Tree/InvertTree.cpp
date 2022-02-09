#include <iostream>
#include <vector>
#include <cassert>

#include "Tree/BinaryTreeNode.h"

using namespace std;

// https://leetcode-cn.com/problems/invert-binary-tree/

TreeNode* invertTree(TreeNode *root) {
    if (!root) return NULL;
    TreeNode *left = invertTree(root->left);
    TreeNode *right = invertTree(root->right);

    root->left = right;
    root->right = left;

    return root;
}

bool isSameTree(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) return true;
    if (!root1 || !root2) return false;
    return root1->val == root2->val && 
           isSameTree(root1->left, root2->left) &&
           isSameTree(root1->right, root2->right);
}

int main(int argc, char* argv[]) {
    vector<int> pre1, in1, pre2, in2;
    int size;

    pre1 = {4, 2, 1, 3, 7, 6, 9};
    in1 = {1, 2, 3, 4, 6, 7, 9};
    size = static_cast<int>(pre1.size());
    auto root1 = buildTreeFromPreOrderAndInorderSerial(pre1, 0, size - 1, in1, 0, size - 1);
    root1 = invertTree(root1);
    pre2 = {4, 7, 9, 6, 2, 3, 1};
    in2 = {9, 7, 6, 4, 3, 2, 1};
    auto root2 = buildTreeFromPreOrderAndInorderSerial(pre2, 0, size - 1, in2, 0, size - 1);
    assert(true == isSameTree(root1, root2));
    destroyTree(root1);
    destroyTree(root2);

    pre1 = {2, 1, 3};
    in1 = {1, 2, 3};
    size = static_cast<int>(pre1.size());
    root1 = buildTreeFromPreOrderAndInorderSerial(pre1, 0, size - 1, in1, 0, size - 1);
    root1 = invertTree(root1);
    pre2 = {2, 3, 1};
    in2 = {3, 2, 1};
    root2 = buildTreeFromPreOrderAndInorderSerial(pre2, 0, size - 1, in2, 0, size - 1);
    assert(true == isSameTree(root1, root2));
    destroyTree(root1);
    destroyTree(root2);

    return 0;
}