#include <iostream>
#include <vector>

#include <cassert>
using namespace std;

// https://leetcode-cn.com/problems/longest-increasing-subsequence/
int lengthOfLIS(vector<int>& nums) {
#if 0  // n^2
    int size = static_cast<int>(nums.size());
    if (size <= 1) return size;
    vector<int> lens(size, 1);
    lens[0] = 1;
    int result = 1;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                lens[i] = max(lens[j] + 1, lens[i]);
            }
        }
        result = max(result, lens[i]);
    }

    return result;
#endif

#if 1  // nlogn

    int size = static_cast<int>(nums.size());
    if (size <= 1) return size;

    vector<int> top(size, 0);
    int piles = 0;
    for (int i = 0; i < size; i++) {
        int cur = nums[i];

        int left = 0;
        int right = piles;

        while (left < right) {
            int mid = (right + left) / 2;
            if (top[mid] < cur) {
                left = mid + 1;
            } else if (top[mid] > cur) {
                right = mid;
            } else if (top[mid] == cur) {
                right = mid;
            }
        }

        if (left == piles) piles += 1;
        top[left] = cur;
    }

    return piles;

#endif
}
int main(int argc, char* argv[]) {
    vector<int> nums = {1, 5, 122, 34, 45, 232, 342, 34};
    assert(6 == lengthOfLIS(nums));

    nums = {10, 9, 2, 5, 3, 6, 101, 18};
    assert(4 == lengthOfLIS(nums));

    nums = {0, 1, 0, 3, 2, 3};
    assert(4 == lengthOfLIS(nums));

    nums = {7, 7};
    assert(1 == lengthOfLIS(nums));

    return 0;
}