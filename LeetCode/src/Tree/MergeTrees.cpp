#include <iostream>
#include <vector>

#include "../../include/Tree/BinaryTreeNode.h"

using namespace std;

struct TreeNode* mergeTrees(struct TreeNode *t1, struct TreeNode *t2) {
    if (t1 == nullptr && t2 == nullptr) return nullptr;
    if (t1 != nullptr && t2 == nullptr) return t1;
    if (t1 == nullptr && t2 != nullptr) return t2;  
    t1->val += t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    return t1;
}

int main() {
    vector<int> pre1 = {1, 3, 5, 2};
    vector<int> in1 = {5, 3, 1, 2};
    int size1 = 4;
    vector<int> pre2 = {2, 1, 4, 3, 7};
    vector<int> in2 = {1, 4, 2, 3, 7};
    int size2 = 5;
    struct TreeNode *root1 = buildTreeFromPreOrderAndInorderSerial(pre1, 0, size1 - 1, in1, 0, size1 - 1);
    struct TreeNode *root2 = buildTreeFromPreOrderAndInorderSerial(pre2, 0, size2 - 1, in2, 0, size2 - 1);
    struct TreeNode *merge = mergeTrees(root1, root2);
    merge = nullptr;
    return 0;
}
