// https://leetcode-cn.com/problems/maximum-subarray/

#include <cassert>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>

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

// 进阶版本，求其组成的任意一个数组
vector<int> maxSubArrayList(vector<int>& nums) {
    int size = nums.size();
    if (size <= 1) return nums;

    vector<int> sums(size, 0);
    sums[0] = nums[0];
    int end = 0;
    int max_sum = sums[0];
    for (int i = 1; i < size; i++) {
        // 第一次出现的最大子数组和
        sums[i] = max(sums[i - 1] + nums[i], nums[i]);
        if (max_sum < sums[i]) {  // < 第一次出现的(最短)，<= 最后一次出现的(最长)
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

// 判断一个数组(sub)是否为另一个数组(seq)的子序列
bool isSubsequence(vector<int>& seq, vector<int>& sub) {
    int seqSize = static_cast<int>(seq.size());
    int subSize = static_cast<int>(sub.size());
    if (subSize > seqSize) return false;
    int seqIndex = 0;
    int subIndex = 0;

    while (seqIndex < seqSize && subIndex < subSize) {
        while (seqIndex < seqSize && seq[seqIndex] != sub[subIndex]) {
            seqIndex++;
        }
        if (seqIndex != seqSize) {
            seqIndex++;
            subIndex++;
        }
    }

    return seqIndex <= seqSize && subIndex == subSize;
}

int main(int argc, char* argv[]) {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    assert(6 == maxSubArray(nums));
    auto arr = maxSubArrayList(nums);
    assert(6 == accumulate(arr.begin(), arr.end(), 0));
    assert(true == isSubsequence(nums, arr));
    // vector<int> ans = {4, -1, 2, 1};

    nums = {1};
    assert(1 == maxSubArray(nums));
    arr = maxSubArrayList(nums);
    assert(1 == accumulate(arr.begin(), arr.end(), 0));
    assert(true == isSubsequence(nums, arr));
    // ans = {1};

    nums = {5, 4, -1, 7, 8};
    assert(23 == maxSubArray(nums));
    arr = maxSubArrayList(nums);
    assert(23 == accumulate(arr.begin(), arr.end(), 0));
    assert(true == isSubsequence(nums, arr));
    // ans = {5, 4, -1, 7, 8};

    nums = {-2, -1};
    assert(-1 == maxSubArray(nums));
    arr = maxSubArrayList(nums);
    assert(-1 == accumulate(arr.begin(), arr.end(), 0));
    assert(true == isSubsequence(nums, arr));
    // ans = {-1};

    nums = {5, 4, -1, -1, 2};
    assert(9 == maxSubArray(nums));
    arr = maxSubArrayList(nums);
    assert(9 == accumulate(arr.begin(), arr.end(), 0));
    assert(true == isSubsequence(nums, arr));
    // ans = {5, 4} {5, 4, -1, -1, 2}

    return 0;
}