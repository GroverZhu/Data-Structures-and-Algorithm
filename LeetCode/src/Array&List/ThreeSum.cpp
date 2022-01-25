#include <iostream>
#include <vector>
#include <algorithm>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/3sum
vector<vector<int>> threeSum(vector<int>& nums) {
    int size = static_cast<int>(nums.size());
    vector<vector<int>> result;
    if (size < 3) return result;

    sort(nums.begin(), nums.end());

    for (int i = 0; i < size; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int target = -nums[i];
        int left = i + 1;
        int right = size - 1;
        while (left < right) {
            int begin = left;
            int end = right;
            int sum = nums[begin] + nums[end];
            if (sum == target) {
                result.push_back({nums[i], nums[begin], nums[end]});
                while (begin <= right && nums[begin] == nums[left]) ++begin;
                while (end >= left && nums[end] == nums[right]) --end;
                left = begin;
                right = end;
            } else if (sum > target) {
                while (end > left && nums[end] == nums[right]) --end;
                right = end;
            } else if (sum < target) {
                while (begin < right && nums[begin] == nums[left]) ++begin;
                left = begin;
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {

    vector<int> nums;
    vector<vector<int>> result;
    vector<vector<int>> ans;

    auto cmp = [](vector<int>& lhs, vector<int>& rhs) {
        sort(lhs.begin(), lhs.end());
        sort(rhs.begin(), rhs.end());
        for (int i = 0; i < static_cast<int>(lhs.size()); i++) {
            if (lhs[i] != rhs[i]) {
                return lhs[i] < rhs[i];
            }
        }
        return true;
    };

    nums = {-1,0,1,2,-1,-4};
    ans = {{-1, 0, 1}, {-1, -1, 2}};
    result = threeSum(nums);

    sort(ans.begin(), ans.end(), cmp);
    sort(result.begin(), result.end(), cmp);
    assert(ans == result);


    nums = {-2,0,0,2,2};
    ans = {{-2, 0, 2}};
    result = threeSum(nums);

    sort(ans.begin(), ans.end(), cmp);
    sort(result.begin(), result.end(), cmp);
    assert(ans == result);

    return 0;
}