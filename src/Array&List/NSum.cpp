#include <algorithm>
#include <iostream>
#include <vector>

#include <cassert>

using namespace std;

vector<vector<int>> nSum(vector<int>& nums, int target, int n, int start);

// https://leetcode-cn.com/problems/4sum/
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    return nSum(nums, target, 4, 0);
}

vector<vector<int>> nSum(vector<int>& nums, int target, int n, int start) {
    int size = static_cast<int>(nums.size());
    vector<vector<int>> result;
    if (size < 2 || size < n) return result;

    // 两数之和
    if (n == 2) {
        int left = start;
        int right = size - 1;
        while (left < right) {
            int begin = left;
            int end = right;
            int sum = nums[begin] + nums[end];
            if (sum == target) {
                result.push_back({nums[left], nums[right]});
                while (left <= right && nums[begin] == nums[left]) ++left;
                while (right >= left && nums[end] == nums[right]) --right;
            } else if (sum < target) {
                while (left <= right && nums[begin] == nums[left]) ++left;
            } else if (sum > target) {
                while (right >= left && nums[end] == nums[right]) --right;
            }
        }
    } else {
        for (int i = start; i < size; i++) {
            auto subs = nSum(nums, target - nums[i], n - 1, i + 1);
            for (auto& sub : subs) {
                sub.push_back(nums[i]);
                result.push_back(sub);
            }

            while (i < size - 1 && nums[i] == nums[i + 1]) i++;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    vector<int> nums;
    int target;
    vector<vector<int>> result;
    vector<vector<int>> ans;

    auto cmp = [](vector<int>& lhs, vector<int>& rhs) {
        sort(lhs.begin(), lhs.end());
        sort(rhs.begin(), rhs.end());
        int size = static_cast<int>(lhs.size());
        for (int i = 0; i < size; i++) {
            if (lhs[i] != rhs[i]) return lhs[i] < rhs[i];
        }
        return true;
    };

    nums = {1, 0, -1, 0, -2, 2};
    target = 0;
    ans = {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}};
    result = fourSum(nums, target);
    sort(ans.begin(), ans.end(), cmp);
    sort(result.begin(), result.end(), cmp);
    assert(ans == result);

    nums = {2, 2, 2, 2, 2};
    target = 8;
    ans = {{2, 2, 2, 2}};
    result = fourSum(nums, target);
    sort(ans.begin(), ans.end(), cmp);
    sort(result.begin(), result.end(), cmp);
    assert(ans == result);

    return 0;
}