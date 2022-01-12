#include <iostream>
#include <vector>
#include <set>

#include <cassert>

using namespace std;

// https://leetcode-cn.com/problems/subsets/

void dfs(vector<vector<int>>& result, vector<int>& nums, vector<int> temp, int index) {

    if (index > static_cast<int>(nums.size())) return;

    result.push_back(temp);

    for (int i = index; i < static_cast<int>(nums.size()); i++) {
        temp.emplace_back(nums[i]);
        dfs(result, nums, temp, i + 1);
        temp.pop_back();
    }

}

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> temp;

    dfs(result, nums, temp, 0);

    return result;
}

int main(int argc, char* argv[]) {
    vector<int> nums = {1, 2, 3};
    set<vector<int>> ans = {{},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3}};
    auto result = subsets(nums);
    set<vector<int>> transfer(result.begin(), result.end());
    assert(ans == transfer);
    return 0;
}