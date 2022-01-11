// https://leetcode-cn.com/problems/maximum-subarray/

#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/maximum-subarray/
int maxSubArray(vector<int>& nums) {
    int size = nums.size();
    if (size == 0) return 0;
    if (size == 1) return nums[0];

    vector<int> sums(size, 0);
    sums[0] = nums[0];
    int result = sums[0];
    for (int i = 1; i < size; i++) {
        sums[i] = max(sums[i - 1] + nums[i], nums[i]);
        result = max(result, sums[i]);
    }
    return result;
}

// 进阶版本，求其组成的数组
vector<int> maxSubArrayList(vector<int>& nums) {
    int size = nums.size();
    if (size <= 1) return nums;

    vector<int> sums(size, 0);
    sums[0] = nums[0];
    int end = 0;
    int max_sum = sums[0];
    for (int i = 1; i < size; i++) {
        sums[i] = max(sums[i - 1] + nums[i], nums[i]);
        if (max_sum < sums[i]) {
            max_sum = sums[i];
            end = i;
        }
    }

    deque<int> result;
    result.push_front(nums[end]);
    max_sum -= nums[end];
    while (end >= 0 && max_sum != 0) {
        while (end >= 0 && sums[end] != max_sum) --end;
        result.push_front(nums[end]);
        max_sum -= nums[end];
    }

    return vector<int>(result.begin(), result.end());
}

int main(int argc, char* argv[]) {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(6 == maxSubArray(nums));
    auto arr = maxSubArrayList(nums);
    vector<int> ans = {4, -1, 2, 1};
    assert(arr == ans);

    nums = {1};
    assert(1 == maxSubArray(nums));
    arr = maxSubArrayList(nums);
    ans = {1};
    assert(ans == arr);


    nums = {5, 4, -1, 7, 8};
    assert(23 == maxSubArray(nums));
    arr = maxSubArrayList(nums);
    ans = {5, 4, -1, 7, 8};
    assert(nums == arr);

    nums = {-2, -1};
    assert(-1 == maxSubArray(nums));
    arr = maxSubArrayList(nums);
    ans = {-1};
    assert(arr == ans);
    return 0;
}