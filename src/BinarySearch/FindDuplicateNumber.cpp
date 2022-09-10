#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/find-the-duplicate-number/
int findDuplicate(vector<int>& nums) {
#if 0

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

#if 1
    int size = static_cast<int>(nums.size());
    int left = 0;
    int right = size;
    int mid;
    int ans = -1;

    while (left < right) {
        mid = (right - left) / 2 + left;

        int cnt = 0;
        for (int i = 0; i < size; i++) {
            if (nums[i] <= mid) ++cnt;
        }

        if (cnt <= mid) {
            left = mid + 1;
        } else {
            right = mid;
            ans = right;
        }
    }
    return ans;

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
