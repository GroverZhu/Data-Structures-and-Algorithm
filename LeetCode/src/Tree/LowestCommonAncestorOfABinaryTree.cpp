#include <cassert>
#include <iostream>
#include <map>
#include <set>

#include "Tree/BinaryTreeNode.h"

using namespace std;

// https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
// 递归解法
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

void preorder(TreeNode* root, map<TreeNode*, TreeNode*>& childToParent) {
    if (!root) {
        return;
    }

    if (root->left) {
        childToParent[root->left] = root;
    }
    if (root->right) {
        childToParent[root->right] = root;
    }

    preorder(root->left, childToParent);
    preorder(root->right, childToParent);
}

// 迭代解法
TreeNode* lowestCommonAncestorIter(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root->val == p->val || root->val == q->val) {
        return root;
    }
    map<TreeNode*, TreeNode*> childToParent;
    childToParent[root] = nullptr;
    preorder(root, childToParent);

    set<TreeNode*> first;
    TreeNode* cur = p;
    while (cur != nullptr) {
        first.insert(cur);
        cur = childToParent[cur];
    }

    cur = q;
    while (cur != nullptr) {
        if (first.find(cur) != first.end()) {
            return cur;
        }
        cur = childToParent[cur];
    }

    return nullptr;
}

int main(int argc, char* argv[]) {
    string data = "3,5,6,#,#,2,7,#,#,4,#,#,1,0,#,#,8,#,#";
    auto root = deserialBinaryTree(data);
    lowestCommonAncestorIter(root, root->left->left, root->left->right);
    auto ancestor = lowestCommonAncestor(root, root->left->left, root->left->right);
    assert(ancestor->val == root->left->val);
    ancestor = lowestCommonAncestor(root, root->right->left, root->right->right);
    assert(ancestor->val == root->right->val);

    destroyTree(root);
    return 0;
}