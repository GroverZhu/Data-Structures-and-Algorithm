#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// [begin, end)
int dfs(vector<int>& nums, int begin, int end) {
    if (begin + 1 == end) return nums[begin];

    int mid = (end - begin) / 2 + begin;

    int left = dfs(nums, begin, mid);
    int right = dfs(nums, mid, end);

    if (left == right) return nums[left];

    int leftCount = 0, rightCount = 0;
    for (int i = begin; i < end; i++) {
        if (nums[i] == left) ++leftCount;
        if (nums[i] == right) ++rightCount;
    }
    return leftCount < rightCount ? right : left;
}

// https://leetcode-cn.com/problems/majority-element/
int majorityElement(vector<int>& nums) {
#if 0
    // 摩尔投票法
    int size = static_cast<int>(nums.size());
    if (size <= 2) return nums[0];

    int result = nums[0];
    int cnt = 1;
    int index = 1;

    while (index < size) {
        if (result != nums[index]) {
            --cnt;
            if (cnt == 0) {
                result = nums[index];
                cnt = 1;
            }
        } else {
            ++cnt;
        }
        index++;
    }
    return result;
#endif

#if 1
    // 递归
    int size = static_cast<int>(nums.size());
    return dfs(nums, 0, size);
#endif
}

int main() {
    vector<int> nums;
    int ans, result;

    nums = {3, 2, 3};
    ans = 3;
    result = majorityElement(nums);
    assert(result == ans);
    
    nums = {2,2,1,1,1,2,2};
    ans = 2;
    result = majorityElement(nums);
    assert(result == ans);
    return 0;
}