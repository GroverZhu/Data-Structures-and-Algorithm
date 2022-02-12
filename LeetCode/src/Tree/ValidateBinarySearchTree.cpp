#include <iostream>
#include <climits>
#include <cassert>

#include "Tree/BinaryTreeNode.h"

using namespace std;

bool isValidBSTHelper(TreeNode* root, long long left, long long right) {
    if (!root) return true;
    bool result = (root->val > left && root->val < right);
    if (!result) return result;
    result = result && isValidBSTHelper(root->left, left, root->val);
    if (!result) return result;
    result = result && isValidBSTHelper(root->right, root->val, right);
    return result;
}

// https://leetcode-cn.com/problems/validate-binary-search-tree/
bool isValidBST(TreeNode* root) {
    return isValidBSTHelper(root, LONG_LONG_MIN, LONG_LONG_MAX);
}

int main(int argc, char* argv[]) {
    string data = "2,1,#,#,3,#,#";
    auto root = deserialBinaryTree(data);
    assert(true == isValidBST(root));
    destroyTree(root);


    data = "5,1,#,#,4,3,#,#,6,#,#";
    root = deserialBinaryTree(data);
    assert(false == isValidBST(root));
    destroyTree(root);
    return 0;
}