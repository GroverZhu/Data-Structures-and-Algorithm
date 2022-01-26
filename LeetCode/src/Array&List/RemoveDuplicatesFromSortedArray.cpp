#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/
int removeDuplicates(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    if (size <= 1) return size;
    int first = 1;
    for (int i = 1; i < size; i++) {
        if (nums[i] == nums[first - 1]) continue;
        swap(nums[first], nums[i]);
        ++first;
    }
    return first;
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int len, len_ans;
    vector<int> ans;

    nums = {1, 1, 2};
    len_ans = 2;
    len = removeDuplicates(nums);
    assert(len == len_ans);
    ans = {1, 2};
    for (int i = 0; i < len; i++) {
        assert(nums[i] == ans[i]);
    }

    nums = {0,0,1,1,1,2,2,3,3,4};
    len_ans = 5;
    len = removeDuplicates(nums);
    assert(len == len_ans);
    ans = {0,1,2,3,4};
    for (int i = 0; i < len; i++) {
        assert(nums[i] == ans[i]);
    }
    return 0;
}