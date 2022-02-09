#include <iostream>
#include <vector>
#include <stack>
#include <cassert>

#include "Tree/BinaryTreeNode.h"

using namespace std;

// https://leetcode-cn.com/problems/merge-two-binary-trees/
TreeNode* mergeTrees(TreeNode *t1, TreeNode *t2) {
    if (t1 == nullptr && t2 == nullptr) return nullptr;
    if (t1 != nullptr && t2 == nullptr) return t1;
    if (t1 == nullptr && t2 != nullptr) return t2;  
    t1->val += t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    // 避免内存泄露， 删除t2树，保留t1树
    delete t2;
    t2 = nullptr;
    return t1;
}

bool isSameTree(TreeNode* root1, TreeNode* root2) {
    if (!root1 && !root2) return true;
    if (!root1 || !root2) return false;
    return root1->val == root2->val && 
           isSameTree(root1->left, root2->left) &&
           isSameTree(root1->right, root2->right);
}

int main() {
    auto preorder = [](TreeNode* root) {
        vector<int> pre;
        if (!root) return pre;
        stack<TreeNode*> stk;
        stk.push(root);

        while (!stk.empty()) {
            auto node = stk.top();
            stk.pop();
            pre.emplace_back(node->val);
            if (node->right) stk.push(node->right);
            if (node->left) stk.push(node->left);
        }

        return pre;
    };

    auto inorder = [](TreeNode* root) {
        vector<int> in;
        if (!root) return in;
        TreeNode* cur = root;
        stack<TreeNode*> stk;

        while (cur || !stk.empty()) {
            if (cur) {
                stk.push(cur);
                cur = cur->left;
            } else {
                cur = stk.top();
                stk.pop();
                in.push_back(cur->val);
                cur = cur->right;
            }
        }

        return in;
    };
    vector<int> pre1 = {1, 3, 5, 2};
    vector<int> in1 = {5, 3, 1, 2};
    int size1 = static_cast<int>(pre1.size());
    vector<int> pre2 = {2, 1, 4, 3, 7};
    vector<int> in2 = {1, 4, 2, 3, 7};
    int size2 = static_cast<int>(pre2.size());
    struct TreeNode *root1 = buildTreeFromPreOrderAndInorderSerial(pre1, 0, size1 - 1, in1, 0, size1 - 1);
    struct TreeNode *root2 = buildTreeFromPreOrderAndInorderSerial(pre2, 0, size2 - 1, in2, 0, size2 - 1);
    struct TreeNode *merge = mergeTrees(root1, root2);
    vector<int> pre3 = {3, 4, 5, 4, 5, 7};
    vector<int> in3 = {5, 4, 4, 3, 5, 7};
    auto tmp_pre = preorder(merge);
    auto tmp_in = inorder(merge);

    // for (auto num : tmp_pre) {
    //     cout << num << "\t";
    // }
    // cout << endl;

    // for (auto num : tmp_in) {
    //     cout << num << "\t";
    // }
    // cout << endl;

    assert(pre3 == tmp_pre);
    assert(in3 == tmp_in);

    destroyTree(merge);
    return 0;
}
