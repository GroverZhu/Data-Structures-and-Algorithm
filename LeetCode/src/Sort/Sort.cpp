#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://www.cnblogs.com/onepixel/p/7674659.html

#if 0
// 冒泡排序
#endif

#if 0
// 选择排序
#endif

#if 0
// 插入排序
#endif

#if 0
// 希尔排序
#endif

#if 0
// 堆排序

#endif

#if 0
// 归并排序
// [begin, end]
void mergeSort(vector<int>& nums, int begin, int end) {
    if (begin >= end) return;
    int mid = (end - begin) / 2 + begin;

    mergeSort(nums, begin, mid);
    mergeSort(nums, mid + 1, end);

    int size = end - begin + 1;
    vector<int> tmp(size);
    int left = begin;
    int right = mid + 1;
    int index = 0;

    while (left <= mid && right <= end) {
        if (nums[left] <= nums[right]) {
            tmp[index++] = nums[left++];
        } else {
            tmp[index++] = nums[right++];
        }
    }

    while (left <= mid) tmp[index++] = nums[left++];
    while (right <= end) tmp[index++] = nums[right++];

    for (int i = 0; i < size; i++) {
        nums[i + begin] = tmp[i];
    }


}
#endif

#if 1
// 快速排序
// [begin, end]
void quickSort(vector<int>& nums, int begin, int end) {
    if (begin >= end) return;
    int randomIndex = (rand() % (end - begin + 1)) + begin;
    if (randomIndex != begin) swap(nums[randomIndex], nums[begin]);  // 蒙特卡洛算法，均摊复杂度
    int pivot = nums[begin];
    int left = begin + 1;
    int right = end;

    while (true) {
        while (left <= end && nums[left] <= pivot) ++left;
        while (right > begin && nums[right] > pivot) --right;
        if (left >= right) break;
        swap(nums[left], nums[right]);
    }

    swap(nums[begin], nums[right]);

    quickSort(nums, begin, right - 1);
    quickSort(nums, right + 1, end);
}
#endif

#if 0
// 堆排序
#endif

#if 0
// 计数排序
#endif

#if 0
// 桶排序
#endif

#if 0
// 基数排序
#endif

// https://leetcode-cn.com/problems/sort-an-array/
vector<int> sortArray(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    quickSort(nums, 0, size - 1);
    return nums;
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    vector<int> ans;

    nums = {5, 2, 3, 1};
    ans = {1, 2, 3, 5};
    assert(ans == sortArray(nums));

    nums = {5, 1, 1, 2, 0, 0};
    ans = {0, 0, 1, 1, 2, 5};
    assert(ans == sortArray(nums));

    return 0;
}