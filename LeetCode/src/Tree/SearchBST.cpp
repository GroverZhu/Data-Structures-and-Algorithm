#include <iostream>
#include <vector>
#include <cassert>

#include "../include/Tree/BinaryTreeNode.h"

using namespace std;

// https://leetcode-cn.com/problems/search-in-a-binary-search-tree/
TreeNode* searchBST(TreeNode *root, int val) {
    if (root) {
        if (val < root->val) return searchBST(root->left, val);
        if (val > root->val) return searchBST(root->right, val);
        if (root->val == val) return root;
    }
    return nullptr;
}


int main(int argc, char* argv[]) {
    vector<int> preorder = {4, 2, 1, 3, 7};
    vector<int> inorder = {1, 2, 3, 4, 7};
    int size = static_cast<int>(preorder.size());
    auto root = buildTreeFromPreOrderAndInorderSerial(preorder, 0, size - 1, inorder, 0, size - 1);
    auto find = searchBST(root, 2);
    assert(2 == find->val);
    find = searchBST(root, 5);
    assert(nullptr == find);
    destroyTree(root);
    return 0;
}