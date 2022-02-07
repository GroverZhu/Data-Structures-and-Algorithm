
#ifndef BINARY_TREE_H__
#define BINARY_TREE_H__

#include <vector>

// 二叉树节点定义
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;

    TreeNode() {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int val) {
        this->val = val;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode* buildTreeFromPreOrderAndInorderSerial(std::vector<int>& preorder, int pre_bgn, int pre_end, std::vector<int>& inorder, int in_bgn, int in_end) {
    if (pre_bgn > pre_end) return nullptr;
    TreeNode* root = new TreeNode(preorder[pre_bgn]);

    int pivot = preorder[pre_bgn];
    int index = in_bgn;

    while (index <= in_end && inorder[index] != pivot) ++index;

    int size = index - in_bgn;

    root->left = buildTreeFromPreOrderAndInorderSerial(preorder, pre_bgn + 1, pre_bgn + size, inorder, in_bgn, index - 1);
    root->right = buildTreeFromPreOrderAndInorderSerial(preorder, pre_bgn + size + 1, pre_end, inorder, in_bgn + size + 1, in_end);

    return root;

}

void destroyTree(TreeNode* root) {
    if (!root) return;
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
    root = nullptr;
}

#endif