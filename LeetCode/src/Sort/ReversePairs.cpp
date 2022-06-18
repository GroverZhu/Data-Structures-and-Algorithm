#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// [begin, end]
int mergeSort(vector<int>& nums, int begin, int end) {
    if (begin >= end) return 0;
    int mid = (end - begin) / 2 + begin;
    int result = 0;
    int left = mergeSort(nums, begin, mid);
    int right = mergeSort(nums, mid + 1, end);

    result += left + right;

    int leftIndex = begin;
    int rightIndex = mid + 1;

    while (leftIndex <= mid && rightIndex <= end) {
        if (nums[leftIndex] / 2.0 > nums[rightIndex]) {
            result += (mid - leftIndex + 1);
            ++rightIndex;
        } else {
            ++leftIndex;
        }
    }

    // 合并
    int size = end - begin + 1;
    vector<int> tmp(size);
    leftIndex = begin;
    rightIndex = mid + 1;
    int index = 0;
    while (leftIndex <= mid && rightIndex <= end) {
        if (nums[leftIndex] <= nums[rightIndex]) {
            tmp[index++] = nums[leftIndex++];
        } else {
            tmp[index++] = nums[rightIndex++];
        }
    }

    while (leftIndex <= mid) tmp[index++] = nums[leftIndex++];
    while (rightIndex <= end) tmp[index++] = nums[rightIndex++];

    for (index = 0; index < size; index++) {
        nums[begin + index] = tmp[index];
    }

    return result;
}

// https://leetcode-cn.com/problems/reverse-pairs/
int reversePairs(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    if (size <= 1) return 0;
    return mergeSort(nums, 0, size - 1);
}

int main(int argc, char* argv[]) {
    vector<int> nums;

    nums = {1, 3, 2, 3, 1};
    assert(2 == reversePairs(nums));

    nums = {2, 4, 3, 5, 1};
    assert(3 == reversePairs(nums));

    return 0;
}