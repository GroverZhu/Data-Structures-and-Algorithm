#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/longest-subarray-of-1s-after-deleting-one-element/
int longestSubarray(vector<int>& nums) {
    int size = static_cast<int>(nums.size());

    int left = 0;
    int right = 0;
    int cnt = 0;
    int len = 0;

    while (right < size) {
        auto add = nums[right];
        right++;
        if (add == 0) {
            ++cnt;
        }

        while (cnt > 1) {
            auto del = nums[left];
            left++;
            if (del == 0) {
                --cnt;
            }
        }

        len = max(len, right - left);
    }

    return len - 1;
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int result;
    int ans;

    nums = {1, 1, 0, 1};
    ans = 3;
    result = longestSubarray(nums);
    assert(result == ans);

    nums = {0,1,1,1,0,1,1,0,1};
    ans = 5;
    result = longestSubarray(nums);
    assert(result == ans);


    nums = {1,1,1};
    ans = 2;
    result = longestSubarray(nums);
    assert(result == ans);

    nums = {1,1,0,0,1,1,1,0,1};
    ans = 4;
    result = longestSubarray(nums);
    assert(result == ans);

    nums = {0, 0, 0};
    ans = 0;
    result = longestSubarray(nums);
    assert(result == ans);

    return 0;
}
