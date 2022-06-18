#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Tree/BinaryTreeNode.h"

using namespace std;

// https://leetcode-cn.com/problems/house-robber/
int rob(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    if (size == 1) return nums[0];
    if (size == 2) return max(nums[0], nums[1]);
    vector<int> profits(size, 0);
    profits[0] = nums[0];
    profits[1] = max(nums[0], nums[1]);
    for (int i = 2; i < size; i++) {
        profits[i] = max(profits[i - 2] + nums[i], profits[i - 1]);
    }

    return profits[size - 1];
}

// https://leetcode-cn.com/problems/house-robber-ii/
// [begin, end]
int robIIHelper(vector<int>& nums, int begin, int end) {
    int size = end - begin + 1;
    if (size == 1) return nums[begin];
    if (size == 2) return max(nums[begin], nums[end]);
    vector<int> profits(size, 0);
    profits[0] = nums[begin];
    profits[1] = max(nums[begin], nums[begin + 1]);

    for (int i = 2; i < size; i++) {
        profits[i] = max(profits[i - 1], profits[i - 2] + nums[begin + i]);
    }

    return profits[size - 1];
}
int robII(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    if (size == 1) return nums[0];
    if (size == 2) return max(nums[0], nums[1]);
    return max(robIIHelper(nums, 1, size - 1), robIIHelper(nums, 0, size - 2));
}

// https://leetcode-cn.com/problems/house-robber-iii/
// 返回值为偷/不偷当前获得最大的收益
pair<int, int> robIIIHelper(TreeNode* root) {
    if (!root) return {0, 0};
    if (!root->left && !root->right) return {root->val, 0};
    auto left = robIIIHelper(root->left);
    auto right = robIIIHelper(root->right);
    return {left.second + right.second + root->val, max(left.first, left.second) + max(right.first, right.second)};
}
int robIII(TreeNode* root) {
    auto result = robIIIHelper(root);
    return max(result.first, result.second);
}

int main(int argc, char* argv[]) {
    // https://leetcode-cn.com/problems/house-robber/
    vector<int> nums;

    nums = {1, 2, 3, 1};
    assert(4 == rob(nums));

    nums = {2, 7, 9, 3, 1};
    assert(12 == rob(nums));

    // https://leetcode-cn.com/problems/house-robber-ii/
    nums = {2, 3, 2};
    assert(3 == robII(nums));

    nums = {1, 2, 3, 1};
    assert(4 == robII(nums));

    nums = {1, 2, 3};
    assert(3 == robII(nums));

    // https://leetcode-cn.com/problems/house-robber-iii/
    string s = "3,2,#,3,#,#,3,#,1,#,#";
    auto root = deserialBinaryTree(s);
    assert(7 == robIII(root));
    destroyTree(root);

    s = "3,4,1,#,#,3,#,#,5,#,1,#,#";
    root = deserialBinaryTree(s);
    assert(9 == robIII(root));
    destroyTree(root);

    s = "4,1,2,3,#,#,#";
    root = deserialBinaryTree(s);
    assert(7 == robIII(root));
    destroyTree(root);

    s = "2,1,#,4,#,#,3,#,#";
    root = deserialBinaryTree(s);
    assert(7 == robIII(root));
    destroyTree(root);

    return 0;
}