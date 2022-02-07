#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <cassert>

#include "../../include/Tree/BinaryTreeNode.h"

using namespace std;


// 从前序与中序遍历序列 https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// [pre_bgn, pre_end], [in_bgn, in_end]
TreeNode* buildTreeFromPreOrderAndInorder(vector<int>& preorder, int pre_bgn, int pre_end, vector<int>& inorder, int in_bgn, int in_end) {
    if (pre_bgn > pre_end) return nullptr;
    TreeNode* root = new TreeNode(preorder[pre_bgn]);

    int pivot = preorder[pre_bgn];
    int index = in_bgn;

    while (index <= in_end && inorder[index] != pivot) ++index;

    int size = index - in_bgn;

    root->left = buildTreeFromPreOrderAndInorder(preorder, pre_bgn + 1, pre_bgn + size, inorder, in_bgn, index - 1);
    root->right = buildTreeFromPreOrderAndInorder(preorder, pre_bgn + size + 1, pre_end, inorder, in_bgn + size + 1, in_end);

    return root;

}

TreeNode* buildTreeFromPreIn(vector<int>& preorder, vector<int>& inorder) {
    int pre_size = preorder.size();
    int in_size = inorder.size();
    if (pre_size != in_size) return nullptr;
    return buildTreeFromPreOrderAndInorder(preorder, 0, pre_size - 1, inorder, 0, in_size - 1);
}



// 后序与中序构造二叉树 https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
// 均为闭区间[in_bgn, in_end], [post_bgn, post_end]
TreeNode* buildTreeFromInorderAndPostOrder(vector<int>& inorder, int in_bgn, int in_end, vector<int>& postorder, int post_bgn, int post_end) {
    if (in_bgn > in_end) return nullptr;

    int pivot = postorder[post_end];
    TreeNode* root = new TreeNode(pivot);

    int index = in_bgn;
    while (index < in_end && inorder[index] != pivot) ++index;
    int size = index - in_bgn;

    root->left = buildTreeFromInorderAndPostOrder(inorder, in_bgn, index - 1, postorder, post_bgn, post_bgn + size - 1);
    root->right = buildTreeFromInorderAndPostOrder(inorder, index + 1, in_end, postorder, post_bgn + size, post_end - 1);

    return root;
}

TreeNode* buildTreeFromInPost(vector<int>& inorder, vector<int>& postorder) {
    int in_size = inorder.size();
    int post_size = postorder.size();
    if (in_size != post_size) return nullptr;

    return buildTreeFromInorderAndPostOrder(inorder, 0, in_size - 1, postorder, 0, post_size - 1);
}


// 前序遍历 https://leetcode-cn.com/problems/binary-tree-preorder-traversal/
vector<int> preorderTraversalIteration(TreeNode* root) {
    vector<int> result = {};
    if (!root) return result;
    stack<TreeNode*> stk;
    stk.push(root);

    while (!stk.empty()) {
        auto node = stk.top();
        stk.pop();
        result.push_back(node->val);
        if (node->right) stk.push(node->right);
        if (node->left) stk.push(node->left);
    }

    return result;
}

void preorderTraversalRecursiveHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preorderTraversalRecursiveHelper(root->left, result);
    preorderTraversalRecursiveHelper(root->right, result);
}

vector<int> preorderTraversalRecursive(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    preorderTraversalRecursiveHelper(root, result);
    return result;
}



// 中序遍历 https://leetcode-cn.com/problems/binary-tree-inorder-traversal/
vector<int> inorderTraversalIteration(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    stack<TreeNode*> stk;
    TreeNode* cur = root;
    while (cur || !stk.empty()) {
        if (cur) {
            stk.push(cur);
            cur = cur->left;
        } else {
            cur = stk.top();
            stk.pop();
            result.push_back(cur->val);
            cur = cur->right;
        }
    }
    return result;
}

void inorderTraversalRecursiveHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderTraversalRecursiveHelper(root->left, result);
    result.push_back(root->val);
    inorderTraversalRecursiveHelper(root->right, result);
}

vector<int> inorderTraversalRecursive(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    inorderTraversalRecursiveHelper(root, result);
    return result;
}



// 后序遍历 https://leetcode-cn.com/problems/binary-tree-postorder-traversal/
vector<int> postorderTraversalIteration(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    stack<TreeNode*> stk;
    deque<int> temp;
    stk.push(root);

    while (!stk.empty()) {
        auto node = stk.top();
        stk.pop();
        temp.push_front(node->val);
        if (node->left) stk.push(node->left);
        if (node->right) stk.push(node->right);
    }

    result = vector<int>(temp.begin(), temp.end());
    return result;

}

void postorderTraversalRecursiveHelper(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorderTraversalRecursiveHelper(root->left, result);
    postorderTraversalRecursiveHelper(root->right, result);
    result.push_back(root->val);
}

vector<int> postorderTraversalRecursive(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    postorderTraversalRecursiveHelper(root, result);
    return result;
}

// 层序遍历 https://leetcode-cn.com/problems/binary-tree-level-order-traversal/
vector<vector<int>> levelOrderIteration(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> temp;
        for (int i = 0; i < size; i++) {
            auto node = q.front();
            q.pop();
            temp.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(temp);
    }

    return result;
}

void levelOrderRecursiveHelper(TreeNode* root, vector<vector<int>>& result, int index) {
    if (!root) return;
    if (static_cast<int>(result.size()) <= index) result.push_back({});
    result[index].push_back(root->val);
    levelOrderRecursiveHelper(root->left, result, index + 1);
    levelOrderRecursiveHelper(root->right, result, index + 1);
}

vector<vector<int>> levelOrderRecursive(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    levelOrderRecursiveHelper(root, result, 0);
    return result;
}


int main() {
    vector<int> preorder = {3,9,20,15,7};
    vector<int> inorder = {9,3,15,20,7};
    vector<int> postorder = {9,15,7,20,3};
    vector<vector<int>> levelorder = {{3}, {9, 20}, {15, 7}};

    TreeNode* root1 = buildTreeFromPreIn(preorder, inorder);
    TreeNode* root2 = buildTreeFromInPost(inorder, postorder);

    assert(preorder == preorderTraversalIteration(root1));
    assert(preorder == preorderTraversalRecursive(root1));
    assert(preorder == preorderTraversalIteration(root2));
    assert(preorder == preorderTraversalRecursive(root2));

    assert(inorder == inorderTraversalIteration(root1));
    assert(inorder == inorderTraversalRecursive(root1));
    assert(inorder == inorderTraversalIteration(root2));
    assert(inorder == inorderTraversalRecursive(root2));

    assert(postorder == postorderTraversalIteration(root1));
    assert(postorder == postorderTraversalRecursive(root1));
    assert(postorder == postorderTraversalIteration(root2));
    assert(postorder == postorderTraversalRecursive(root2));

    assert(levelorder == levelOrderIteration(root1));
    assert(levelorder == levelOrderRecursive(root1));
    assert(levelorder == levelOrderIteration(root2));
    assert(levelorder == levelOrderRecursive(root2));

    destroyTree(root1);
    destroyTree(root2);



    preorder = {1, 2, 3};
    inorder = {1, 3, 2};
    postorder = {3, 2, 1};
    levelorder = {{1}, {2}, {3}};
    root1 = buildTreeFromPreIn(preorder, inorder);
    root2 = buildTreeFromInPost(inorder, postorder);

    assert(preorder == preorderTraversalIteration(root1));
    assert(preorder == preorderTraversalRecursive(root1));
    assert(preorder == preorderTraversalIteration(root2));
    assert(preorder == preorderTraversalRecursive(root2));

    assert(inorder == inorderTraversalIteration(root1));
    assert(inorder == inorderTraversalRecursive(root1));
    assert(inorder == inorderTraversalIteration(root2));
    assert(inorder == inorderTraversalRecursive(root2));

    assert(postorder == postorderTraversalIteration(root1));
    assert(postorder == postorderTraversalRecursive(root1));
    assert(postorder == postorderTraversalIteration(root2));
    assert(postorder == postorderTraversalRecursive(root2));

    assert(levelorder == levelOrderIteration(root1));
    assert(levelorder == levelOrderRecursive(root1));
    assert(levelorder == levelOrderIteration(root2));
    assert(levelorder == levelOrderRecursive(root2));

    destroyTree(root1);
    destroyTree(root2);


    preorder = {1, 2, 3, 4, 5};
    inorder = {2, 1, 4, 3, 5};
    postorder = {2, 4, 5, 3, 1};
    levelorder = {{1}, {2, 3}, {4, 5}};
    root1 = buildTreeFromPreIn(preorder, inorder);
    root2 = buildTreeFromInPost(inorder, postorder);
    
    assert(preorder == preorderTraversalIteration(root1));
    assert(preorder == preorderTraversalRecursive(root1));
    assert(preorder == preorderTraversalIteration(root2));
    assert(preorder == preorderTraversalRecursive(root2));

    assert(inorder == inorderTraversalIteration(root1));
    assert(inorder == inorderTraversalRecursive(root1));
    assert(inorder == inorderTraversalIteration(root2));
    assert(inorder == inorderTraversalRecursive(root2));

    assert(postorder == postorderTraversalIteration(root1));
    assert(postorder == postorderTraversalRecursive(root1));
    assert(postorder == postorderTraversalIteration(root2));
    assert(postorder == postorderTraversalRecursive(root2));

    assert(levelorder == levelOrderIteration(root1));
    assert(levelorder == levelOrderRecursive(root1));
    assert(levelorder == levelOrderIteration(root2));
    assert(levelorder == levelOrderRecursive(root2));
    
    destroyTree(root1);
    destroyTree(root2);

    return 0;
}