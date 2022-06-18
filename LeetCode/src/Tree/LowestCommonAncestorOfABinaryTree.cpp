#include <cassert>
#include <iostream>

#include "Tree/BinaryTreeNode.h"

using namespace std;

// https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return root;
    if (root->val == p->val || root->val == q->val) return root;

    auto left = lowestCommonAncestor(root->left, p, q);
    auto right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root;
    if (!left) return right;
    if (!right) return left;
    return nullptr;
}

int main(int argc, char* argv[]) {
    string data = "3,5,6,#,#,2,7,#,#,4,#,#,1,0,#,#,8,#,#";
    auto root = deserialBinaryTree(data);
    auto ancestor = lowestCommonAncestor(root, root->left->left, root->left->right);
    assert(ancestor->val == root->left->val);
    ancestor = lowestCommonAncestor(root, root->right->left, root->right->right);
    assert(ancestor->val == root->right->val);

    destroyTree(root);
    return 0;
}