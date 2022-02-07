#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/
int findMin(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    int left = 0;
    int right = size;
    int mid;

    if (size == 1 || nums[left] <= nums[right - 1]) return nums[left];

    while (left < right) {
        mid = (right - left) / 2.0 + left;
        if (nums[mid] > nums[0]) {
            left = mid + 1;
        } else if (nums[mid] < nums[0]) {
            right = mid;
        } else if (nums[mid] == nums[0]) {
            left = mid + 1;
        }
    }
    return nums[left];
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int result;
    int ans;
    nums = {3, 4, 5, 1, 2};
    ans = 1;
    result = findMin(nums);
    assert(ans == result);

    nums = {4, 5, 6, 7, 0, 1, 2};
    ans = 0;
    result = findMin(nums);
    assert(ans == result);

    nums = {11, 13, 15, 17};
    ans = 11;
    result = findMin(nums);
    assert(ans == result);

    nums = {2, 1};
    ans = 1;
    result = findMin(nums);
    assert(ans == result);


    nums = {3, 1, 2};
    ans = 1;
    result = findMin(nums);
    assert(ans == result);
    return 0;
}
