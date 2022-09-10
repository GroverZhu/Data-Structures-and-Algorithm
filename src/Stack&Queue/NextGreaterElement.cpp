#include <cassert>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

// https://leetcode-cn.com/problems/next-greater-element-i/
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    int size2 = static_cast<int>(nums2.size());
    stack<int> stk;
    map<int, int> ref;

    for (int i = size2 - 1; i >= 0; i--) {
        while (!stk.empty() && nums2[i] >= nums2[stk.top()]) {
            stk.pop();
        }
        ref[nums2[i]] = stk.empty() ? -1 : nums2[stk.top()];
        stk.push(i);
    }

    int size1 = static_cast<int>(nums1.size());
    vector<int> result(size1, 0);
    for (int i = 0; i < size1; i++) {
        result[i] = ref[nums1[i]];
    }
    return result;
}

// https://leetcode-cn.com/problems/next-greater-element-ii/submissions/
vector<int> nextGreaterElements(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    int index = 2 * size - 1;
    vector<int> result(size, 0);
    stack<int> stk;

    for (; index >= 0; index--) {
        while (!stk.empty() && nums[index % size] >= nums[stk.top() % size]) {
            stk.pop();
        }
        result[index % size] = stk.empty() ? -1 : nums[stk.top() % size];
        stk.push(index);
    }

    return result;
}

// https://leetcode-cn.com/problems/daily-temperatures/
vector<int> dailyTemperatures(vector<int>& temperatures) {
    int size = static_cast<int>(temperatures.size());
    vector<int> result(size, 0);
    stack<int> stk;
    for (int i = size - 1; i >= 0; i--) {
        while (!stk.empty() && temperatures[i] >= temperatures[stk.top()]) {
            stk.pop();
        }
        result[i] = stk.empty() ? 0 : stk.top() - i;
        stk.push(i);
    }
    return result;
}

int main(int argc, char* argv[]) {
    vector<int> nums1, nums2;
    vector<int> ans;

    nums1 = {4, 1, 2};
    nums2 = {1, 3, 4, 2};
    ans = {-1, 3, -1};
    assert(ans == nextGreaterElement(nums1, nums2));

    nums1 = {2, 4};
    nums2 = {1, 2, 3, 4};
    ans = {3, -1};
    assert(ans == nextGreaterElement(nums1, nums2));

    nums1 = {1, 2, 1};
    ans = {2, -1, 2};
    assert(ans == nextGreaterElements(nums1));

    nums1 = {73, 74, 75, 71, 69, 72, 76, 73};
    ans = {1, 1, 4, 2, 1, 1, 0, 0};
    assert(ans == dailyTemperatures(nums1));

    nums1 = {30, 40, 50, 60};
    ans = {1, 1, 1, 0};
    assert(ans == dailyTemperatures(nums1));

    nums1 = {30, 60, 90};
    ans = {1, 1, 0};
    assert(ans == dailyTemperatures(nums1));

    return 0;
}