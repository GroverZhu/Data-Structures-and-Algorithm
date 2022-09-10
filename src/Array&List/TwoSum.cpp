#include <iostream>
#include <map>
#include <vector>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/two-sum/
vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> val2index;
    int size = static_cast<int>(nums.size());

    for (int i = 0; i < size; i++) {
        if (val2index.find(target - nums[i]) != val2index.end()) {
            return {val2index[target - nums[i]], i};
        }
        val2index[nums[i]] = i;
    }

    return {};
}

int main(int argc, char* argv[]) {
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    auto result = twoSum(nums, target);
    assert(result.size() == 2);
    assert(target == nums[result[0]] + nums[result[1]]);
    return 0;
}