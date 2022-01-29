#include <iostream>
#include <vector>
#include <deque>

#include <cassert>

using namespace std;


// https://leetcode-cn.com/problems/sliding-window-maximum/
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    if (k == 1) return nums;
    int size = static_cast<int>(nums.size());

    vector<int> ans(size - k + 1);
    deque<int> mono;
    for (int i = 0; i < size; i++) {
        while (!mono.empty() && nums[mono.back()] <= nums[i]) {
            mono.pop_back();
        }
        mono.push_back(i);
        while (i - mono.front() >= k) mono.pop_front();
        if (i - k + 1 >= 0) ans[i - k + 1] = nums[mono.front()];
    }

    return ans;
}

int main(int argc, char* argv[]) {
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<int> ans = {3, 3, 5, 5, 6, 7};
    assert(ans == maxSlidingWindow(nums, k));

    nums = {1, 3, -1, -3, 5, 3, 6, 7};
    k = 1;
    ans = {1, 3, -1, -3, 5, 3, 6, 7};
    assert(ans == maxSlidingWindow(nums, k));

    nums = {1, -1};
    k = 1;
    ans = {1, -1};
    assert(ans == maxSlidingWindow(nums, k));

    nums = {9, 12};
    k = 2;
    ans = {12};
    assert(ans == maxSlidingWindow(nums, k));
    return 0;
}