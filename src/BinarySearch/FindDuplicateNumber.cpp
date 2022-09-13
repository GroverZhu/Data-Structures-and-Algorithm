#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/find-the-duplicate-number/
int findDuplicate(vector<int>& nums) {
#if 0  // 快慢指针
    int slow = 0;
    int fast = 0;

    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    slow = 0;

    do {
        slow = nums[slow];
        fast = nums[fast];
    } while (slow != fast);

    return slow;
#endif

#if 1  // 二分查找 + 抽屉原理
    int size = static_cast<int>(nums.size());
    int left = 1;
    int right = size - 1;
    int mid;

    // [left, right]
    while (left < right) {
        mid = (right - left) / 2 + left;

        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (nums[i] <= mid) ++cnt;
        }

        if (cnt <= mid) {
            left = mid + 1;  // [mid + 1, right]
        } else {
            right = mid;  // [left, mid]
        }
    }
    return left;

#endif

#if 0  // 原地哈希
    int size = static_cast<int>(nums.size());

    for (int i = 0; i < size; i++) {
        // nums[i] - 1 == i -> nums[nums[i] - 1] == nums[i]
        while (i > 0 && nums[i] <= size && nums[nums[i] - 1] != nums[i]) {
            swap(nums[nums[i] - 1], nums[i]);
        }
    }

    for (int i = 1; i < size; i++) {
        if (nums[i] - 1 != i) {
            return nums[i];
        }
    }

    return 0;

#endif
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int result;
    int ans;

    nums = {1, 3, 4, 2, 2};
    ans = 2;
    result = findDuplicate(nums);
    assert(ans == result);

    nums = {3, 1, 3, 4, 2};
    ans = 3;
    result = findDuplicate(nums);
    assert(ans == result);

    nums = {1, 1};
    ans = 1;
    result = findDuplicate(nums);
    assert(ans == result);

    nums = {1, 1, 2};
    ans = 1;
    result = findDuplicate(nums);
    assert(ans == result);

    return 0;
}
