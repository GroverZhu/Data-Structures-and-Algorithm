#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

int leftBound(vector<int>& nums, int target) {
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
            right = mid;
        }
    }

    if (left >= size || nums[left] != target) return -1;
    return left;
}

int rightBound(vector<int>& nums, int target) {
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
            left = mid + 1;
        }
    }

    if (right <= 0 || nums[right - 1] != target) return -1;
    return right - 1; 

}

// https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/

vector<int> searchRange(vector<int>& nums, int target) {
    return {leftBound(nums, target), rightBound(nums, target)};
}


int main(int argc, char* argv[]) {
    
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    int target = 8;
    vector<int> ans = {3, 4};
    vector<int> result = searchRange(nums, target);
    assert(result == ans);

    nums = {5, 7, 7, 8, 8, 10};
    target = 6;
    ans = {-1, -1};
    result = searchRange(nums, target);
    assert(result == ans);

    nums = {};
    target = 0;
    ans = {-1, -1};
    result = searchRange(nums, target);
    assert(result == ans);
    return 0;
}