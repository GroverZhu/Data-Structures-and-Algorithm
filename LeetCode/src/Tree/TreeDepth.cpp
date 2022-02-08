#include <iostream>

#include "../include/Tree/BinaryTreeNode.h"

using namespace std;

// 求最大深度 https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/
int maxDepth(TreeNode* root){
    if (root == nullptr) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return max(left, right) + 1;
}


// 求最小深度 https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/
int minDepth(TreeNode* root){
    if (root == nullptr) return 0;
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
    vector<int> pre, in;
    int size;

    pre = {};
    in = {};
    size = static_cast<int>(pre.size());
    auto root = buildTreeFromPreOrderAndInorderSerial(pre, 0, size - 1, in, 0, size - 1);
    assert(0 == minDepth(root));
    assert(0 == maxDepth(root));
    destroyTree(root);

    pre = {3, 9, 20, 15, 7};
    in = {9, 3, 15, 20, 7};
    size = static_cast<int>(pre.size());
    root = buildTreeFromPreOrderAndInorderSerial(pre, 0, size - 1, in, 0, size - 1);
    assert(2 == minDepth(root));
    assert(3 == maxDepth(root));
    destroyTree(root);

    pre = {1, 2, 3};
    in = {3, 2, 1};
    size = static_cast<int>(pre.size());
    root = buildTreeFromPreOrderAndInorderSerial(pre, 0, size - 1, in, 0, size - 1);
    assert(3 == minDepth(root));
    assert(3 == maxDepth(root));
    destroyTree(root);

    return 0;
}