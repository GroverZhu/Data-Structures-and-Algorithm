#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/search-insert-position/
int searchInsert(vector<int>& nums, int target) {
    int size = static_cast<int>(nums.size());

    int left = 0;
    int right = size;
    int mid;
    while (left < right) {
        mid = (right - left) / 2 + left;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid;
        } else if (nums[mid] == target) {
            return mid;
        }
    }
    return right;
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int target;
    int ans;
    int result;

    nums = {1, 3, 5, 6};
    target = 5;
    ans = 2;
    result = searchInsert(nums, target);
    assert(ans == result);

    nums = {1, 3, 5, 6};
    target = 2;
    ans = 1;
    result = searchInsert(nums, target);
    assert(ans == result);

    nums = {1, 3, 5, 6};
    target = 7;
    ans = 4;
    result = searchInsert(nums, target);
    assert(ans == result);

    nums = {1, 3, 5, 6};
    target = 0;
    ans = 0;
    result = searchInsert(nums, target);
    assert(ans == result);

    nums = {1};
    target = 0;
    ans = 0;
    result = searchInsert(nums, target);
    assert(ans == result);
    return 0;
}
