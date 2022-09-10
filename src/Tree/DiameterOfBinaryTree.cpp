#include <cassert>
#include <iostream>

#include "Tree/BinaryTreeNode.h"

using namespace std;

int diameterHelper(TreeNode* root, int& ans) {
    if (!root) return 0;
    int left = diameterHelper(root->left, ans);
    int right = diameterHelper(root->right, ans);
    ans = max(ans, left + right);
    return 1 + max(left, right);
}
// https://leetcode-cn.com/problems/diameter-of-binary-tree/
int diameterOfBinaryTree(TreeNode* root) {
    int ans = 0;
    diameterHelper(root, ans);
    return ans;
}

int main(int argc, char* argv[]) {
    string data = "1,2,4,#,#,5,#,#,3,#,#";
    auto root = deserialBinaryTree(data);
    assert(3 == diameterOfBinaryTree(root));
    destroyTree(root);
    return 0;
}