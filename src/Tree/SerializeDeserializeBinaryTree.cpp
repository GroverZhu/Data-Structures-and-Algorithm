#include <cassert>
#include <iostream>
#include <string>

#include "Tree/BinaryTreeNode.h"

using namespace std;

string serialize(TreeNode* root) {
    if (!root) return "#";
    // 前序遍历
    string result = to_string(root->val) + ",";
    result += serialize(root->left) + ",";
    result += serialize(root->right);

    return result;
}

TreeNode* deserializeHelper(string& data) {
    if (data[0] == '#') {
        if (data.size() > 2) {
            data = data.substr(2);
        }
        return nullptr;
    }
    int pos = data.find(',');
    int val = stoi(data.substr(0, pos));
    data = data.substr(pos + 1);
    TreeNode* root = new TreeNode(val);
    root->left = deserializeHelper(data);
    root->right = deserializeHelper(data);
    return root;
}

TreeNode* deserialize(string data) { return deserializeHelper(data); }

// https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/
int main(int argc, char* argv[]) {
    string data = "1,2,#,#,3,4,#,#,5,#,#";
    auto root = deserialize(data);
    auto result = serialize(root);
    assert(result == data);
    destroyTree(root);

    data = "12,22,#,#,31,444,#,#,50,#,#";
    root = deserialize(data);
    result = serialize(root);
    assert(result == data);
    destroyTree(root);

    return 0;
}