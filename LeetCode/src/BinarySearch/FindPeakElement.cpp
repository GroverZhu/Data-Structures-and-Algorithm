#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/find-peak-element/
int findPeakElement(vector<int>& nums) {

#ifdef FORCE
    int size = static_cast<int>(nums.size());
    if (size == 1) return 0;
    int prev = 0;
    int cur = 1;
    while (cur < size) {
        if (nums[prev] > nums[cur]) {
            return prev;
        }
        prev++;
        cur++;
    }
    if (cur == size) return cur - 1;
    return -1;
#else 
    int size = static_cast<int>(nums.size());
    if (size == 1) return 0;
    int left = 0;
    int right = size;
    int mid;
    while (left < right) {
        mid = (right - left) / 2 + left;
        if ((mid < size - 1) && nums[mid] <= nums[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
# endif
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int result, ans;

    nums = {1, 2, 3, 1};
    ans = 2;
    result = findPeakElement(nums);
    assert(ans == result);

    nums = {1, 2, 1, 3, 5, 6, 4};
    result = findPeakElement(nums);
    assert((1 == result || 5 == result));

    nums = {2, 1};
    result = findPeakElement(nums);
    assert(0 == result);
    return 0;
}
