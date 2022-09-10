#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/search-in-rotated-sorted-array/A
int search(vector<int>& nums, int target) {
    int size = static_cast<int>(nums.size());

    int left = 0;
    int right = size;
    int mid;

    // 分割点
    while (left < right) {
        mid = (right - left) / 2 + left;
        if (nums[mid] < nums[0]) {
            right = mid;
        } else if (nums[mid] > nums[0]) {
            left = mid + 1;
        } else if (nums[mid] == nums[0]) {
            left = mid + 1;
        }
    }

    int pivot = left;
    if (target < nums[0]) {
        left = pivot;
        right = size;
    } else {
        left = 0;
        right = pivot;
    }

    while (left < right) {
        mid = (right - left) / 2 + left;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] > target) {
            right = mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        }
    }

    return -1;
}

int main(int argc, char* argv[]) {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    int target = 0;
    int result = search(nums, target);
    int ans = 4;
    assert(result == ans);

    nums = {4, 5, 6, 7, 0, 1, 2};
    target = 3;
    result = search(nums, target);
    ans = -1;
    assert(result == ans);

    nums = {1};
    target = 0;
    result = search(nums, target);
    ans = -1;
    assert(result == ans);

    nums = {1};
    target = 1;
    result = search(nums, target);
    ans = 0;
    assert(result == ans);

    nums = {4, 5, 6, 7, 0, 1, 2};
    target = 7;
    result = search(nums, target);
    ans = 3;
    assert(result == ans);
    return 0;
}
