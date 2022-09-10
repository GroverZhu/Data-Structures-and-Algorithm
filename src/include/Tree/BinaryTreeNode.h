
#ifndef BINARY_TREE_H__
#define BINARY_TREE_H__

#include <string>
#include <vector>

// 二叉树节点定义
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;

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

TreeNode* buildTreeFromPreOrderAndInorderSerial(std::vector<int>& preorder, int pre_bgn, int pre_end,
                                                std::vector<int>& inorder, int in_bgn, int in_end) {
    if (pre_bgn > pre_end) return nullptr;
    TreeNode* root = new TreeNode(preorder[pre_bgn]);

    int pivot = preorder[pre_bgn];
    int index = in_bgn;

    while (index <= in_end && inorder[index] != pivot) ++index;

    int size = index - in_bgn;

    root->left =
        buildTreeFromPreOrderAndInorderSerial(preorder, pre_bgn + 1, pre_bgn + size, inorder, in_bgn, index - 1);
    root->right = buildTreeFromPreOrderAndInorderSerial(preorder, pre_bgn + size + 1, pre_end, inorder,
                                                        in_bgn + size + 1, in_end);

    return root;
}

/**
 * @brief 根据前序遍历的结果创建二叉树，有空节点的话，以"#"表示
 * @param data "1,2,4,#,#,5,#,#,3,#,#"
 * @return TreeNode* 根节点
 */
TreeNode* deserialBinaryTree(std::string& data) {
    if (data[0] == '#') {
        if (data.size() > 2) {
            data = data.substr(2);
        }
        return nullptr;
    }

    int index = data.find(",");
    int val = stoi(data.substr(0, index));
    data = data.substr(index + 1);
    TreeNode* root = new TreeNode(val);
    root->left = deserialBinaryTree(data);
    root->right = deserialBinaryTree(data);
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